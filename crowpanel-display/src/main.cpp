/**
 * Elevator Operator Display
 * Hardware: CrowPanel 7" Advance (800x480)
 *
 * Features:
 * - 40-floor grid display (8x5 layout)
 * - UP/DOWN/LOAD indicator lights per floor
 * - Touch interface for manual call clearing
 * - I2C communication with T-ETH Elite gateway
 * - Real-time RSSI display
 * - Auto-refresh display
 */

#include <Arduino.h>
#include <lvgl.h>
#include <Wire.h>
#include <TCA9534.h>

#include "lgfx_setup.h"

// Display packet structure (must match gateway)
struct DisplayPacket {
  uint8_t floor;
  uint8_t status;  // Bit 0:UP, Bit 1:DOWN, Bit 2:LOAD, Bit 7:ELEVATOR_POS
  int8_t rssi;
};

// Floor state
struct FloorState {
  bool upActive = false;
  bool downActive = false;
  bool loadActive = false;
  int8_t rssi = -120;
  uint32_t lastUpdate = 0;
};

constexpr uint8_t STC_BACKLIGHT_ADDR = 0x30;
constexpr uint8_t STC_CMD_BUZZER_ON = 246;
constexpr uint8_t STC_CMD_BUZZER_OFF = 247;

// Global objects
LGFX tft;
TwoWire ioBus = TwoWire(1);
TCA9534 ioExpander;
FloorState floorStates[TOTAL_FLOORS + 1];
uint8_t currentElevatorFloor = 20;

// LVGL objects
lv_obj_t *screen;
lv_obj_t *floorGrid[TOTAL_FLOORS + 1];
lv_obj_t *floorLabels[TOTAL_FLOORS + 1];
lv_obj_t *upIndicators[TOTAL_FLOORS + 1];
lv_obj_t *downIndicators[TOTAL_FLOORS + 1];
lv_obj_t *loadIndicators[TOTAL_FLOORS + 1];
lv_obj_t *statusLabel;

// Colors
lv_color_t COLOR_UP = lv_color_hex(0x2ECC71);      // Green
lv_color_t COLOR_DOWN = lv_color_hex(0xE74C3C);    // Red
lv_color_t COLOR_LOAD = lv_color_hex(0xF39C12);    // Yellow
lv_color_t COLOR_INACTIVE = lv_color_hex(0xBDC3C7); // Light gray
lv_color_t COLOR_CURRENT = lv_color_hex(0x3498DB);  // Blue highlight
lv_color_t COLOR_BG = lv_color_hex(0x0B1320);      // Dark slate
lv_color_t COLOR_CARD_BG = lv_color_hex(0xECF0F1);
lv_color_t COLOR_BORDER = lv_color_hex(0xBDC3C7);
lv_color_t COLOR_TEXT = lv_color_hex(0x2C3E50);

// Function prototypes
void initDisplay();
void initLVGL();
void createFloorGrid();
void updateFloorDisplay(uint8_t floor);
void highlightCurrentFloor();
void requestDataFromGateway();
void sendClearCommand(uint8_t floor, uint8_t callType);
void floorTouchCallback(lv_event_t *e);
void initBacklightControl();
bool stcSend(uint8_t value);
void stcSetBacklight(uint8_t level);
void stcDisableBuzzer();

// Timing
uint32_t lastI2CRequest = 0;
uint32_t lastDisplayRefresh = 0;
uint32_t lastTickUpdate = 0;
uint32_t lastGatewayProbe = 0;
bool gatewayAvailable = false;

bool probeGateway();

// ============= SETUP =============
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("========================================"));
  Serial.println(F("CrowPanel Display v2.0"));
  Serial.println(F("40-Floor Elevator Operator Interface"));
  Serial.println(F("========================================"));

  initBacklightControl();

  // Initialize I2C as master
  Wire.begin(17, 18);  // CrowPanel I2C pins
  Wire.setClock(100000);  // 100kHz

  // Initialize display
  initDisplay();

  // Initialize LVGL
  initLVGL();

  // Create UI
  createFloorGrid();

  uint32_t now = millis();
  lastTickUpdate = now;
  lastGatewayProbe = now;

  Serial.println(F("Display ready!"));
}

