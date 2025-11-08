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

using lgfx::v1::LGFX_Sprite;
using lgfx::v1::fonts::Font2;
using lgfx::v1::fonts::Font4;
using lgfx::v1::textdatum_t;

enum class ThemeVariant : uint8_t { DarkGlass = 0, Blueprint, HighContrast };

struct ThemePalette {
  const char *name;
  lv_color_t bgPrimary;
  lv_color_t bgSecondary;
  lv_color_t cardBg;
  lv_color_t cardBorder;
  lv_color_t textPrimary;
  lv_color_t textSecondary;
  lv_color_t indicatorUp;
  lv_color_t indicatorDown;
  lv_color_t indicatorLoad;
  lv_color_t indicatorInactive;
  lv_color_t elevatorHighlight;
  lv_color_t shadowColor;
  const lv_font_t *headingFont;
  const lv_font_t *floorFont;
  const lv_font_t *statusFont;
  const lv_font_t *legendFont;
};

static const ThemePalette THEME_DARK_GLASS = {
    "Dark Glass",
    lv_color_hex(0x050C1C),
    lv_color_hex(0x111A32),
    lv_color_hex(0x10192C),
    lv_color_hex(0x2A395B),
    lv_color_hex(0xEEF4FF),
    lv_color_hex(0xA5B4FC),
    lv_color_hex(0x2ECC71),
    lv_color_hex(0xFF5F6D),
    lv_color_hex(0xF8C537),
    lv_color_hex(0x253147),
    lv_color_hex(0x4FC3F7),
    lv_color_hex(0x000000),
    &lv_font_montserrat_28,
    &lv_font_montserrat_32,
    &lv_font_montserrat_20,
    &lv_font_montserrat_18};

static const ThemePalette THEME_BLUEPRINT = {
    "Blueprint",
    lv_color_hex(0x011837),
    lv_color_hex(0x043F78),
    lv_color_hex(0x0A2A4F),
    lv_color_hex(0x1E90FF),
    lv_color_hex(0xE0F2FF),
    lv_color_hex(0x9AD4FF),
    lv_color_hex(0x7CFC00),
    lv_color_hex(0xFF6B6B),
    lv_color_hex(0xFFD166),
    lv_color_hex(0x1D3D63),
    lv_color_hex(0x64B5F6),
    lv_color_hex(0x061C3A),
    &lv_font_montserrat_28,
    &lv_font_montserrat_32,
    &lv_font_montserrat_20,
    &lv_font_montserrat_18};

static const ThemePalette THEME_HIGH_CONTRAST = {
    "High Contrast",
    lv_color_hex(0x101010),
    lv_color_hex(0x1F1F1F),
    lv_color_hex(0xF5F5F5),
    lv_color_hex(0x2E2E2E),
    lv_color_hex(0x111111),
    lv_color_hex(0x3D3D3D),
    lv_color_hex(0x2ECC71),
    lv_color_hex(0xC62828),
    lv_color_hex(0xF9A825),
    lv_color_hex(0xC4C4C4),
    lv_color_hex(0x1565C0),
    lv_color_hex(0x000000),
    &lv_font_montserrat_32,
    &lv_font_montserrat_32,
    &lv_font_montserrat_20,
    &lv_font_montserrat_18};

constexpr ThemeVariant DEFAULT_THEME = ThemeVariant::HighContrast;
const ThemePalette *activeTheme = &THEME_HIGH_CONTRAST;
ThemeVariant currentTheme = DEFAULT_THEME;

const lv_color_t COLOR_SCREEN_BG = lv_color_black();
const lv_color_t COLOR_TEXT_MAIN = lv_color_hex(0xFFFFFF);
const lv_color_t COLOR_BAR_UP = lv_color_hex(0x4CAF50);
const lv_color_t COLOR_BAR_LOAD = lv_color_hex(0xFFC107);
const lv_color_t COLOR_BAR_DOWN = lv_color_hex(0xFF5252);
const lv_color_t COLOR_BAR_INACTIVE = lv_color_hex(0x2A2A2A);
const lv_color_t COLOR_HIGHLIGHT = lv_color_hex(0x1E88E5);

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
constexpr uint8_t BUZZER_PIN = 8;

// Global objects
LGFX tft;
TwoWire ioBus = TwoWire(1);
TCA9534 ioExpander;
LGFX_Sprite textSprite(&tft);
FloorState floorStates[TOTAL_FLOORS + 1];
uint8_t currentElevatorFloor = 20;

constexpr int ROW_HEIGHT = 18;
constexpr int ROW_SPACING = 2;
constexpr int HEADER_HEIGHT = 70;
constexpr int ROW_LEFT = 12;
constexpr int BAR_WIDTH = 80;
constexpr int BAR_HEIGHT = 8;
constexpr int BAR_SPACING = 8;

