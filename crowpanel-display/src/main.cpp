#include <Arduino.h>
#include <Wire.h>
#include <algorithm>
#include <lvgl.h>
#include <TCA9534.h>

#include "elevator_ui.h"
#include "lgfx_setup.h"
#include "ui_styles.h"
#include "ui_theme.h"

#ifndef TOTAL_FLOORS
#error "TOTAL_FLOORS must be defined"
#endif
#ifndef I2C_MASTER_ADDRESS
#error "I2C_MASTER_ADDRESS must be defined"
#endif
#ifndef SCREEN_WIDTH
#error "SCREEN_WIDTH must be defined"
#endif
#ifndef SCREEN_HEIGHT
#error "SCREEN_HEIGHT must be defined"
#endif

constexpr uint8_t STC_BACKLIGHT_ADDR = 0x30;
constexpr uint8_t STC_CMD_BUZZER_OFF = 247;

constexpr uint16_t TOUCH_X_MIN = 0;
constexpr uint16_t TOUCH_X_MAX = 799;
constexpr uint16_t TOUCH_Y_MIN = 0;
constexpr uint16_t TOUCH_Y_MAX = 479;
constexpr bool TOUCH_SWAP_XY = true;
constexpr bool TOUCH_INVERT_X = false;
constexpr bool TOUCH_INVERT_Y = true;

struct DisplayPacket {
  uint8_t floor;
  uint8_t status;  // Bit0:UP Bit1:DOWN Bit2:LOAD Bit7:ELEV_POS
  int8_t rssi;
};

struct FloorState {
  bool upActive = false;
  bool downActive = false;
  bool loadActive = false;
  int8_t rssi = -120;
};

static LGFX tft;
static TwoWire ioBus = TwoWire(1);
static TCA9534 ioExpander;

static FloorState floorStates[TOTAL_FLOORS + 1];
static uint8_t currentElevatorFloor = 1;
static bool gatewayAvailable = false;
static bool lastGatewayState = false;
static uint32_t lastGatewayProbe = 0;
static uint32_t lastI2CRequest = 0;
static uint32_t lastTickUpdate = 0;

static void handleUICall(uint8_t floor, ElevatorCallType type, bool active);
static void initDisplay();
static void initLVGL();
static void lvglTouchRead(lv_indev_drv_t *, lv_indev_data_t *data);
static void initBacklightControl();
static void muteHardwareBuzzer();
static void stcSetBacklight(uint8_t level);
static void stcDisableBuzzer();
static bool stcSend(uint8_t value);
static bool probeGateway();
static void requestDataFromGateway();
static void sendClearCommand(uint8_t floor, uint8_t callTypeMask);
static void handleSerialCommands();

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println(F("========================================"));
  Serial.println(F("CrowPanel Elevator UI (LVGL 3-screen)"));
  Serial.println(F("========================================"));

  muteHardwareBuzzer();
  initBacklightControl();

  Wire.begin(17, 18);
  Wire.setClock(100000);

  initDisplay();
  initLVGL();
  ui_theme_init();
  ui_styles_init();

  elevator_ui_init();
  elevator_ui_set_call_handler(handleUICall);

  elevator_ui_log_message("SYSTEM: Display online");

  uint32_t now = millis();
  lastGatewayProbe = now;
  lastTickUpdate = now;
}

void loop() {
  handleSerialCommands();

  uint32_t now = millis();
  lv_tick_inc(now - lastTickUpdate);
  lastTickUpdate = now;
  lv_timer_handler();

  if (now - lastGatewayProbe > 2000) {
    gatewayAvailable = probeGateway();
    if (gatewayAvailable != lastGatewayState) {
      elevator_ui_log_message(gatewayAvailable ? "Gateway online"
                                               : "Gateway missing");
      lastGatewayState = gatewayAvailable;
    }
    lastGatewayProbe = now;
  }

  if (gatewayAvailable && (now - lastI2CRequest > 200)) {
    requestDataFromGateway();
    lastI2CRequest = now;
  }

  delay(5);
}

static void initDisplay() {
  tft.init();
  tft.setRotation(1);
  tft.setColorDepth(16);
  tft.setSwapBytes(true);
  tft.fillScreen(0x0000);
}

