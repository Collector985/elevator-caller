#pragma once

#include <lvgl.h>

#define UI_COLOR_BG lv_color_hex(0x667eea)
#define UI_COLOR_PANEL lv_color_hex(0xFFFFFF)
#define UI_COLOR_SHAFT lv_color_hex(0x2c3e50)
#define UI_COLOR_ELEV lv_color_hex(0x3498db)
#define UI_COLOR_UP lv_color_hex(0x2ecc71)
#define UI_COLOR_DOWN lv_color_hex(0xe74c3c)
#define UI_COLOR_LOAD lv_color_hex(0xf39c12)
#define UI_COLOR_NAV lv_color_hex(0x34495e)

extern lv_style_t style_floor_card;
extern lv_style_t style_floor_current;
extern lv_style_t style_call_btn;
extern lv_style_t style_call_btn_pressed;
extern lv_style_t style_call_btn_checked;
extern lv_style_t style_nav_btn;
extern lv_style_t style_nav_btn_active;
extern lv_style_t style_grid_cell;
extern lv_style_t style_grid_cell_current;
extern lv_style_t style_log_panel;
extern lv_style_t style_log_ta;

void ui_styles_init();
