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
#include <TFT_eSPI.h>
#include <Wire.h>

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

// Global objects
TFT_eSPI tft = TFT_eSPI();
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
lv_color_t COLOR_UP = lv_color_hex(0x00FF00);      // Green
lv_color_t COLOR_DOWN = lv_color_hex(0xFF0000);    // Red
lv_color_t COLOR_LOAD = lv_color_hex(0xFFFF00);    // Yellow
lv_color_t COLOR_INACTIVE = lv_color_hex(0x404040); // Dark gray
lv_color_t COLOR_CURRENT = lv_color_hex(0x0000FF);  // Blue
lv_color_t COLOR_BG = lv_color_hex(0x000000);      // Black

// Function prototypes
void initDisplay();
void initLVGL();
void createFloorGrid();
void updateFloorDisplay(uint8_t floor);
void highlightCurrentFloor();
void requestDataFromGateway();
void sendClearCommand(uint8_t floor, uint8_t callType);
void floorTouchCallback(lv_event_t *e);
static void lv_tick_handler();

// Timing
uint32_t lastI2CRequest = 0;
uint32_t lastDisplayRefresh = 0;

// ============= SETUP =============
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("========================================"));
  Serial.println(F("CrowPanel Display v2.0"));
  Serial.println(F("40-Floor Elevator Operator Interface"));
  Serial.println(F("========================================"));

  // Initialize I2C as master
  Wire.begin();
  Wire.setClock(100000);  // 100kHz

  // Initialize display
  initDisplay();

  // Initialize LVGL
  initLVGL();

  // Create UI
  createFloorGrid();

  Serial.println(F("Display ready!"));
}

// ============= MAIN LOOP =============
void loop() {
  lv_timer_handler();  // LVGL task handler

  // Request data from gateway every 200ms
  if (millis() - lastI2CRequest > 200) {
    requestDataFromGateway();
    lastI2CRequest = millis();
  }

  // Refresh display every 100ms
  if (millis() - lastDisplayRefresh > 100) {
    for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
      if (millis() - floorStates[f].lastUpdate < 10000) {  // Only if recent update
        updateFloorDisplay(f);
      }
    }
    highlightCurrentFloor();
    lastDisplayRefresh = millis();
  }

  delay(5);
}

// ============= DISPLAY INITIALIZATION =============
void initDisplay() {
  tft.begin();
  tft.setRotation(1);  // Landscape
  tft.fillScreen(TFT_BLACK);

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
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, true);
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
  const int CELL_WIDTH = SCREEN_WIDTH / COLS;
  const int CELL_HEIGHT = SCREEN_HEIGHT / ROWS;
  const int IND_SIZE = 12;  // Indicator size

  // Create floor cells (top to bottom = floor 40 to floor 1)
  for (uint8_t row = 0; row < ROWS; row++) {
    for (uint8_t col = 0; col < COLS; col++) {
      uint8_t floor = 40 - (row * COLS + col);

      if (floor < 1 || floor > TOTAL_FLOORS) continue;

      int x = col * CELL_WIDTH;
      int y = row * CELL_HEIGHT;

      // Create floor container
      floorGrid[floor] = lv_obj_create(screen);
      lv_obj_set_size(floorGrid[floor], CELL_WIDTH - 4, CELL_HEIGHT - 4);
      lv_obj_set_pos(floorGrid[floor], x + 2, y + 2);
      lv_obj_set_style_border_width(floorGrid[floor], 2, 0);
      lv_obj_set_style_border_color(floorGrid[floor], lv_color_hex(0x404040), 0);
      lv_obj_set_style_bg_color(floorGrid[floor], lv_color_hex(0x202020), 0);

      // Add touch callback
      lv_obj_add_event_cb(floorGrid[floor], floorTouchCallback, LV_EVENT_CLICKED, (void*)(intptr_t)floor);
      lv_obj_add_flag(floorGrid[floor], LV_OBJ_FLAG_CLICKABLE);

      // Floor number label
      floorLabels[floor] = lv_label_create(floorGrid[floor]);
      lv_label_set_text_fmt(floorLabels[floor], "%d", floor);
      lv_obj_set_style_text_font(floorLabels[floor], &lv_font_montserrat_24, 0);
      lv_obj_set_style_text_color(floorLabels[floor], lv_color_hex(0xFFFFFF), 0);
      lv_obj_align(floorLabels[floor], LV_ALIGN_TOP_MID, 0, 5);

      // UP indicator (green circle)
      upIndicators[floor] = lv_obj_create(floorGrid[floor]);
      lv_obj_set_size(upIndicators[floor], IND_SIZE, IND_SIZE);
      lv_obj_set_style_radius(upIndicators[floor], LV_RADIUS_CIRCLE, 0);
      lv_obj_set_style_bg_color(upIndicators[floor], COLOR_INACTIVE, 0);
      lv_obj_set_style_border_width(upIndicators[floor], 0, 0);
      lv_obj_set_pos(upIndicators[floor], 10, CELL_HEIGHT - 25);

      // LOAD indicator (yellow square)
      loadIndicators[floor] = lv_obj_create(floorGrid[floor]);
      lv_obj_set_size(loadIndicators[floor], IND_SIZE, IND_SIZE);
      lv_obj_set_style_radius(loadIndicators[floor], 0, 0);
      lv_obj_set_style_bg_color(loadIndicators[floor], COLOR_INACTIVE, 0);
      lv_obj_set_style_border_width(loadIndicators[floor], 0, 0);
      lv_obj_set_pos(loadIndicators[floor], (CELL_WIDTH / 2) - (IND_SIZE / 2), CELL_HEIGHT - 25);

      // DOWN indicator (red circle)
      downIndicators[floor] = lv_obj_create(floorGrid[floor]);
      lv_obj_set_size(downIndicators[floor], IND_SIZE, IND_SIZE);
      lv_obj_set_style_radius(downIndicators[floor], LV_RADIUS_CIRCLE, 0);
      lv_obj_set_style_bg_color(downIndicators[floor], COLOR_INACTIVE, 0);
      lv_obj_set_style_border_width(downIndicators[floor], 0, 0);
      lv_obj_set_pos(downIndicators[floor], CELL_WIDTH - 22, CELL_HEIGHT - 25);
    }
  }

  // Status bar at bottom (if space available)
  statusLabel = lv_label_create(screen);
  lv_label_set_text(statusLabel, "Ready");
  lv_obj_set_style_text_color(statusLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(statusLabel, LV_ALIGN_BOTTOM_LEFT, 10, -5);

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
  // Remove highlight from all floors
  for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
    if (floorGrid[f] != NULL) {
      lv_obj_set_style_border_color(floorGrid[f], lv_color_hex(0x404040), 0);
      lv_obj_set_style_border_width(floorGrid[f], 2, 0);
    }
  }

  // Highlight current floor
  if (currentElevatorFloor >= 1 && currentElevatorFloor <= TOTAL_FLOORS) {
    lv_obj_set_style_border_color(floorGrid[currentElevatorFloor], COLOR_CURRENT, 0);
    lv_obj_set_style_border_width(floorGrid[currentElevatorFloor], 4, 0);
  }
}

// ============= I2C COMMUNICATION =============
void requestDataFromGateway() {
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
