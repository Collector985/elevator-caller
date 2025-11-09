# LVGL Creator Setup Guide

## Choosing the Right Template

When creating a new project in LVGL Creator, you have several template options:

### Recommended: **Custom / Blank Project**

**Why?**
- Full control over layout
- No pre-existing components to remove
- Clean starting point
- Best for industrial/custom interfaces

**Alternative:** **Arduino ESP32 Template** (if available)
- Pre-configured for ESP32
- May include TFT setup code
- Requires removing example UI components

### ❌ **Avoid These Templates:**
- **Material Design** - Too consumer-focused
- **Dashboard** - Wrong layout pattern
- **Phone UI** - Mobile-oriented, not industrial

## Project Configuration

### Step 1: Create New Project

**Settings:**
```
Project Name:       elevator-display-lvgl
Target Platform:    ESP32 / Arduino
LVGL Version:       8.3.x
Display Width:      480 px
Display Height:     800 px
Color Depth:        16-bit (RGB565)
```

**Advanced Settings:**
```
Enable Touch:       Yes (Capacitive)
Rotation:           0° (we'll handle in code)
Memory:             128 KB
Draw Buffer:        4800 pixels (480×10)
DPI:                130
Refresh Rate:       30 ms
```

### Step 2: Font Setup

**Import Fonts:**
1. Go to **Assets → Fonts**
2. Click **Add Font**
3. Select **Montserrat** from built-in fonts
4. Enable sizes: **16, 18, 22**
5. Character range: **ASCII + Custom** ("P" for parking floors)

**Or Download:**
```
Google Fonts: Montserrat Regular
Sizes: 16pt, 18pt, 22pt
Format: C array
```

### Step 3: Color Palette Setup

**Create Color Variables:**
1. Go to **Styles → Colors**
2. Add custom colors:

```
Name:              Hex:      Usage:
UI_COLOR_BG        #667eea   Screen background
UI_COLOR_PANEL     #FFFFFF   Panel background
UI_COLOR_SHAFT     #2c3e50   Shaft/containers
UI_COLOR_ELEV      #3498db   Current floor
UI_COLOR_UP        #2ecc71   UP calls
UI_COLOR_DOWN      #e74c3c   DOWN calls
UI_COLOR_LOAD      #f39c12   LOAD calls
UI_COLOR_NAV       #34495e   Nav bar
UI_COLOR_INACTIVE  #9ea3b4   Inactive buttons
```

### Step 4: Create Base Styles

**Style 1: Floor Card**
```
Name: style_floor_card
Type: Button style

Background:
  - Color: UI_COLOR_SHAFT (#34495e)
  - Opacity: 100%
Border:
  - Width: 0
Radius: 8px
Padding: 4px (all sides)
Text:
  - Font: Montserrat 22
  - Color: #FFFFFF
```

**Style 2: Floor Current**
```
Name: style_floor_current
Type: Button style (state override)

Background:
  - Color: UI_COLOR_ELEV (#3498db)
  - Opacity: 100%
Outline:
  - Width: 2px
  - Color: #FFFFFF
  - Opacity: 80%
```

**Style 3: Nav Button**
```
Name: style_nav_btn
Type: Button style

Background:
  - Color: #2c3e50
Radius: 10px
Border: 0
Text:
  - Font: Montserrat 18
  - Color: #FFFFFF
Padding: 10px
```

**Style 4: Nav Button Active**
```
Name: style_nav_btn_active
Type: Button style (state override)

Background:
  - Color: UI_COLOR_ELEV (#3498db)
```

## Building the UI

### Method 1: Visual Editor (Recommended for Learning)

**Main Screen:**
1. Create main screen object
2. Set background: UI_COLOR_BG
3. Size: 480×800
4. Scrollable: OFF

**Panel Container:**
1. Drag **Container (Object)** onto screen
2. Size: 460×720
3. Align: Top center, Y offset: -4
4. Background: #FFFFFF
5. Radius: 12px
6. Padding: 16px
7. Scrollable: OFF

**Columns:**
1. Create 3 container objects inside panel
2. Layout: Flex column
3. Size: Calculate (412÷3 = ~137px width each)
4. Position: Manual (12px margin, 12px gap)
5. Background: Transparent
6. Padding: 0, Row gap: 4px

**Floor Row (Create as Template):**
1. Container object
2. Layout: Flex row, space-between
3. Size: 100% width × 34px
4. Padding: 4px left/right, 6px column gap
5. Children:
   - Button (UP): 28×28, transparent, symbol ▲
   - Button (Floor): 58×32, style_floor_card, grow=1
     - Label child: "34"
   - Button (DOWN): 28×28, transparent, symbol ▼

**Navigation Bar:**
1. Container at bottom
2. Size: 480×60
3. Align: Bottom center
4. Background: UI_COLOR_NAV
5. Padding: 10px
6. 3 buttons: 140×40 each, labels: "SHAFT", "GRID", "CONTROL"

### Method 2: Code Export (Recommended for Production)

After visual design:
1. **File → Export → Arduino Code**
2. Choose: **UI functions only** (separate from main)
3. Output:
   - `ui.h` - UI declarations
   - `ui.c` - UI creation functions
   - `ui_events.h` - Event handlers

