#include "ui_styles.h"

LV_FONT_DECLARE(lv_font_montserrat_16);
LV_FONT_DECLARE(lv_font_montserrat_18);
LV_FONT_DECLARE(lv_font_montserrat_22);

lv_style_t style_floor_card;
lv_style_t style_floor_current;
lv_style_t style_call_btn;
lv_style_t style_call_btn_pressed;
lv_style_t style_call_btn_checked;
lv_style_t style_nav_btn;
lv_style_t style_nav_btn_active;
lv_style_t style_grid_cell;
lv_style_t style_grid_cell_current;
lv_style_t style_log_panel;
lv_style_t style_log_ta;

void ui_styles_init() {
  lv_style_init(&style_floor_card);
  lv_style_set_bg_color(&style_floor_card, lv_color_hex(0x34495e));
  lv_style_set_bg_opa(&style_floor_card, LV_OPA_COVER);
  lv_style_set_radius(&style_floor_card, 8);
  lv_style_set_border_width(&style_floor_card, 0);
  lv_style_set_pad_all(&style_floor_card, 4);
  lv_style_set_text_font(&style_floor_card, &lv_font_montserrat_22);
  lv_style_set_text_color(&style_floor_card, lv_color_hex(0xFFFFFF));

  lv_style_init(&style_floor_current);
  lv_style_set_bg_color(&style_floor_current, UI_COLOR_ELEV);
  lv_style_set_bg_opa(&style_floor_current, LV_OPA_COVER);
  lv_style_set_outline_width(&style_floor_current, 2);
  lv_style_set_outline_color(&style_floor_current, lv_color_hex(0xFFFFFF));
  lv_style_set_outline_opa(&style_floor_current, LV_OPA_80);

  lv_style_init(&style_call_btn);
  lv_style_set_radius(&style_call_btn, 8);
  lv_style_set_border_width(&style_call_btn, 0);
  lv_style_set_pad_all(&style_call_btn, 8);
  lv_style_set_bg_opa(&style_call_btn, LV_OPA_COVER);
  lv_style_set_shadow_color(&style_call_btn, lv_color_hex(0x1a1a1a));
  lv_style_set_shadow_width(&style_call_btn, 10);
  lv_style_set_shadow_ofs_y(&style_call_btn, 4);
  lv_style_set_shadow_opa(&style_call_btn, LV_OPA_40);
  lv_style_set_text_font(&style_call_btn, &lv_font_montserrat_18);
  lv_style_set_text_color(&style_call_btn, lv_color_hex(0x000000));

  lv_style_init(&style_call_btn_pressed);
  lv_style_set_bg_opa(&style_call_btn_pressed, LV_OPA_COVER);
  lv_style_set_bg_color(&style_call_btn_pressed, lv_color_hex(0x16a085));

  lv_style_init(&style_call_btn_checked);
  lv_style_set_outline_width(&style_call_btn_checked, 2);
  lv_style_set_outline_color(&style_call_btn_checked, lv_color_hex(0xFFFF00));
  lv_style_set_outline_opa(&style_call_btn_checked, LV_OPA_80);

  lv_style_init(&style_nav_btn);
  lv_style_set_radius(&style_nav_btn, 10);
  lv_style_set_border_width(&style_nav_btn, 0);
  lv_style_set_bg_color(&style_nav_btn, lv_color_hex(0x2c3e50));
  lv_style_set_bg_opa(&style_nav_btn, LV_OPA_COVER);
  lv_style_set_text_color(&style_nav_btn, lv_color_hex(0xFFFFFF));
  lv_style_set_text_font(&style_nav_btn, &lv_font_montserrat_18);

  lv_style_init(&style_nav_btn_active);
  lv_style_set_bg_color(&style_nav_btn_active, lv_color_hex(0x3498db));
  lv_style_set_bg_opa(&style_nav_btn_active, LV_OPA_COVER);

  lv_style_init(&style_grid_cell);
  lv_style_set_radius(&style_grid_cell, 8);
  lv_style_set_border_width(&style_grid_cell, 2);
  lv_style_set_border_color(&style_grid_cell, lv_color_hex(0xbdc3c7));
  lv_style_set_bg_color(&style_grid_cell, lv_color_hex(0xecf0f1));
  lv_style_set_bg_opa(&style_grid_cell, LV_OPA_COVER);
  lv_style_set_pad_all(&style_grid_cell, 4);
  lv_style_set_text_font(&style_grid_cell, &lv_font_montserrat_16);
  lv_style_set_text_color(&style_grid_cell, lv_color_hex(0x000000));

  lv_style_init(&style_grid_cell_current);
  lv_style_set_border_color(&style_grid_cell_current, UI_COLOR_ELEV);
  lv_style_set_border_width(&style_grid_cell_current, 3);
  lv_style_set_bg_color(&style_grid_cell_current, lv_color_hex(0xe3f2fd));

  lv_style_init(&style_log_panel);
  lv_style_set_radius(&style_log_panel, 8);
  lv_style_set_bg_color(&style_log_panel, lv_color_hex(0x111111));
  lv_style_set_bg_opa(&style_log_panel, LV_OPA_COVER);
  lv_style_set_border_width(&style_log_panel, 0);

  lv_style_init(&style_log_ta);
  lv_style_set_bg_color(&style_log_ta, lv_color_hex(0x111111));
  lv_style_set_bg_opa(&style_log_ta, LV_OPA_TRANSP);
  lv_style_set_text_color(&style_log_ta, lv_color_hex(0x2ecc71));
  lv_style_set_text_font(&style_log_ta, &lv_font_montserrat_16);
}
