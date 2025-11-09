# Styles Reference

## Font Requirements

### Montserrat Font Family
```c
LV_FONT_DECLARE(lv_font_montserrat_16);  // Log text, grid cells
LV_FONT_DECLARE(lv_font_montserrat_18);  // Navigation buttons, call buttons
LV_FONT_DECLARE(lv_font_montserrat_22);  // Floor numbers (main)
```

**Enable in lv_conf.h:**
```c
#define LV_FONT_MONTSERRAT_16  1
#define LV_FONT_MONTSERRAT_18  1
#define LV_FONT_MONTSERRAT_22  1
```

## Style Definitions

### 1. Floor Card Style (`style_floor_card`)

**Applied to**: Floor number cards (normal state)

```c
lv_style_init(&style_floor_card);
lv_style_set_bg_color(&style_floor_card, lv_color_hex(0x34495e));
lv_style_set_bg_opa(&style_floor_card, LV_OPA_COVER);
lv_style_set_radius(&style_floor_card, 8);
lv_style_set_border_width(&style_floor_card, 0);
lv_style_set_pad_all(&style_floor_card, 4);
lv_style_set_text_font(&style_floor_card, &lv_font_montserrat_22);
lv_style_set_text_color(&style_floor_card, lv_color_hex(0xFFFFFF));
```