**Then customize:**
- Rename `ui.c` to `elevator_ui.cpp`
- Add floor iteration loops
- Add event callbacks
- Integrate with I2C communication

## Component Details

### UP/DOWN Button Symbols

In LVGL Creator:
1. Create button
2. Add label child
3. Set label text:
   - UP: Use symbol picker → Select "▲" or type `LV_SYMBOL_UP`
   - DOWN: Symbol "▼" or `LV_SYMBOL_DOWN`

**In code:**
```c
lv_label_set_text(label, LV_SYMBOL_UP);    // ▲
lv_label_set_text(label, LV_SYMBOL_DOWN);  // ▼
```

### Floor Card State Management

**Normal state:** style_floor_card
**Current floor:** Add style_floor_current

In LVGL Creator Events:
```c
// On elevator position update
void set_current_floor(uint8_t floor) {
    // Remove from all
    for (int f = 1; f <= 37; f++) {
        lv_obj_remove_style(floor_cards[f], &style_floor_current, 0);
    }
    // Add to current
    lv_obj_add_style(floor_cards[floor], &style_floor_current, 0);
}
```

### LOAD State (Text Color Change)

```c
void set_load_active(uint8_t floor, bool active) {
    lv_obj_t *label = lv_obj_get_child(floor_cards[floor], 0);
    lv_obj_set_style_text_color(label,
        active ? UI_COLOR_LOAD : lv_color_hex(0xFFFFFF),
        LV_PART_MAIN);
}
```

## Event Handlers

### Floor Card Click (LOAD Toggle)

```c
static void floor_card_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        uint8_t floor = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
        bool active = lv_obj_has_state(e->target, LV_STATE_CHECKED);

        // Toggle checkable state
        if (active) {
            lv_obj_clear_state(e->target, LV_STATE_CHECKED);
        } else {
            lv_obj_add_state(e->target, LV_STATE_CHECKED);
        }

        // Update text color
        set_load_active(floor, !active);

        // Notify gateway
        send_load_command(floor, !active);
    }
}
```

### UP/DOWN Button Click

```c
static void call_button_event_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        uint32_t data = (uint32_t)lv_event_get_user_data(e);
        uint8_t floor = data & 0xFF;
        uint8_t type = (data >> 8) & 0xFF;  // 1=UP, 2=DOWN

        lv_obj_t *btn = lv_event_get_target(e);
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        bool active = lv_obj_has_state(btn, LV_STATE_CHECKED);

        // Toggle color
        lv_color_t color = active ? lv_color_hex(0x9ea3b4) :
                          (type == 1 ? UI_COLOR_UP : UI_COLOR_DOWN);
        lv_obj_set_style_text_color(label, color, 0);

        // Notify gateway
        send_call_command(floor, type, !active);
    }
}
```

### Navigation Button Click

```c
static void nav_button_event_cb(lv_event_t *e) {
    uint8_t idx = (uint8_t)(uintptr_t)lv_event_get_user_data(e);

    // Update active style
    for (int i = 0; i < 3; i++) {
        lv_obj_remove_style(nav_btns[i], &style_nav_btn_active, 0);
    }
    lv_obj_add_style(nav_btns[idx], &style_nav_btn_active, 0);

    // Load screen
    switch (idx) {
        case 0: lv_scr_load(shaft_screen); break;
        case 1: lv_scr_load(grid_screen); break;
        case 2: lv_scr_load(control_screen); break;
    }
}
```

## Integration with Arduino Code

### Export UI from LVGL Creator

**File → Export:**
- Format: Arduino
- Include: UI functions + event stubs
- Output folder: `/src/ui/`

### Modify Exported Code

**ui.h:**
```c
#pragma once
#include <lvgl.h>

void ui_init(void);
void ui_set_current_floor(uint8_t floor);
void ui_set_call_state(uint8_t floor, uint8_t type, bool active);
```

**ui.cpp:**
```cpp
#include "ui.h"

// Generated LVGL objects
lv_obj_t *shaft_screen;
lv_obj_t *floor_cards[38];
lv_obj_t *up_buttons[38];
lv_obj_t *down_buttons[38];

void ui_init(void) {
    // Auto-generated initialization code
    build_shaft_screen();
}
```

### Connect to Main Loop

**main.cpp:**
```cpp
#include "ui.h"

void setup() {
    // Display init
    initDisplay();
    initLVGL();

    // LVGL UI
    ui_init();

    // Your callbacks
    set_call_handler(handleUICall);
}

void loop() {
    lv_timer_handler();

    // Update from gateway
    if (new_data) {
        ui_set_current_floor(elevator_floor);
        ui_set_call_state(floor, type, active);
    }
}
```

## Testing Workflow

1. **Design in LVGL Creator** - Visual layout
2. **Export code** - Generate C files
3. **Integrate** - Merge with existing code
4. **Add logic** - Event handlers, I2C communication
5. **Flash & test** - Upload to CrowPanel
6. **Iterate** - Refine in Creator, re-export

## Tips

- Use **Grid Layout** tool for aligning columns
- **Duplicate** floor rows instead of creating each manually
- **Group** related widgets for easier management
- **Name widgets** clearly: `floor_card_15`, `btn_up_15`
- **Test touch areas** - Ensure 28px minimum
- **Preview** on actual resolution (800×480 rotated)