// ============= MAIN LOOP =============
void loop() {
  uint32_t now = millis();

  // Keep LVGL tick running even without external timer
  lv_tick_inc(now - lastTickUpdate);
  lastTickUpdate = now;
  lv_timer_handler();

  // Probe gateway presence every 2 seconds
  if (now - lastGatewayProbe > 2000) {
    gatewayAvailable = probeGateway();
    lastGatewayProbe = now;
  }

  // Request data from gateway every 200ms
  if (gatewayAvailable && (now - lastI2CRequest > 200)) {
    requestDataFromGateway();
    lastI2CRequest = now;
  }

  // Refresh display every 100ms
  if (now - lastDisplayRefresh > 100) {
    for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
      if (now - floorStates[f].lastUpdate < 10000) {  // Only if recent update
        updateFloorDisplay(f);
      }
    }
    highlightCurrentFloor();
    lastDisplayRefresh = now;
  }

  delay(5);
}

// ============= DISPLAY INITIALIZATION =============
void initDisplay() {
  tft.init();
  tft.setRotation(0);  // Native landscape
  tft.setColorDepth(16);
  tft.setSwapBytes(true);
  tft.fillScreen(0x0000);

  Serial.print(F("Display initialized: "));
  Serial.print(SCREEN_WIDTH);
  Serial.print(F("x"));
  Serial.println(SCREEN_HEIGHT);
}

void initLVGL() {
  lv_init();

  // Create display buffer
  static lv_disp_draw_buf_t draw_buf;
  static lv_color_t buf[SCREEN_WIDTH * 10];
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_WIDTH * 10);

  // Initialize display driver
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = SCREEN_WIDTH;
  disp_drv.ver_res = SCREEN_HEIGHT;
  disp_drv.flush_cb = [](lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
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

  // Initialize touch driver (optional - depends on CrowPanel touch controller)
  // TODO: Add touch driver initialization based on your specific CrowPanel model

  Serial.println(F("LVGL initialized"));
}

