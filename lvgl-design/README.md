# LVGL Design Documentation

This folder contains complete specifications for recreating the CrowPanel 7" elevator display interface using LVGL Creator.

## Quick Start

1. **Read first:** `LVGL_CREATOR_GUIDE.md` - Choose template and configure project
2. **Reference:** `PROJECT_SPECIFICATION.md` - Overall requirements
3. **Design:** `COLOR_PALETTE.md` + `STYLES_REFERENCE.md` - Visual design
4. **Build:** `COMPONENT_BREAKDOWN.md` - UI structure
5. **Code:** `EVENT_HANDLERS.md` - Functionality

## File Overview

| File | Purpose |
|------|---------|
| `PROJECT_SPECIFICATION.md` | Hardware specs, software stack, display config |
| `COLOR_PALETTE.md` | All colors with hex codes and usage |
| `STYLES_REFERENCE.md` | LVGL style definitions and fonts |
| `COMPONENT_BREAKDOWN.md` | Widget hierarchy and layout calculations |
| `LVGL_CREATOR_GUIDE.md` | Step-by-step guide for LVGL Creator |
| `EVENT_HANDLERS.md` | Event callbacks and I2C integration |

## Project Context

This design is for the **CrowPanel 7" Advance** display in an elevator call station system:

- **Total Floors:** 37 (1-34 + P1, P2, P3)
- **Call Types:** UP, DOWN, LOAD (materials)
- **Communication:** I2C with LoRa gateway
- **Views:** SHAFT (implemented), GRID, CONTROL (planned)

## Current Status

**Implemented:**
- ✅ SHAFT view - 3-column vertical floor list
- ✅ UP/DOWN call buttons with color states
- ✅ LOAD call via floor card tap
- ✅ Current floor highlighting
- ✅ Touch-based call clearing
- ✅ I2C gateway communication
- ✅ Navigation bar (UI only)

**Planned:**
- ⏳ GRID view - 8×5 floor grid layout
- ⏳ CONTROL view - Log panel + system stats
- ⏳ RSSI signal strength display
- ⏳ Network status indicator

## Display Specifications

```
Hardware:     CrowPanel 7" Advance (Elecrow)
Resolution:   800×480 (landscape after rotation)
Touch:        GT911 capacitive
MCU:          ESP32-S3
Driver:       LovyanGFX
LVGL:         8.3.0
Color:        RGB565 (16-bit)
```

## Color Scheme

```
Background:   Purple gradient (#667eea)
Panel:        White (#FFFFFF)
UP:           Green (#2ecc71)
DOWN:         Red (#e74c3c)
LOAD:         Orange (#f39c12)
Current:      Blue (#3498db)
Containers:   Dark gray (#34495e, #2c3e50)
```

## Layout Dimensions

```
Screen:           480 × 800
Panel:            460 × 720
Columns:          3 (each ~137px wide)
Floor row:        100% × 34px
UP/DOWN button:   28 × 28
Floor card:       58 × 32 (grows to fill)
Nav bar:          480 × 60
Nav button:       140 × 40
```

## Fonts

- **Montserrat 22** - Floor numbers
- **Montserrat 18** - Navigation buttons
- **Montserrat 16** - Log text (future)

## Key Features

### Touch Interactions
- **Floor card tap** → Toggle LOAD call (text color changes)
- **UP button tap** → Toggle UP call (green/gray)
- **DOWN button tap** → Toggle DOWN call (red/gray)
- **Nav button tap** → Switch view (future)

### Visual Feedback
- **Current floor** → Blue background + white outline
- **Active call** → Colored symbol (green/red) or text (orange)
- **Inactive call** → Gray (#9ea3b4)

### Communication
- **I2C Address:** 0x08 (gateway)
- **Polling:** 200ms
- **Packet format:** floor + status byte + RSSI

## Integration Points

### From Code to LVGL Creator

If you're starting fresh in LVGL Creator:

1. Use `COMPONENT_BREAKDOWN.md` to recreate widget hierarchy
2. Apply styles from `STYLES_REFERENCE.md`
3. Use colors from `COLOR_PALETTE.md`
4. Follow setup in `LVGL_CREATOR_GUIDE.md`

### From LVGL Creator to Code

After designing in LVGL Creator:

1. Export → Arduino code
2. Merge with existing `elevator_ui.cpp`
3. Add event handlers from `EVENT_HANDLERS.md`
4. Integrate I2C communication

## Source Code Reference

Current implementation files:
```
crowpanel-display/
├── include/
│   ├── elevator_ui.h         - Public API
│   ├── ui_styles.h            - Style declarations
│   ├── ui_theme.h             - Theme init
│   └── lv_conf.h              - LVGL configuration
├── src/
│   ├── main.cpp               - Main loop + I2C
│   ├── elevator_ui.cpp        - UI implementation
│   ├── ui_styles.cpp          - Style definitions
│   └── ui_theme.cpp           - Theme setup
└── platformio.ini             - Build config
```

## Design Philosophy

**Industrial & Professional:**
- High contrast for construction site visibility
- Large touch targets (minimum 28×28px)
- Simple color coding (green=up, red=down, orange=load)
- Clean, minimal interface

**Performance:**
- Efficient LVGL rendering
- Minimal memory usage (128KB buffer)
- Fast touch response (<50ms)
- No heavy animations

**Scalability:**
- Supports 1-100+ floors
- Dynamic column layout
- Configurable floor count
- Extensible to additional views

## Tips for LVGL Creator

1. **Start with blank project** - Easier than modifying templates
2. **Create floor row as template** - Duplicate 37 times
3. **Use flex layouts** - Auto-arranges columns and rows
4. **Name widgets clearly** - `floor_card_15`, `btn_up_15`, etc.
5. **Test on actual resolution** - Preview at 800×480
6. **Export often** - Keep code and design in sync

## Next Steps

1. Open LVGL Creator
2. Follow `LVGL_CREATOR_GUIDE.md` step-by-step
3. Create blank 480×800 project
4. Import Montserrat fonts (16, 18, 22)
5. Set up color palette from `COLOR_PALETTE.md`
6. Build UI structure from `COMPONENT_BREAKDOWN.md`
7. Apply styles from `STYLES_REFERENCE.md`
8. Export and integrate with event handlers

## Questions?

Refer to specific documentation files for detailed information:
- **"How do I set up colors?"** → `COLOR_PALETTE.md`
- **"What are the exact widget sizes?"** → `COMPONENT_BREAKDOWN.md`
- **"How do I style buttons?"** → `STYLES_REFERENCE.md`
- **"How do events work?"** → `EVENT_HANDLERS.md`
- **"Which template should I use?"** → `LVGL_CREATOR_GUIDE.md`

---

**Last Updated:** 2025-11-08
**LVGL Version:** 8.3.0
**Hardware:** CrowPanel 7" Advance (ESP32-S3)