LGFX_Sprite textSprite(&tft);
bool screenDirty = true;
char statusLine[64] = "Awaiting data...";

// Function prototypes
void initDisplay();
void initLVGL();
void renderStatusScreen();
void drawFloorRow(uint8_t floor, int y);
void markDisplayDirty();
void requestDataFromGateway();
void sendClearCommand(uint8_t floor, uint8_t callType);
void initBacklightControl();
bool stcSend(uint8_t value);
void stcSetBacklight(uint8_t level);
void stcDisableBuzzer();
void muteHardwareBuzzer();
void runLovyanSimpleDemo();
void applyTheme(ThemeVariant variant);
const ThemePalette *paletteForVariant(ThemeVariant variant);
void rebuildUI();
void resetFloorWidgets();
void handleSerialCommands();
void cycleTheme(bool forward = true);

#if LV_USE_LOG
void lvglLogPrinter(const char *buf);
#endif

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

  applyTheme(DEFAULT_THEME);
  muteHardwareBuzzer();
  initBacklightControl();

  // Initialize I2C as master
  Wire.begin(17, 18);  // CrowPanel I2C pins
  Wire.setClock(100000);  // 100kHz

  // Initialize display
  initDisplay();
  runLovyanSimpleDemo();

  // Initialize LVGL
  initLVGL();

  screenDirty = true;
  renderStatusScreen();
  screenDirty = false;

  uint32_t now = millis();
  lastTickUpdate = now;
  lastGatewayProbe = now;

  Serial.println(F("Display ready!"));
}

// ============= MAIN LOOP =============
void loop() {
  handleSerialCommands();

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

  if (screenDirty) {
    renderStatusScreen();
    screenDirty = false;
  }

  delay(5);
}

// ============= DISPLAY INITIALIZATION =============
void initDisplay() {
  tft.init();
  tft.setRotation(1);  // Portrait orientation
  tft.setColorDepth(24);
  tft.setSwapBytes(true);
  tft.fillScreen(0x0000);

  Serial.print(F("Display initialized: "));
  Serial.print(SCREEN_WIDTH);
  Serial.print(F("x"));
  Serial.println(SCREEN_HEIGHT);
}