// ============= UI CREATION =============
void createFloorGrid() {
  screen = lv_scr_act();
  lv_obj_set_style_bg_color(screen, COLOR_BG, 0);

  // Grid configuration: 8 columns x 5 rows = 40 floors
  const int COLS = 8;
  const int ROWS = 5;
  const int GRID_MARGIN_X = 24;
  const int GRID_MARGIN_Y = 20;
  const int CELL_SPACING = 12;
  const int GRID_HEIGHT = SCREEN_HEIGHT - GRID_MARGIN_Y * 2 - 40;
  const int CELL_WIDTH = (SCREEN_WIDTH - GRID_MARGIN_X * 2 - (COLS - 1) * CELL_SPACING) / COLS;
  const int CELL_HEIGHT = (GRID_HEIGHT - (ROWS - 1) * CELL_SPACING) / ROWS;
  const int IND_SIZE = 14;  // Indicator size

  // Create floor cells (top to bottom = floor 40 to floor 1)
  for (uint8_t row = 0; row < ROWS; row++) {
    for (uint8_t col = 0; col < COLS; col++) {
      uint8_t floor = TOTAL_FLOORS - (row * COLS) - (COLS - 1 - col);

      if (floor < 1 || floor > TOTAL_FLOORS) continue;

      int x = GRID_MARGIN_X + col * (CELL_WIDTH + CELL_SPACING);
      int y = GRID_MARGIN_Y + row * (CELL_HEIGHT + CELL_SPACING);

      // Create floor container
      floorGrid[floor] = lv_obj_create(screen);
      lv_obj_remove_style_all(floorGrid[floor]);
      lv_obj_set_size(floorGrid[floor], CELL_WIDTH, CELL_HEIGHT);
      lv_obj_set_pos(floorGrid[floor], x, y);
      lv_obj_set_style_border_width(floorGrid[floor], 2, 0);
      lv_obj_set_style_border_color(floorGrid[floor], COLOR_BORDER, 0);
      lv_obj_set_style_bg_color(floorGrid[floor], COLOR_CARD_BG, 0);
      lv_obj_set_style_bg_opa(floorGrid[floor], LV_OPA_COVER, 0);
      lv_obj_set_style_radius(floorGrid[floor], 10, 0);
      lv_obj_set_style_pad_hor(floorGrid[floor], 6, 0);
      lv_obj_set_style_pad_top(floorGrid[floor], 4, 0);
      lv_obj_set_style_pad_bottom(floorGrid[floor], 6, 0);
      lv_obj_clear_flag(floorGrid[floor], LV_OBJ_FLAG_SCROLLABLE);
      lv_obj_set_style_shadow_width(floorGrid[floor], 12, 0);
      lv_obj_set_style_shadow_ofs_y(floorGrid[floor], 4, 0);
      lv_obj_set_style_shadow_color(floorGrid[floor], lv_color_hex(0x0c111d), 0);

      // Add touch callback
      lv_obj_add_event_cb(floorGrid[floor], floorTouchCallback, LV_EVENT_CLICKED, (void*)(intptr_t)floor);
      lv_obj_add_flag(floorGrid[floor], LV_OBJ_FLAG_CLICKABLE);

      // Floor number label
      floorLabels[floor] = lv_label_create(floorGrid[floor]);
      lv_label_set_text_fmt(floorLabels[floor], "%02d", floor);
      lv_obj_set_style_text_font(floorLabels[floor], &lv_font_montserrat_28, 0);
      lv_obj_set_style_text_color(floorLabels[floor], COLOR_TEXT, 0);
      lv_obj_align(floorLabels[floor], LV_ALIGN_TOP_MID, 0, 0);

      // UP indicator (green circle)
      upIndicators[floor] = lv_obj_create(floorGrid[floor]);
      lv_obj_set_size(upIndicators[floor], IND_SIZE, IND_SIZE);
      lv_obj_set_style_radius(upIndicators[floor], LV_RADIUS_CIRCLE, 0);
      lv_obj_set_style_bg_color(upIndicators[floor], COLOR_INACTIVE, 0);
      lv_obj_set_style_border_width(upIndicators[floor], 0, 0);
      lv_obj_align(upIndicators[floor], LV_ALIGN_BOTTOM_LEFT, 8, -8);

      // LOAD indicator (yellow square)
      loadIndicators[floor] = lv_obj_create(floorGrid[floor]);
      lv_obj_set_size(loadIndicators[floor], IND_SIZE, IND_SIZE);
      lv_obj_set_style_radius(loadIndicators[floor], 0, 0);
      lv_obj_set_style_bg_color(loadIndicators[floor], COLOR_INACTIVE, 0);
      lv_obj_set_style_border_width(loadIndicators[floor], 0, 0);
      lv_obj_align(loadIndicators[floor], LV_ALIGN_BOTTOM_MID, 0, -8);

      // DOWN indicator (red circle)
      downIndicators[floor] = lv_obj_create(floorGrid[floor]);
      lv_obj_set_size(downIndicators[floor], IND_SIZE, IND_SIZE);
      lv_obj_set_style_radius(downIndicators[floor], LV_RADIUS_CIRCLE, 0);
      lv_obj_set_style_bg_color(downIndicators[floor], COLOR_INACTIVE, 0);
      lv_obj_set_style_border_width(downIndicators[floor], 0, 0);
      lv_obj_align(downIndicators[floor], LV_ALIGN_BOTTOM_RIGHT, -8, -8);
    }
  }

  // Status bar at bottom (if space available)
  statusLabel = lv_label_create(screen);
  lv_label_set_text(statusLabel, "Ready");
  lv_obj_set_style_text_color(statusLabel, lv_color_hex(0xA5B4FC), 0);
  lv_obj_set_style_text_font(statusLabel, &lv_font_montserrat_22, 0);
  lv_obj_align(statusLabel, LV_ALIGN_BOTTOM_LEFT, 15, -10);

  Serial.println(F("Floor grid created"));
}

// ============= DISPLAY UPDATES =============
void updateFloorDisplay(uint8_t floor) {
  if (floor < 1 || floor > TOTAL_FLOORS) return;

  // Update UP indicator
  if (floorStates[floor].upActive) {
    lv_obj_set_style_bg_color(upIndicators[floor], COLOR_UP, 0);
  } else {
    lv_obj_set_style_bg_color(upIndicators[floor], COLOR_INACTIVE, 0);
  }

  // Update DOWN indicator
  if (floorStates[floor].downActive) {
    lv_obj_set_style_bg_color(downIndicators[floor], COLOR_DOWN, 0);
  } else {
    lv_obj_set_style_bg_color(downIndicators[floor], COLOR_INACTIVE, 0);
  }

  // Update LOAD indicator
  if (floorStates[floor].loadActive) {
    lv_obj_set_style_bg_color(loadIndicators[floor], COLOR_LOAD, 0);
  } else {
    lv_obj_set_style_bg_color(loadIndicators[floor], COLOR_INACTIVE, 0);
  }
}

