#include "ui_theme.h"

LV_FONT_DECLARE(lv_font_montserrat_16);

void ui_theme_init() {
  lv_disp_t *disp = lv_disp_get_default();
  if (!disp) return;

  lv_theme_t *theme = lv_theme_default_init(
      disp, lv_color_hex(0x3498db), lv_color_hex(0x2c3e50), false,
      &lv_font_montserrat_16);
  lv_disp_set_theme(disp, theme);
}
