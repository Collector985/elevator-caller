#include "elevator_ui.h"

#include <Arduino.h>
#include <lvgl.h>
#include <cstring>

#include "ui_styles.h"

namespace {

constexpr uint8_t kMinFloor = 1;
#ifdef TOTAL_FLOORS
constexpr uint8_t kMaxFloor = TOTAL_FLOORS;
#else
constexpr uint8_t kMaxFloor = 30;
#endif
constexpr uint8_t kLeftStart = kMaxFloor;
constexpr uint8_t kLeftEnd = (kMaxFloor > 15) ? 16 : kMaxFloor / 2;
constexpr uint8_t kRightStart = (kLeftEnd - 1);
constexpr uint8_t kRightEnd = kMinFloor;

enum CallMask : uint8_t {
  CALL_UP = 0x01,
  CALL_DOWN = 0x02,
  CALL_LOAD = 0x04,
};

struct FloorWidgets {
  lv_obj_t *card = nullptr;
  lv_obj_t *btnUp = nullptr;
  lv_obj_t *btnDown = nullptr;
  lv_obj_t *btnLoad = nullptr;
};

static lv_obj_t *shaft_screen = nullptr;
static lv_obj_t *nav_btns[3] = {nullptr};
static FloorWidgets floor_widgets[kMaxFloor + 1];
static ElevatorCallHandler call_handler = nullptr;
static uint8_t current_floor = 1;

void reset_floor_widgets() {
  memset(floor_widgets, 0, sizeof(floor_widgets));
}

void log_msg(const char *msg) {
  Serial.println(msg ? msg : "");
}

void set_button_state(lv_obj_t *btn, bool active) {
  if (!btn) return;
  if (active) {
    lv_obj_add_state(btn, LV_STATE_CHECKED);
  } else {
    lv_obj_clear_state(btn, LV_STATE_CHECKED);
  }
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
  set_button_state(btn, !is_active);
  notify_handler(floor, mask, !is_active);
}

void set_active_nav(uint8_t idx) {
  for (uint8_t i = 0; i < 3; ++i) {
    if (!nav_btns[i]) continue;
    if (i == idx) {
      lv_obj_add_style(nav_btns[i], &style_nav_btn_active, 0);
    } else {
      lv_obj_remove_style(nav_btns[i], &style_nav_btn_active, 0);
    }
  }
}

void nav_btn_cb(lv_event_t *e) {
  uint8_t idx = static_cast<uint8_t>(reinterpret_cast<uintptr_t>(
      lv_event_get_user_data(e)));
  switch (idx) {
    case 0:
      log_msg("SHAFT view");
      break;
    case 1:
      log_msg("GRID view link pressed (not available)");
      break;
    case 2:
      log_msg("CONTROL view link pressed (not available)");
      break;
  }
  set_active_nav(0);
}

lv_obj_t *make_floor_box(lv_obj_t *parent, uint8_t floor) {
  lv_obj_t *box = lv_obj_create(parent);
  lv_obj_set_size(box, 58, 36);
  lv_obj_clear_flag(box, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_style(box, &style_floor_card, 0);

  lv_obj_t *label = lv_label_create(box);
  char buf[8];
  snprintf(buf, sizeof(buf), "%u", floor);
  lv_label_set_text(label, buf);
  lv_obj_center(label);
  return box;
}

lv_obj_t *make_call_button(lv_obj_t *parent,
                           CallMask mask,
                           uint8_t floor,
                           lv_color_t base_color) {
  lv_obj_t *btn = lv_btn_create(parent);
  lv_obj_set_size(btn, 36, 36);
  lv_obj_add_style(btn, &style_call_btn, 0);
  lv_obj_add_style(btn, &style_call_btn_pressed, LV_STATE_PRESSED);
  lv_obj_add_style(btn, &style_call_btn_checked, LV_STATE_CHECKED);
  lv_obj_set_style_bg_color(btn, base_color, 0);
  lv_obj_set_style_bg_color(btn, lv_color_hex(0xFFFF00), LV_STATE_CHECKED);
  lv_obj_add_event_cb(btn, call_button_cb, LV_EVENT_CLICKED,
                      (void *)(uintptr_t)(floor | (mask << 8)));

  const char *symbol = "";
  switch (mask) {
    case CALL_UP:
      symbol = "▲";
      break;
    case CALL_DOWN:
      symbol = "▼";
      break;
    case CALL_LOAD:
      symbol = "LD";
      break;
  }
  lv_obj_t *lbl = lv_label_create(btn);
  lv_label_set_text(lbl, symbol);
  lv_obj_center(lbl);
  return btn;
}

void add_floor_row(lv_obj_t *column, uint8_t floor) {
  lv_obj_t *row = lv_obj_create(column);
  lv_obj_set_width(row, lv_pct(100));
  lv_obj_set_height(row, 44);
  lv_obj_set_style_bg_opa(row, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(row, 0, 0);
  lv_obj_set_style_pad_left(row, 2, 0);
  lv_obj_set_style_pad_right(row, 2, 0);
  lv_obj_set_style_pad_column(row, 8, 0);
  lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);

  lv_obj_t *card = make_floor_box(row, floor);
  lv_obj_set_flex_grow(card, 0);
  floor_widgets[floor].card = card;

  lv_obj_t *btn_group = lv_obj_create(row);
  lv_obj_set_style_bg_opa(btn_group, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(btn_group, 0, 0);
  lv_obj_set_style_pad_all(btn_group, 0, 0);
  lv_obj_set_style_pad_column(btn_group, 6, 0);
  lv_obj_clear_flag(btn_group, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_width(btn_group, lv_pct(100));
  lv_obj_set_flex_flow(btn_group, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btn_group, LV_FLEX_ALIGN_SPACE_EVENLY,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_flex_grow(btn_group, 1);

  if (floor < kMaxFloor) {
    floor_widgets[floor].btnUp =
        make_call_button(btn_group, CALL_UP, floor, UI_COLOR_UP);
  }
  if (floor > kMinFloor) {
    floor_widgets[floor].btnDown =
        make_call_button(btn_group, CALL_DOWN, floor, UI_COLOR_DOWN);
  }
  floor_widgets[floor].btnLoad =
      make_call_button(btn_group, CALL_LOAD, floor, UI_COLOR_LOAD);
}

void create_nav_bar(lv_obj_t *parent) {
  for (auto &btn : nav_btns) {
    btn = nullptr;
  }

  lv_obj_t *nav = lv_obj_create(parent);
  lv_obj_set_size(nav, 480, 60);
  lv_obj_align(nav, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(nav, UI_COLOR_NAV, 0);
  lv_obj_set_style_radius(nav, 0, 0);
  lv_obj_set_style_pad_all(nav, 10, 0);
  lv_obj_clear_flag(nav, LV_OBJ_FLAG_SCROLLABLE);

  const char *labels[] = {"SHAFT", "GRID", "CONTROL"};
  for (uint8_t i = 0; i < 3; ++i) {
    lv_obj_t *btn = lv_btn_create(nav);
    lv_obj_set_size(btn, 140, 40);
    lv_obj_add_style(btn, &style_nav_btn, 0);
    lv_obj_add_event_cb(btn, nav_btn_cb, LV_EVENT_CLICKED,
                        (void *)(uintptr_t)i);
    lv_obj_t *lbl = lv_label_create(btn);
    lv_label_set_text(lbl, labels[i]);
    lv_obj_center(lbl);
    nav_btns[i] = btn;
  }

  set_active_nav(0);
}

void build_shaft_screen() {
  reset_floor_widgets();

  shaft_screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(shaft_screen, UI_COLOR_BG, 0);
  lv_obj_clear_flag(shaft_screen, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *panel = lv_obj_create(shaft_screen);
  lv_obj_set_size(panel, 460, 720);
  lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_bg_color(panel, UI_COLOR_PANEL, 0);
  lv_obj_set_style_radius(panel, 12, 0);
  lv_obj_set_style_pad_all(panel, 8, 0);
  lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *shaft_strip = lv_obj_create(panel);
  lv_obj_set_size(shaft_strip, 12, 650);
  lv_obj_align(shaft_strip, LV_ALIGN_TOP_MID, 0, 16);
  lv_obj_set_style_bg_color(shaft_strip, UI_COLOR_SHAFT, 0);
  lv_obj_set_style_radius(shaft_strip, 6, 0);
  lv_obj_clear_flag(shaft_strip, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *col_left = lv_obj_create(panel);
  lv_obj_set_size(col_left, 190, 700);
  lv_obj_align(col_left, LV_ALIGN_TOP_LEFT, 0, 8);
  lv_obj_set_style_bg_opa(col_left, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(col_left, 0, 0);
  lv_obj_set_style_pad_all(col_left, 0, 0);
  lv_obj_set_style_pad_row(col_left, 6, 0);
  lv_obj_clear_flag(col_left, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_flex_flow(col_left, LV_FLEX_FLOW_COLUMN);

  lv_obj_t *col_right = lv_obj_create(panel);
  lv_obj_set_size(col_right, 190, 700);
  lv_obj_align(col_right, LV_ALIGN_TOP_RIGHT, 0, 8);
  lv_obj_set_style_bg_opa(col_right, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(col_right, 0, 0);
  lv_obj_set_style_pad_all(col_right, 0, 0);
  lv_obj_set_style_pad_row(col_right, 6, 0);
  lv_obj_clear_flag(col_right, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_flex_flow(col_right, LV_FLEX_FLOW_COLUMN);

  for (uint8_t f = kLeftStart; f >= kLeftEnd; --f) {
    add_floor_row(col_left, f);
    if (f == kLeftEnd) break;
  }

  for (int f = kRightStart; f >= static_cast<int>(kRightEnd); --f) {
    if (f < kMinFloor) continue;
    add_floor_row(col_right, static_cast<uint8_t>(f));
  }

  create_nav_bar(shaft_screen);
  lv_scr_load(shaft_screen);
}

}  // namespace

void elevator_ui_init(void) {
  build_shaft_screen();
  highlight_current_floor();
  log_msg("SHAFT view ready");
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
  set_button_state(floor_widgets[floor].btnUp, up);
  set_button_state(floor_widgets[floor].btnDown, down);
  set_button_state(floor_widgets[floor].btnLoad, load);
}

void elevator_ui_set_current_floor(uint8_t floor, bool) {
  if (floor < kMinFloor || floor > kMaxFloor) return;
  current_floor = floor;
  highlight_current_floor();
}

void elevator_ui_log_message(const char *msg) {
  log_msg(msg);
}
