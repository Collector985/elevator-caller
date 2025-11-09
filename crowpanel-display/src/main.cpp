#include <Arduino.h>
#include <Wire.h>
#include <algorithm>
#include <lvgl.h>
#include <TCA9534.h>

#include "elevator_ui.h"
#include "lgfx_setup.h"
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
constexpr uint8_t PCA9557_ADDR = 0x18;
constexpr uint8_t PCA_PIN_LED_BK = 1;
constexpr uint8_t PCA_PIN_TP_RST = 2;
constexpr uint8_t PCA_PIN_AUDIO_MUTE = 3;
constexpr uint8_t PCA_PIN_AUDIO_SHUT = 4;

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

static void initDisplay();
static void initLVGL();
static void lvglTouchRead(lv_indev_drv_t *, lv_indev_data_t *data);
static void initBacklightControl();
static void resetTouchController();
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

  // Initialize I2C buses FIRST before anything else
  Wire.end();  // Ensure default Wire instance is stopped before reconfiguring pins
  Wire.begin(17, 18);  // Gateway I2C bus
  Wire.setClock(100000);

  ioBus.begin(15, 16, 400000);  // Shared backlight/touch I2C bus
  delay(100);  // Give I2C time to stabilize

  initBacklightControl();
  resetTouchController();

  // Scan shared backlight/touch I2C bus (GPIO 15/16)
  Serial.println("===========================================");
  Serial.println("Scanning shared I2C bus (GPIO 15=SDA, 16=SCL)...");
  Serial.println("===========================================");
  int deviceCount = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    ioBus.beginTransmission(addr);
    uint8_t error = ioBus.endTransmission();
    if (error == 0) {
      Serial.printf(">>> I2C device found at 0x%02X", addr);
      if (addr == 0x18) {
        Serial.print(" (TCA9534 I/O Expander)");
      } else if (addr == 0x30) {
        Serial.print(" (Backlight Controller)");
      } else if (addr == 0x5D || addr == 0x14) {
        Serial.print(" (GT911 Touch Controller)");
      }
      Serial.println();
      deviceCount++;
    }
  }
  Serial.printf("Found %d device(s) on shared bus\n", deviceCount);
  Serial.println("===========================================");

  initDisplay();

  // Test if touch is working
  Serial.println("===========================================");
  Serial.println("Testing GT911 Touch Controller...");
  Serial.println("===========================================");

  delay(100);
  uint16_t testX, testY;
  bool touchDetected = tft.getTouch(&testX, &testY);

  if (touchDetected) {
    Serial.printf("SUCCESS: Touch controller responding! X=%d, Y=%d\n", testX, testY);
  } else {
    Serial.println("WARNING: Touch controller NOT responding");
    Serial.println("Possible issues:");
    Serial.println("  - GT911 not on I2C bus");
    Serial.println("  - Wrong I2C address (check scan above)");
    Serial.println("  - Touch needs reset sequence");
    Serial.println("  - Touch needs configuration data");
  }
  Serial.println("===========================================");

  initLVGL();
  ui_theme_init();

  elevator_ui_init();

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
  elevator_ui_tick();

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
  bool touched = tft.getTouch(&rawX, &rawY);

  static bool lastTouched = false;
  static uint32_t lastDebugPrint = 0;
  static uint32_t lastUiLog = 0;

  if (!touched) {
    if (lastTouched) {
      Serial.println("TOUCH: Released");
    }
    lastTouched = false;
    data->state = LV_INDEV_STATE_RELEASED;
    return;
  }

  lastTouched = true;

  uint16_t mappedX = rawX;
  uint16_t mappedY = rawY;

  if (mappedX >= SCREEN_WIDTH) mappedX = SCREEN_WIDTH - 1;
  if (mappedY >= SCREEN_HEIGHT) mappedY = SCREEN_HEIGHT - 1;

  uint32_t now = millis();
  if (now - lastDebugPrint > 500) {
    Serial.printf("TOUCH: Raw(%u,%u) -> Mapped(%u,%u)\n", rawX, rawY, mappedX,
                  mappedY);
    lastDebugPrint = now;
  }

  if (now - lastUiLog > 1000) {
    char buf[64];
    snprintf(buf, sizeof(buf), "Touch raw(%u,%u) -> mapped(%u,%u)", rawX, rawY,
             mappedX, mappedY);
    elevator_ui_log_message(buf);
    lastUiLog = now;
  }

  data->state = LV_INDEV_STATE_PRESSED;
  data->point.x = mappedX;
  data->point.y = mappedY;
}

static void initBacklightControl() {
  // ioBus already initialized in setup()
  ioExpander.attach(ioBus);
  ioExpander.setDeviceAddress(PCA9557_ADDR);
  ioExpander.config(TCA9534::Config::OUT);
  ioExpander.output(0xFF);

  ioExpander.output(PCA_PIN_LED_BK, TCA9534::Level::H);
  ioExpander.output(PCA_PIN_AUDIO_MUTE, TCA9534::Level::H);
  ioExpander.output(PCA_PIN_AUDIO_SHUT, TCA9534::Level::H);

  // Hold touch controller in reset until we intentionally release it
  ioExpander.output(PCA_PIN_TP_RST, TCA9534::Level::L);
  delay(10);

  stcSetBacklight(8);
  stcDisableBuzzer();
}

static void resetTouchController() {
  // Follow the GT911 address select sequence: RESET low, INT high, RESET high, INT hi-Z
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  delay(2);
  ioExpander.output(PCA_PIN_TP_RST, TCA9534::Level::H);
  delay(5);
  pinMode(1, INPUT_PULLUP);
  delay(50);
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