static void initLVGL() {
  lv_init();

  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[SCREEN_WIDTH * 10];
  lv_disp_draw_buf_init(&draw_buf, buf, nullptr, SCREEN_WIDTH * 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = SCREEN_WIDTH;
  disp_drv.ver_res = SCREEN_HEIGHT;
  disp_drv.flush_cb = [](lv_disp_drv_t *disp, const lv_area_t *area,
                         lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    tft.startWrite();
    tft.pushImage(area->x1, area->y1, w, h,
                  reinterpret_cast<const uint16_t *>(color_p));
    tft.endWrite();
    lv_disp_flush_ready(disp);
  };
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = lvglTouchRead;
  lv_indev_drv_register(&indev_drv);
}

static void lvglTouchRead(lv_indev_drv_t *, lv_indev_data_t *data) {
  uint16_t rawX = 0;
  uint16_t rawY = 0;
  if (!tft.getTouch(&rawX, &rawY)) {
    data->state = LV_INDEV_STATE_RELEASED;
    return;
  }

  auto clamp = [](uint16_t v, uint16_t minV, uint16_t maxV) {
    if (v < minV) return minV;
    if (v > maxV) return maxV;
    return v;
  };

  uint16_t xMin = TOUCH_X_MIN;
  uint16_t xMax = TOUCH_X_MAX;
  uint16_t yMin = TOUCH_Y_MIN;
  uint16_t yMax = TOUCH_Y_MAX;

  uint16_t adjX = clamp(rawX, xMin, xMax);
  uint16_t adjY = clamp(rawY, yMin, yMax);

  if (TOUCH_SWAP_XY) {
    std::swap(adjX, adjY);
    std::swap(xMin, yMin);
    std::swap(xMax, yMax);
  }
  if (TOUCH_INVERT_X) {
    adjX = xMax - (adjX - xMin);
  }
  if (TOUCH_INVERT_Y) {
    adjY = yMax - (adjY - yMin);
  }

  uint16_t mappedX =
      (uint32_t)(adjX - xMin) * (SCREEN_WIDTH - 1) / (xMax - xMin);
  uint16_t mappedY =
      (uint32_t)(adjY - yMin) * (SCREEN_HEIGHT - 1) / (yMax - yMin);

  data->state = LV_INDEV_STATE_PRESSED;
  data->point.x = mappedX;
  data->point.y = mappedY;
}

static void initBacklightControl() {
  ioBus.begin(15, 16, 400000);
  ioExpander.attach(ioBus);
  ioExpander.setDeviceAddress(0x18);
  ioExpander.config(TCA9534::Config::OUT);
  ioExpander.output(0xFF);

  ioExpander.output(1, TCA9534::Level::H);
  ioExpander.output(2, TCA9534::Level::L);
  delay(20);
  ioExpander.output(2, TCA9534::Level::H);
  delay(50);

  stcSetBacklight(8);
  stcDisableBuzzer();
}

static void muteHardwareBuzzer() {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
}

static bool stcSend(uint8_t value) {
  ioBus.beginTransmission(STC_BACKLIGHT_ADDR);
  ioBus.write(value);
  return ioBus.endTransmission() == 0;
}

static void stcSetBacklight(uint8_t level) {
  if (level > 245) level = 245;
  stcSend(level);
}

static void stcDisableBuzzer() {
  stcSend(STC_CMD_BUZZER_OFF);
}

static bool probeGateway() {
  Wire.beginTransmission(I2C_MASTER_ADDRESS);
  return Wire.endTransmission(true) == 0;
}

static void handleUICall(uint8_t floor, ElevatorCallType type, bool active) {
  uint8_t mask = 0xFF;
  switch (type) {
    case ElevatorCallType::Up:
      mask = 0x01;
      break;
    case ElevatorCallType::Down:
      mask = 0x02;
      break;
    case ElevatorCallType::Load:
      mask = 0x04;
      break;
  }

  if (!active) {
    sendClearCommand(floor, mask);
    elevator_ui_log_message("Display cleared call via touch");
  }
}

static void requestDataFromGateway() {
  Wire.requestFrom(I2C_MASTER_ADDRESS, sizeof(DisplayPacket));
  if (Wire.available() < sizeof(DisplayPacket)) return;

  DisplayPacket pkt;
  Wire.readBytes(reinterpret_cast<uint8_t *>(&pkt), sizeof(DisplayPacket));

  if (pkt.status & 0x80) {
    currentElevatorFloor = pkt.floor;
    elevator_ui_set_current_floor(pkt.floor, false);
    return;
  }

  if (pkt.floor < 1 || pkt.floor > TOTAL_FLOORS) return;

  bool up = pkt.status & 0x01;
  bool down = pkt.status & 0x02;
  bool load = pkt.status & 0x04;

  floorStates[pkt.floor].upActive = up;
  floorStates[pkt.floor].downActive = down;
  floorStates[pkt.floor].loadActive = load;
  floorStates[pkt.floor].rssi = pkt.rssi;

  elevator_ui_apply_floor_state(pkt.floor, up, down, load, false);

  char statusText[64];
  snprintf(statusText, sizeof(statusText), "Floor %u | RSSI %d dBm",
           pkt.floor, pkt.rssi);
  elevator_ui_log_message(statusText);
}

static void sendClearCommand(uint8_t floor, uint8_t callTypeMask) {
  Wire.beginTransmission(I2C_MASTER_ADDRESS);
  Wire.write(floor);
  Wire.write(0x20);
  Wire.write(callTypeMask);
  Wire.endTransmission();
}

static void handleSerialCommands() {
  while (Serial.available()) {
    char c = static_cast<char>(Serial.read());
    if (c == '\n' || c == '\r') continue;

    switch (c) {
      case 'c':
      case 'C':
        for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
          floorStates[f] = {};
          elevator_ui_apply_floor_state(f, false, false, false, true);
        }
        elevator_ui_log_message("Serial: Cleared all floor states");
        break;
      case 'l':
      case 'L':
        elevator_ui_log_message("Serial: ping");
        break;
      default:
        break;
    }
  }
}