void initLVGL() {
  lv_init();
#if LV_USE_LOG
  lv_log_register_print_cb(lvglLogPrinter);
#endif

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
  resetFloorWidgets();

  lv_obj_set_style_bg_color(screen, COLOR_SCREEN_BG, 0);
  lv_obj_set_style_bg_grad_color(screen, COLOR_SCREEN_BG, 0);
  lv_obj_set_style_bg_grad_dir(screen, LV_GRAD_DIR_VER, 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);

  lv_obj_t *titleLabel = lv_label_create(screen);
  lv_label_set_text(titleLabel, "FLOOR CALLS");
  lv_obj_set_style_text_font(titleLabel, activeTheme->headingFont, 0);
  lv_obj_set_style_text_color(titleLabel, COLOR_TEXT_MAIN, 0);
  lv_obj_align(titleLabel, LV_ALIGN_TOP_MID, 0, 4);

  floorListContainer = lv_obj_create(screen);
  lv_obj_remove_style_all(floorListContainer);
  lv_obj_set_size(floorListContainer, SCREEN_WIDTH - 20, SCREEN_HEIGHT - 60);
  lv_obj_align(floorListContainer, LV_ALIGN_TOP_MID, 0, 30);
  lv_obj_set_style_bg_opa(floorListContainer, LV_OPA_TRANSP, 0);
  lv_obj_set_style_pad_all(floorListContainer, 0, 0);
  lv_obj_set_style_pad_row(floorListContainer, 1, 0);
  lv_obj_set_flex_flow(floorListContainer, LV_FLEX_FLOW_COLUMN);
  lv_obj_clear_flag(floorListContainer, LV_OBJ_FLAG_SCROLLABLE);

  const lv_font_t *lineFont = &lv_font_unscii_8;

  for (int floor = TOTAL_FLOORS; floor >= 1; floor--) {
    floorRows[floor] = lv_obj_create(floorListContainer);
    lv_obj_remove_style_all(floorRows[floor]);
    lv_obj_set_width(floorRows[floor], lv_pct(100));
    lv_obj_set_height(floorRows[floor], 18);
    lv_obj_set_style_pad_left(floorRows[floor], 6, 0);
    lv_obj_set_style_pad_right(floorRows[floor], 6, 0);
    lv_obj_set_style_pad_column(floorRows[floor], 8, 0);
    lv_obj_set_style_bg_opa(floorRows[floor], LV_OPA_TRANSP, 0);
    lv_obj_set_flex_flow(floorRows[floor], LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(floorRows[floor], LV_FLEX_ALIGN_START,
                          LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_event_cb(floorRows[floor], floorTouchCallback, LV_EVENT_CLICKED,
                        (void *)(intptr_t)floor);
    lv_obj_add_flag(floorRows[floor], LV_OBJ_FLAG_CLICKABLE);

    floorLabels[floor] = lv_label_create(floorRows[floor]);
    lv_label_set_text(floorLabels[floor], "F00");
    lv_obj_set_style_text_font(floorLabels[floor], lineFont, 0);
    lv_obj_set_style_text_color(floorLabels[floor], COLOR_TEXT_MAIN, 0);
    lv_obj_set_style_bg_opa(floorLabels[floor], LV_OPA_TRANSP, 0);
    lv_obj_set_flex_grow(floorLabels[floor], 1);

    auto createBar = [&](lv_color_t inactiveColor) -> lv_obj_t * {
      lv_obj_t *bar = lv_obj_create(floorRows[floor]);
      lv_obj_remove_style_all(bar);
      lv_obj_set_size(bar, 60, 6);
      lv_obj_set_style_radius(bar, 3, 0);
      lv_obj_set_style_bg_color(bar, inactiveColor, 0);
      lv_obj_set_style_bg_opa(bar, LV_OPA_COVER, 0);
      return bar;
    };

    barUp[floor] = createBar(COLOR_BAR_INACTIVE);
    barLoad[floor] = createBar(COLOR_BAR_INACTIVE);
    barDown[floor] = createBar(COLOR_BAR_INACTIVE);

    updateFloorDisplay(floor);
  }

  statusLabel = lv_label_create(screen);
  lv_label_set_text(statusLabel, "Awaiting data...");
  lv_obj_set_style_text_color(statusLabel, COLOR_TEXT_MAIN, 0);
  lv_obj_set_style_text_font(statusLabel, activeTheme->statusFont, 0);
  lv_obj_align(statusLabel, LV_ALIGN_BOTTOM_LEFT, 6, -6);

  Serial.println(F("Floor grid created"));
}

// ============= DISPLAY UPDATES =============
void updateFloorDisplay(uint8_t floor) {
  if (floor < 1 || floor > TOTAL_FLOORS) return;
  if (!floorLabels[floor]) return;

  char line[24];
  snprintf(line, sizeof(line), "F%02d", floor);
  lv_label_set_text(floorLabels[floor], line);

  if (barUp[floor]) {
    lv_obj_set_style_bg_color(barUp[floor],
                              floorStates[floor].upActive ? COLOR_BAR_UP : COLOR_BAR_INACTIVE, 0);
  }
  if (barLoad[floor]) {
    lv_obj_set_style_bg_color(barLoad[floor],
                              floorStates[floor].loadActive ? COLOR_BAR_LOAD : COLOR_BAR_INACTIVE, 0);
  }
  if (barDown[floor]) {
    lv_obj_set_style_bg_color(barDown[floor],
                              floorStates[floor].downActive ? COLOR_BAR_DOWN : COLOR_BAR_INACTIVE, 0);
  }
}

void highlightCurrentFloor() {
  for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
    if (floorRows[f] != NULL) {
      lv_obj_set_style_bg_opa(floorRows[f], LV_OPA_TRANSP, 0);
      lv_obj_set_style_text_color(floorLabels[f], COLOR_TEXT_MAIN, 0);
    }
  }

  if (currentElevatorFloor >= 1 && currentElevatorFloor <= TOTAL_FLOORS) {
    if (floorRows[currentElevatorFloor]) {
      lv_obj_set_style_bg_color(floorRows[currentElevatorFloor],
                                COLOR_HIGHLIGHT, 0);
      lv_obj_set_style_bg_opa(floorRows[currentElevatorFloor], LV_OPA_40, 0);
      lv_obj_set_style_text_color(floorLabels[currentElevatorFloor],
                                  COLOR_TEXT_MAIN, 0);
    }
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

void muteHardwareBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void runLovyanSimpleDemo() {
  Serial.println(F("Rendering LovyanGFX full-screen test..."));
  const int w = tft.width();
  const int h = tft.height();

  // Gradient background
  for (int y = 0; y < h; y++) {
    float t = static_cast<float>(y) / h;
    uint32_t color = tft.color888(
        static_cast<uint8_t>(255 * t),
        static_cast<uint8_t>(100 + 100 * sinf(t * 3.14f)),
        static_cast<uint8_t>(255 * (1.0f - t)));
    tft.drawFastHLine(0, y, w, color);
  }

  // Hue bars
  const int barCount = 12;
  const int barWidth = w / barCount;
  for (int i = 0; i < barCount; i++) {
    float t = static_cast<float>(i) / (barCount - 1);
    uint8_t r = static_cast<uint8_t>(255 * t);
    uint8_t g = static_cast<uint8_t>(255 * (1.0f - t));
    uint8_t b = static_cast<uint8_t>(128 + 127 * sinf(t * 6.283f));
    tft.fillRect(i * barWidth, h / 2 - 60, barWidth - 2, 120, tft.color888(r, g, b));
  }

  // Grid overlay
  tft.setColor(0xFFFFFFU);
  for (int y = 0; y < h; y += 40) {
    tft.drawFastHLine(0, y, w);
  }
  for (int x = 0; x < w; x += 40) {
    tft.drawFastVLine(x, 0, h);
  }

  // Anti-aliased text via sprite
  const int spriteWidth = w - 80;
  const int spriteHeight = 100;
  textSprite.setColorDepth(24);
  textSprite.createSprite(spriteWidth, spriteHeight);
  textSprite.fillScreen(tft.color888(0, 0, 0));
  textSprite.setTextColor(0xFFFFFFU, tft.color888(0, 0, 0));
  textSprite.setFont(&Font4);
  textSprite.setTextDatum(textdatum_t::top_center);
  textSprite.drawString("LovyanGFX Full-Screen Test", spriteWidth / 2, 8);
  textSprite.setFont(&Font2);
  textSprite.drawString(String(w) + " x " + String(h) + " @24-bit", spriteWidth / 2, 64);
  textSprite.pushSprite((w - spriteWidth) / 2, 24, tft.color888(0, 0, 0));
  textSprite.deleteSprite();

  delay(60000);
  tft.fillScreen(0x0000);
}

const ThemePalette *paletteForVariant(ThemeVariant variant) {
  switch (variant) {
    case ThemeVariant::DarkGlass:
      return &THEME_DARK_GLASS;
    case ThemeVariant::Blueprint:
      return &THEME_BLUEPRINT;
    case ThemeVariant::HighContrast:
      return &THEME_HIGH_CONTRAST;
    default:
      return &THEME_DARK_GLASS;
  }
}

void applyTheme(ThemeVariant variant) {
  const ThemePalette *palette = paletteForVariant(variant);
  if (palette == nullptr) {
    return;
  }
  currentTheme = variant;
  activeTheme = palette;
  Serial.print(F("Applied theme: "));
  Serial.println(activeTheme->name);
}

void resetFloorWidgets() {
  for (uint8_t f = 0; f <= TOTAL_FLOORS; f++) {
    floorRows[f] = nullptr;
    floorLabels[f] = nullptr;
    barUp[f] = nullptr;
    barLoad[f] = nullptr;
    barDown[f] = nullptr;
  }
  statusLabel = nullptr;
  floorListContainer = nullptr;
}

void rebuildUI() {
  lv_obj_clean(lv_scr_act());
  createFloorGrid();
  for (uint8_t f = 1; f <= TOTAL_FLOORS; f++) {
    updateFloorDisplay(f);
  }
  highlightCurrentFloor();
}

#if LV_USE_LOG
void lvglLogPrinter(const char *buf) {
  if (!buf) return;
  Serial.print(F("[LVGL] "));
  Serial.println(buf);
}
#endif

void cycleTheme(bool forward) {
  constexpr uint8_t themeCount = 3;
  int8_t idx = static_cast<int8_t>(currentTheme);
  idx += forward ? 1 : -1;
  if (idx >= static_cast<int8_t>(themeCount)) idx = 0;
  if (idx < 0) idx = themeCount - 1;
  applyTheme(static_cast<ThemeVariant>(idx));
  rebuildUI();
}

void handleSerialCommands() {
  while (Serial.available()) {
    char c = static_cast<char>(Serial.read());
    if (c == '\n' || c == '\r') {
      continue;
    }

    switch (c) {
      case 't':
      case 'T':
        cycleTheme(true);
        break;
      case 'r':
      case 'R':
        cycleTheme(false);
        break;
      case '1':
        applyTheme(ThemeVariant::DarkGlass);
        rebuildUI();
        break;
      case '2':
        applyTheme(ThemeVariant::Blueprint);
        rebuildUI();
        break;
      case '3':
        applyTheme(ThemeVariant::HighContrast);
        rebuildUI();
        break;
      default:
        Serial.print(F("Unknown theme command: "));
        Serial.println(c);
        break;
    }
  }
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
      if (statusLabel != nullptr) {
        lv_label_set_text(statusLabel, statusText);
      }
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
