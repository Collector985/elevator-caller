#include "elevator_ui.h"

#include <Arduino.h>
#include <lvgl.h>
#include <cstring>
#include <vector>

#include "ui_styles.h"

namespace {

constexpr uint8_t kMinFloor = 1;
#ifdef TOTAL_FLOORS
constexpr uint8_t kMaxFloor = TOTAL_FLOORS;
#else
constexpr uint8_t kMaxFloor = 30;
#endif
constexpr uint8_t kTopDisplayFloor = 34;
constexpr uint8_t kParkFloorCount = 3;
constexpr uint8_t kFirstParkFloor = kTopDisplayFloor + 1;
constexpr const char *kParkLabels[kParkFloorCount] = {"P3", "P2", "P1"};

enum CallMask : uint8_t {
  CALL_UP = 0x01,
  CALL_DOWN = 0x02,
  CALL_LOAD = 0x04,
};

struct FloorWidgets {
  lv_obj_t *card = nullptr;
  lv_obj_t *label = nullptr;
  lv_obj_t *btnUp = nullptr;
  lv_obj_t *btnDown = nullptr;
};

static lv_obj_t *shaft_screen = nullptr;
static lv_obj_t *control_screen = nullptr;
constexpr uint8_t kMaxNavButtons = 4;

struct NavConfig {
  const char *label;
  uint8_t action;
};

static lv_obj_t *shaft_nav_btns[kMaxNavButtons] = {nullptr};
static lv_obj_t *control_nav_btns[kMaxNavButtons] = {nullptr};

static constexpr NavConfig kShaftNavConfig[] = {
    {"SHAFT", 0},
    {"GRID", 1},
    {"CONTROL", 2},
};

static constexpr NavConfig kControlNavConfig[] = {
    {"SHAFT", 0},
    {"BACK", 3},
    {"GRID", 1},
    {"CONTROL", 2},
};
static FloorWidgets floor_widgets[kMaxFloor + 1];
static ElevatorCallHandler call_handler = nullptr;
static uint8_t current_floor = 1;
static uint8_t active_view = 0;  // 0=SHAFT, 2=CONTROL

// Control screen widgets
static lv_obj_t *gateway_status_label = nullptr;
static lv_obj_t *current_floor_label = nullptr;
static lv_obj_t *active_calls_label = nullptr;
static lv_obj_t *rssi_label = nullptr;
static lv_obj_t *log_textarea = nullptr;

void reset_floor_widgets() {
  memset(floor_widgets, 0, sizeof(floor_widgets));
}

bool is_park_floor(uint8_t floor) {
  return floor >= kFirstParkFloor && floor <= kMaxFloor;
}

void apply_floor_label(lv_obj_t *label, uint8_t floor) {
  if (!label) return;
  if (is_park_floor(floor)) {
    uint8_t idx = kMaxFloor - floor;
    if (idx < kParkFloorCount) {
      lv_label_set_text(label, kParkLabels[idx]);
      return;
    }
  }
  char buf[8];
  snprintf(buf, sizeof(buf), "%u", floor);
  lv_label_set_text(label, buf);
}

void log_msg(const char *msg) {
  Serial.println(msg ? msg : "");
}

void set_load_state(uint8_t floor, bool active) {
  if (floor < kMinFloor || floor > kMaxFloor) return;
  lv_obj_t *label = floor_widgets[floor].label;
  if (!label) return;
  lv_obj_set_style_text_color(label,
                              active ? UI_COLOR_LOAD : lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN);
}

void set_button_state(lv_obj_t *btn,
                      bool active,
                      lv_color_t active_color,
                      lv_color_t inactive_color) {
  if (!btn) return;
  lv_obj_t *label = lv_obj_get_child(btn, 0);
  if (!label) return;
  lv_obj_set_style_text_color(label, active ? active_color : inactive_color, 0);
}

void notify_handler(uint8_t floor, CallMask type, bool active) {
  if (!call_handler) return;
  ElevatorCallType mapped = ElevatorCallType::Up;
  switch (type) {
    case CALL_UP:
      mapped = ElevatorCallType::Up;
      break;
    case CALL_DOWN:
      mapped = ElevatorCallType::Down;
      break;
    case CALL_LOAD:
      mapped = ElevatorCallType::Load;
      break;
  }
  call_handler(floor, mapped, active);
}

void highlight_current_floor() {
  for (uint8_t f = kMinFloor; f <= kMaxFloor; ++f) {
    if (!floor_widgets[f].card) continue;
    lv_obj_remove_style(floor_widgets[f].card, &style_floor_current, 0);
  }
  if (current_floor >= kMinFloor && current_floor <= kMaxFloor) {
    if (floor_widgets[current_floor].card) {
      lv_obj_add_style(floor_widgets[current_floor].card, &style_floor_current,
                       0);
    }
  }
}

void call_button_cb(lv_event_t *e) {
  lv_obj_t *btn = lv_event_get_target(e);
  uint32_t data = (uint32_t)lv_event_get_user_data(e);
  uint8_t floor = data & 0xFF;
  CallMask mask = static_cast<CallMask>((data >> 8) & 0xFF);
  bool is_active = lv_obj_has_state(btn, LV_STATE_CHECKED);
  set_button_state(btn, !is_active,
                   (mask == CALL_UP) ? UI_COLOR_UP : UI_COLOR_DOWN,
                   lv_color_hex(0x9ea3b4));
  notify_handler(floor, mask, !is_active);
}

void floor_card_cb(lv_event_t *e) {
  lv_obj_t *card = lv_event_get_target(e);
  uint8_t floor = static_cast<uint8_t>(reinterpret_cast<uintptr_t>(
      lv_event_get_user_data(e)));
  bool now_active = !lv_obj_has_state(card, LV_STATE_CHECKED);
  if (now_active) {
    lv_obj_add_state(card, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(card, LV_STATE_CHECKED);
  }
  set_load_state(floor, now_active);
  notify_handler(floor, CALL_LOAD, now_active);
}

void set_active_nav(uint8_t idx, lv_obj_t **nav_btns, uint8_t count) {
  for (uint8_t i = 0; i < count; ++i) {
    if (!nav_btns[i]) continue;
    if (i == idx) {
      lv_obj_add_style(nav_btns[i], &style_nav_btn_active, 0);
    } else {
      lv_obj_remove_style(nav_btns[i], &style_nav_btn_active, 0);
    }
  }
}

void nav_btn_cb(lv_event_t *e) {
  uint8_t action = static_cast<uint8_t>(reinterpret_cast<uintptr_t>(
      lv_event_get_user_data(e)));
  switch (action) {
    case 0:
      if (shaft_screen) {
        lv_scr_load(shaft_screen);
        active_view = 0;
        log_msg("SHAFT view");
        set_active_nav(0, shaft_nav_btns, 3);
      }
      break;
    case 1:
      log_msg("GRID view (not available)");
      break;
    case 2:
      if (control_screen) {
        lv_scr_load(control_screen);
        active_view = 2;
        log_msg("CONTROL view");
        set_active_nav(3, control_nav_btns, 4);
      }
      break;
    case 3:
      if (shaft_screen) {
        lv_scr_load(shaft_screen);
        active_view = 0;
        log_msg("Returning to SHAFT view");
        set_active_nav(0, shaft_nav_btns, 3);
      }
      break;
  }
}

lv_obj_t *make_floor_box(lv_obj_t *parent, uint8_t floor) {
  lv_obj_t *box = lv_btn_create(parent);
  lv_obj_set_size(box, 58, 32);
  lv_obj_add_style(box, &style_floor_card, 0);
  lv_obj_set_style_bg_opa(box, LV_OPA_COVER, 0);
  lv_obj_add_event_cb(box, floor_card_cb, LV_EVENT_CLICKED,
                      (void *)(uintptr_t)floor);

  lv_obj_t *label = lv_label_create(box);
  apply_floor_label(label, floor);
  lv_obj_center(label);
  return box;
}

lv_obj_t *make_call_button(lv_obj_t *parent,
                           CallMask mask,
                           uint8_t floor,
                           const char *symbol) {
  lv_obj_t *btn = lv_btn_create(parent);
  lv_obj_remove_style_all(btn);
  lv_obj_set_size(btn, 28, 28);
  lv_obj_set_style_bg_opa(btn, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(btn, 0, 0);
  lv_obj_set_style_pad_all(btn, 0, 0);
  lv_obj_add_event_cb(btn, call_button_cb, LV_EVENT_CLICKED,
                      (void *)(uintptr_t)(floor | (mask << 8)));

  lv_obj_t *lbl = lv_label_create(btn);
  lv_label_set_text(lbl, symbol);
  lv_obj_set_style_text_color(lbl, lv_color_hex(0x9ea3b4), 0);
  lv_obj_center(lbl);
  return btn;
}

void add_floor_row(lv_obj_t *column, uint8_t floor) {
  lv_obj_t *row = lv_obj_create(column);
  lv_obj_set_width(row, lv_pct(100));
  lv_obj_set_height(row, 34);
  lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(row, 0, 0);
  lv_obj_set_style_pad_left(row, 4, 0);
  lv_obj_set_style_pad_right(row, 4, 0);
  lv_obj_set_style_pad_column(row, 6, 0);
  lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row, LV_FLEX_ALIGN_SPACE_BETWEEN,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  lv_obj_t *btn_up = make_call_button(row, CALL_UP, floor, LV_SYMBOL_UP);
  if (floor >= kTopDisplayFloor) {
    lv_obj_add_state(btn_up, LV_STATE_DISABLED);
    lv_obj_clear_flag(btn_up, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(btn_up, LV_OBJ_FLAG_HIDDEN);
    floor_widgets[floor].btnUp = nullptr;
  } else {
    floor_widgets[floor].btnUp = btn_up;
  }

  lv_obj_t *card = make_floor_box(row, floor);
  lv_obj_set_flex_grow(card, 1);
  floor_widgets[floor].card = card;
  floor_widgets[floor].label = lv_obj_get_child(card, 0);

  lv_obj_t *btn_down = make_call_button(row, CALL_DOWN, floor, LV_SYMBOL_DOWN);
  if (floor <= kMinFloor) {
    lv_obj_add_state(btn_down, LV_STATE_DISABLED);
    lv_obj_clear_flag(btn_down, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(btn_down, LV_OBJ_FLAG_HIDDEN);
    floor_widgets[floor].btnDown = nullptr;
  } else {
    floor_widgets[floor].btnDown = btn_down;
  }
}

void create_nav_bar(lv_obj_t *parent,
                    lv_obj_t **nav_btn_array,
                    const NavConfig *config,
                    uint8_t count,
                    uint8_t active_idx) {
  for (uint8_t i = 0; i < kMaxNavButtons; ++i) {
    nav_btn_array[i] = nullptr;
  }

  lv_obj_t *nav = lv_obj_create(parent);
  lv_obj_set_size(nav, 480, 60);
  lv_obj_align(nav, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(nav, UI_COLOR_NAV, 0);
  lv_obj_set_style_radius(nav, 0, 0);
  lv_obj_set_style_pad_all(nav, 10, 0);
  lv_obj_clear_flag(nav, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_flex_flow(nav, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(nav, LV_FLEX_ALIGN_SPACE_EVENLY,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(nav, 10, 0);

  for (uint8_t i = 0; i < count; ++i) {
    lv_obj_t *btn = lv_btn_create(nav);
    lv_obj_set_height(btn, 40);
    lv_obj_set_width(btn, LV_PCT(100 / count));
    lv_obj_add_style(btn, &style_nav_btn, 0);
    lv_obj_add_event_cb(btn, nav_btn_cb, LV_EVENT_CLICKED,
                        (void *)(uintptr_t)config[i].action);
    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, config[i].label);
    lv_obj_center(lbl);
    nav_btn_array[i] = btn;
  }

  set_active_nav(active_idx, nav_btn_array, count);
}

void build_shaft_screen() {
  reset_floor_widgets();

  shaft_screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(shaft_screen, UI_COLOR_BG, 0);
  lv_obj_clear_flag(shaft_screen, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *panel = lv_obj_create(shaft_screen);
  lv_obj_set_size(panel, 460, 720);
  lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, 10);
  lv_obj_set_style_bg_color(panel, UI_COLOR_PANEL, 0);
  lv_obj_set_style_radius(panel, 12, 0);
  lv_obj_set_style_pad_all(panel, 16, 0);
  lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

  constexpr uint8_t kColumnCount = 3;
  const lv_coord_t margin = 12;
  const lv_coord_t gap = 12;
  lv_coord_t usable_width = lv_obj_get_width(panel) - 2 * margin - gap * (kColumnCount - 1);
  lv_coord_t column_width = usable_width / kColumnCount;
  lv_coord_t column_height = lv_obj_get_height(panel) - 64;
  if (column_height <= 0) column_height = lv_obj_get_height(panel) - 16;

  lv_obj_t *columns[kColumnCount];
  for (uint8_t i = 0; i < kColumnCount; ++i) {
    columns[i] = lv_obj_create(panel);
    lv_obj_set_size(columns[i], column_width, column_height);
    lv_obj_set_pos(columns[i], margin + i * (column_width + gap), margin);
    lv_obj_set_style_bg_opa(columns[i], LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(columns[i], 0, 0);
    lv_obj_set_style_pad_all(columns[i], 0, 0);
    lv_obj_set_style_pad_row(columns[i], 4, 0);
    lv_obj_clear_flag(columns[i], LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(columns[i], LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(columns[i], LV_FLEX_ALIGN_START,
                          LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
  }

  std::vector<uint8_t> floor_order;
  for (int f = kTopDisplayFloor; f >= static_cast<int>(kMinFloor); --f) {
    floor_order.push_back(static_cast<uint8_t>(f));
  }
  for (int p = kParkFloorCount - 1; p >= 0; --p) {
    floor_order.push_back(kFirstParkFloor + p);
  }

  uint8_t per_column =
      (floor_order.size() + kColumnCount - 1) / kColumnCount;
  size_t idx = 0;
  for (uint8_t col = 0; col < kColumnCount && idx < floor_order.size();
       ++col) {
    for (uint8_t row = 0; row < per_column && idx < floor_order.size();
         ++row, ++idx) {
      add_floor_row(columns[col], floor_order[idx]);
    }
  }

  create_nav_bar(shaft_screen, shaft_nav_btns, kShaftNavConfig,
                 sizeof(kShaftNavConfig) / sizeof(kShaftNavConfig[0]), 0);
  lv_scr_load(shaft_screen);
}

lv_obj_t *create_status_card(lv_obj_t *parent, const char *title, const char *value, lv_color_t value_color, lv_coord_t x, lv_coord_t y) {
  lv_obj_t *card = lv_obj_create(parent);
  lv_obj_set_size(card, 200, 70);
  lv_obj_set_pos(card, x, y);
  lv_obj_add_style(card, &style_floor_card, 0);
  lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *title_label = lv_label_create(card);
  lv_label_set_text(title_label, title);
  lv_obj_set_pos(title_label, 12, 10);
  lv_obj_set_style_text_color(title_label, lv_color_hex(0xFFFFFF), 0);

  lv_obj_t *value_label = lv_label_create(card);
  lv_label_set_text(value_label, value);
  lv_obj_set_pos(value_label, 12, 40);
  lv_obj_set_style_text_color(value_label, value_color, 0);

  return value_label;
}

void build_control_screen() {
  control_screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(control_screen, UI_COLOR_BG, 0);
  lv_obj_clear_flag(control_screen, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *panel = lv_obj_create(control_screen);
  lv_obj_set_size(panel, 460, 720);
  lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, -4);
  lv_obj_set_style_bg_color(panel, UI_COLOR_PANEL, 0);
  lv_obj_set_style_radius(panel, 12, 0);
  lv_obj_set_style_pad_all(panel, 16, 0);
  lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

  // Status section container
  lv_obj_t *status_section = lv_obj_create(panel);
  lv_obj_set_size(status_section, 428, 160);
  lv_obj_set_pos(status_section, 0, 0);
  lv_obj_set_style_bg_opa(status_section, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(status_section, 0, 0);
  lv_obj_clear_flag(status_section, LV_OBJ_FLAG_SCROLLABLE);

  // Create 4 status cards
  gateway_status_label = create_status_card(status_section, "Gateway", "Online", UI_COLOR_UP, 0, 0);
  current_floor_label = create_status_card(status_section, "Current Floor", "1", UI_COLOR_ELEV, 228, 0);
  active_calls_label = create_status_card(status_section, "Active Calls", "0", UI_COLOR_LOAD, 0, 90);
  rssi_label = create_status_card(status_section, "Signal (RSSI)", "-65 dBm", lv_color_hex(0xFFFFFF), 228, 90);

  // Log panel
  lv_obj_t *log_panel = lv_obj_create(panel);
  lv_obj_set_size(log_panel, 428, 500);
  lv_obj_set_pos(log_panel, 0, 180);
  lv_obj_add_style(log_panel, &style_floor_card, 0);
  lv_obj_set_style_bg_color(log_panel, lv_color_hex(0x2c3e50), 0);

  lv_obj_t *log_title = lv_label_create(log_panel);
  lv_label_set_text(log_title, "System Log");
  lv_obj_set_pos(log_title, 12, 12);
  lv_obj_set_style_text_color(log_title, lv_color_hex(0xFFFFFF), 0);

  log_textarea = lv_textarea_create(log_panel);
  lv_obj_set_size(log_textarea, 404, 440);
  lv_obj_set_pos(log_textarea, 12, 40);
  lv_obj_set_style_bg_color(log_textarea, lv_color_hex(0x1e1e1e), 0);
  lv_obj_set_style_text_color(log_textarea, lv_color_hex(0x2ecc71), 0);
  lv_obj_set_style_border_width(log_textarea, 1, 0);
  lv_obj_set_style_border_color(log_textarea, lv_color_hex(0x34495e), 0);
  lv_textarea_set_text(log_textarea, "[SYSTEM] Display online\n[GATEWAY] Connected\n[INFO] Ready");

  create_nav_bar(control_screen, control_nav_btns, kControlNavConfig,
                 sizeof(kControlNavConfig) / sizeof(kControlNavConfig[0]), 3);
}


}  // namespace

void elevator_ui_init(void) {
  build_shaft_screen();
  build_control_screen();
  highlight_current_floor();
  log_msg("Elevator UI ready - SHAFT and CONTROL views available");
}

void elevator_ui_set_call_handler(ElevatorCallHandler handler) {
  call_handler = handler;
}

void elevator_ui_apply_floor_state(uint8_t floor,
                                   bool up,
                                   bool down,
                                   bool load,
                                   bool) {
  if (floor < kMinFloor || floor > kMaxFloor) return;
  set_button_state(floor_widgets[floor].btnUp, up, UI_COLOR_UP,
                   lv_color_hex(0x9ea3b4));
  set_button_state(floor_widgets[floor].btnDown, down, UI_COLOR_DOWN,
                   lv_color_hex(0x9ea3b4));
  set_load_state(floor, load);
}

void elevator_ui_set_current_floor(uint8_t floor, bool) {
  if (floor < kMinFloor || floor > kMaxFloor) return;
  current_floor = floor;
  highlight_current_floor();
}

void elevator_ui_log_message(const char *msg) {
  log_msg(msg);
}