**Properties:**
- Background: Dark slate gray (#34495e)
- Opacity: Full (100%)
- Border radius: 8px (rounded corners)
- No border
- Padding: 4px all sides
- Font: Montserrat 22pt
- Text: White

---

### 2. Current Floor Style (`style_floor_current`)

**Applied to**: The floor where elevator is currently located

```c
lv_style_init(&style_floor_current);
lv_style_set_bg_color(&style_floor_current, UI_COLOR_ELEV);  // #3498db
lv_style_set_bg_opa(&style_floor_current, LV_OPA_COVER);
lv_style_set_outline_width(&style_floor_current, 2);
lv_style_set_outline_color(&style_floor_current, lv_color_hex(0xFFFFFF));
lv_style_set_outline_opa(&style_floor_current, LV_OPA_80);
```

**Properties:**
- Background: Blue (#3498db)
- Opacity: Full (100%)
- Outline: 2px white at 80% opacity
- Overrides `style_floor_card` background

**Usage:**
```c
// Remove from all floors
for (uint8_t f = 1; f <= TOTAL_FLOORS; ++f) {
    lv_obj_remove_style(floor_widgets[f].card, &style_floor_current, 0);
}

// Add to current floor
lv_obj_add_style(floor_widgets[current_floor].card, &style_floor_current, 0);
```

---

### 3. Call Button Style (`style_call_btn`)

**Applied to**: UP/DOWN call buttons (deprecated in current implementation)

```c
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
```

**Note**: Current implementation uses transparent buttons with colored symbols instead.

---

### 4. Call Button Pressed Style (`style_call_btn_pressed`)

```c
lv_style_init(&style_call_btn_pressed);
lv_style_set_bg_opa(&style_call_btn_pressed, LV_OPA_COVER);
lv_style_set_bg_color(&style_call_btn_pressed, lv_color_hex(0x16a085));
```

**Properties:**
- Background: Teal (#16a085)
- Applied on LV_STATE_PRESSED

---

### 5. Call Button Checked Style (`style_call_btn_checked`)

```c
lv_style_init(&style_call_btn_checked);
lv_style_set_outline_width(&style_call_btn_checked, 2);
lv_style_set_outline_color(&style_call_btn_checked, lv_color_hex(0xFFFF00));
lv_style_set_outline_opa(&style_call_btn_checked, LV_OPA_80);
```

**Properties:**
- Outline: 2px yellow at 80% opacity
- Applied on LV_STATE_CHECKED

---

### 6. Navigation Button Style (`style_nav_btn`)

**Applied to**: Bottom navigation buttons (inactive state)

```c
lv_style_init(&style_nav_btn);
lv_style_set_radius(&style_nav_btn, 10);
lv_style_set_border_width(&style_nav_btn, 0);
lv_style_set_bg_color(&style_nav_btn, lv_color_hex(0x2c3e50));
lv_style_set_bg_opa(&style_nav_btn, LV_OPA_COVER);
lv_style_set_text_color(&style_nav_btn, lv_color_hex(0xFFFFFF));
lv_style_set_text_font(&style_nav_btn, &lv_font_montserrat_18);
```

**Properties:**
- Background: Dark gray (#2c3e50)
- Border radius: 10px
- No border
- Text: White, Montserrat 18pt

---

### 7. Navigation Button Active Style (`style_nav_btn_active`)

**Applied to**: Currently selected navigation button

```c
lv_style_init(&style_nav_btn_active);
lv_style_set_bg_color(&style_nav_btn_active, lv_color_hex(0x3498db));
lv_style_set_bg_opa(&style_nav_btn_active, LV_OPA_COVER);
```

**Properties:**
- Background: Blue (#3498db)
- Overrides `style_nav_btn` background

**Usage:**
```c
// Set SHAFT button as active by default
lv_obj_add_style(nav_btns[0], &style_nav_btn_active, 0);
```

---

### 8. Grid Cell Style (`style_grid_cell`)

**For future GRID view implementation**

```c
lv_style_init(&style_grid_cell);
lv_style_set_radius(&style_grid_cell, 8);
lv_style_set_border_width(&style_grid_cell, 2);
lv_style_set_border_color(&style_grid_cell, lv_color_hex(0xbdc3c7));
lv_style_set_bg_color(&style_grid_cell, lv_color_hex(0xecf0f1));
lv_style_set_bg_opa(&style_grid_cell, LV_OPA_COVER);
lv_style_set_pad_all(&style_grid_cell, 4);
lv_style_set_text_font(&style_grid_cell, &lv_font_montserrat_16);
lv_style_set_text_color(&style_grid_cell, lv_color_hex(0x000000));
```

---

### 9. Grid Cell Current Style (`style_grid_cell_current`)

**For future GRID view implementation**

```c
lv_style_init(&style_grid_cell_current);
lv_style_set_border_color(&style_grid_cell_current, UI_COLOR_ELEV);
lv_style_set_border_width(&style_grid_cell_current, 3);
lv_style_set_bg_color(&style_grid_cell_current, lv_color_hex(0xe3f2fd));
```

---

### 10. Log Panel Style (`style_log_panel`)

**For future CONTROL view implementation**

```c
lv_style_init(&style_log_panel);
lv_style_set_radius(&style_log_panel, 8);
lv_style_set_bg_color(&style_log_panel, lv_color_hex(0x111111));
lv_style_set_bg_opa(&style_log_panel, LV_OPA_COVER);
lv_style_set_border_width(&style_log_panel, 0);
```

---

### 11. Log Text Area Style (`style_log_ta`)

**For future CONTROL view implementation**

```c
lv_style_init(&style_log_ta);
lv_style_set_bg_color(&style_log_ta, lv_color_hex(0x111111));
lv_style_set_bg_opa(&style_log_ta, LV_OPA_TRANSP);
lv_style_set_text_color(&style_log_ta, lv_color_hex(0x2ecc71));
lv_style_set_text_font(&style_log_ta, &lv_font_montserrat_16);
```

## Dynamic State Colors

### UP/DOWN Button States
Applied programmatically via `set_button_state()`:

```c
// Inactive
lv_obj_set_style_text_color(label, lv_color_hex(0x9ea3b4), 0);

// Active UP
lv_obj_set_style_text_color(label, UI_COLOR_UP, 0);  // #2ecc71

// Active DOWN
lv_obj_set_style_text_color(label, UI_COLOR_DOWN, 0);  // #e74c3c
```

### LOAD State
Applied programmatically via `set_load_state()`:

```c
// Inactive
lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);

// Active LOAD
lv_obj_set_style_text_color(label, UI_COLOR_LOAD, LV_PART_MAIN);  // #f39c12
```

## Style Initialization Order

**In `main.cpp` setup():**
```c
ui_theme_init();    // Initialize theme (if used)
ui_styles_init();   // Initialize all styles above
elevator_ui_init(); // Build UI and apply styles
```

**In `elevator_ui_init()`:**
```c
build_shaft_screen();      // Create widgets
highlight_current_floor(); // Apply current floor style
```

## Style Application Patterns

### Adding Multiple Styles
```c
lv_obj_t *btn = lv_btn_create(parent);
lv_obj_add_style(btn, &style_floor_card, 0);           // Base style
lv_obj_add_style(btn, &style_floor_current, 0);        // Current state
```

### Removing Styles
```c
lv_obj_remove_style(floor_widgets[f].card, &style_floor_current, 0);
```

### Style Priority
Later styles override earlier ones for conflicting properties:
```c
style_floor_card      (background: #34495e)
style_floor_current   (background: #3498db) ← wins
```

## Performance Considerations

- Styles are initialized once at startup
- Style changes are applied to individual objects
- Use `lv_obj_add_style()` / `lv_obj_remove_style()` for state changes
- Avoid recreating styles during runtime
- Shadow effects disabled to save memory/performance