void highlightCurrentFloor() {
  for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
    if (floorGrid[f] != NULL) {
      lv_obj_set_style_border_color(floorGrid[f], COLOR_BORDER, 0);
      lv_obj_set_style_bg_color(floorGrid[f], COLOR_CARD_BG, 0);
      lv_obj_set_style_border_width(floorGrid[f], 2, 0);
      lv_obj_set_style_shadow_color(floorGrid[f], lv_color_hex(0x0c111d), 0);
    }
  }

  if (currentElevatorFloor >= 1 && currentElevatorFloor <= TOTAL_FLOORS) {
    lv_obj_set_style_border_color(floorGrid[currentElevatorFloor], COLOR_CURRENT, 0);
    lv_obj_set_style_border_width(floorGrid[currentElevatorFloor], 4, 0);
    lv_obj_set_style_bg_color(floorGrid[currentElevatorFloor], lv_color_hex(0xE3F2FD), 0);
    lv_obj_set_style_shadow_color(floorGrid[currentElevatorFloor], COLOR_CURRENT, 0);
  }
}

void initBacklightControl() {
  ioBus.begin(15, 16, 400000);
  ioExpander.attach(ioBus);
  ioExpander.setDeviceAddress(0x18);
  ioExpander.config(TCA9534::Config::OUT);
  ioExpander.output(0xFF);  // drive all pins high (no peripherals pulled low)

  // Backlight control on pin 1 (active high)
  ioExpander.output(1, TCA9534::Level::H);

  // Touch reset on pin 2 (active low pulse)
  ioExpander.output(2, TCA9534::Level::L);
  delay(20);
  ioExpander.output(2, TCA9534::Level::H);
  delay(50);

  stcSetBacklight(8);       // near-max brightness (0 = max, 245 = min)
  stcDisableBuzzer();       // ensure onboard buzzer is muted

  Serial.println(F("Backlight enabled via IO expander"));
}

bool stcSend(uint8_t value) {
  ioBus.beginTransmission(STC_BACKLIGHT_ADDR);
  ioBus.write(value);
  bool ok = (ioBus.endTransmission() == 0);
  if (!ok) {
    Serial.print(F("STC I2C write failed for value "));
    Serial.println(value);
  }
  return ok;
}

void stcSetBacklight(uint8_t level) {
  if (level > 245) level = 245;
  stcSend(level);
}

void stcDisableBuzzer() {
  stcSend(STC_CMD_BUZZER_OFF);
}

bool probeGateway() {
  Wire.beginTransmission(I2C_MASTER_ADDRESS);
  return Wire.endTransmission(true) == 0;
}

// ============= I2C COMMUNICATION =============
void requestDataFromGateway() {
  if (!gatewayAvailable) {
    return;
  }
  // Request data from gateway
  Wire.requestFrom(I2C_MASTER_ADDRESS, sizeof(DisplayPacket));

  if (Wire.available() >= sizeof(DisplayPacket)) {
    DisplayPacket pkt;
    Wire.readBytes((uint8_t*)&pkt, sizeof(DisplayPacket));

    // Check if this is elevator position update
    if (pkt.status & 0x80) {
      currentElevatorFloor = pkt.floor;
      return;
    }

    // Normal floor update
    if (pkt.floor >= 1 && pkt.floor <= TOTAL_FLOORS) {
      floorStates[pkt.floor].upActive = (pkt.status & 0x01);
      floorStates[pkt.floor].downActive = (pkt.status & 0x02);
      floorStates[pkt.floor].loadActive = (pkt.status & 0x04);
      floorStates[pkt.floor].rssi = pkt.rssi;
      floorStates[pkt.floor].lastUpdate = millis();

      // Update status label
      char statusText[64];
      snprintf(statusText, sizeof(statusText), "Floor %d | RSSI: %d dBm | Elevator: %d",
               pkt.floor, pkt.rssi, currentElevatorFloor);
      lv_label_set_text(statusLabel, statusText);
    }
  }
}

void sendClearCommand(uint8_t floor, uint8_t callType) {
  Wire.beginTransmission(I2C_MASTER_ADDRESS);
  Wire.write(floor);
  Wire.write(0x20);  // CMD_CLEAR
  Wire.write(callType);
  Wire.endTransmission();

  Serial.print(F("Clear sent: Floor "));
  Serial.print(floor);
  Serial.print(F(" Type "));
  Serial.println(callType);
}

// ============= TOUCH CALLBACKS =============
void floorTouchCallback(lv_event_t *e) {
  uint8_t floor = (uint8_t)(intptr_t)lv_event_get_user_data(e);

  Serial.print(F("Floor "));
  Serial.print(floor);
  Serial.println(F(" touched"));

  // Clear all active calls for this floor
  if (floorStates[floor].upActive || floorStates[floor].downActive || floorStates[floor].loadActive) {
    sendClearCommand(floor, 0xFF);  // Clear all

    // Update local state
    floorStates[floor].upActive = false;
    floorStates[floor].downActive = false;
    floorStates[floor].loadActive = false;

    updateFloorDisplay(floor);
  }
}
