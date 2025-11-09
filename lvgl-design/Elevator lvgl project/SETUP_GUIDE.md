# Elevator LVGL Project - Setup Guide

## Project Configuration Complete! ✅

I've configured your LVGL Editor project with all the specifications from the crowpanel-display design.

## What's Been Set Up:

### 1. **Display Configuration** (`project.xml`)
- Resolution: 480×800 pixels (matches CrowPanel 7")
- Target name: "crowpanel"

### 2. **Color Palette** (`globals.xml`)
All colors defined as constants:
```
UI_COLOR_BG       #667eea  (purple background)
UI_COLOR_PANEL    #FFFFFF  (white panel)
UI_COLOR_SHAFT    #2c3e50  (dark gray containers)
UI_COLOR_ELEV     #3498db  (blue - current floor)
UI_COLOR_UP       #2ecc71  (green - UP calls)
UI_COLOR_DOWN     #e74c3c  (red - DOWN calls)
UI_COLOR_LOAD     #f39c12  (orange - LOAD calls)
UI_COLOR_NAV      #34495e  (dark slate - nav bar)
UI_COLOR_INACTIVE #9ea3b4  (gray - inactive buttons)
```

### 3. **Layout Constants** (`globals.xml`)
```
PANEL_WIDTH         460px
PANEL_HEIGHT        720px
NAV_HEIGHT          60px
FLOOR_ROW_HEIGHT    34px
FLOOR_CARD_HEIGHT   32px
CALL_BTN_SIZE       28px
```

### 4. **Styles Defined** (`globals.xml`)
- `style_floor_card` - Floor number cards
- `style_floor_current` - Current elevator position
- `style_nav_btn` - Navigation buttons (inactive)
- `style_nav_btn_active` - Navigation buttons (active)

### 5. **Main Screen** (`screens/shaft_screen.xml`)
- Purple background screen (480×800)
- White panel container (460×720)
- Navigation bar with 3 buttons: SHAFT, GRID, CONTROL

### 6. **Reusable Widget** (`widgets/floor_row.xml`)
Template for floor rows containing:
- UP button (↑) - 28×28px
- Floor card - 58×32px (grows to fill)
- DOWN button (↓) - 28×28px

## How to Use in LVGL Editor:

### **Step 1: Open the Project**

In VSCode:
1. Press `Ctrl+Shift+P`
2. Type: "LVGL: Open Editor"
3. Navigate to: `/home/collector985/lstore/Documents/PlatformIO/Projects/elevator-caller/lvgl-design/Elevator lvgl project`
4. Open `project.xml`

### **Step 2: View the Design**

The editor should show:
- **Left panel**: Widget tree (shaft_screen)
- **Center**: Visual preview (480×800 canvas)
- **Right panel**: Properties editor

### **Step 3: Build the Floor Layout**

**The panel needs 37 floor rows distributed across 3 columns:**

**Manual approach:**
1. Click on "panel" in the widget tree
2. Add 3 container objects (for columns)
3. Set each column:
   - Size: ~137px width × 624px height
   - Flex flow: column
   - Background: transparent
4. In each column, add multiple "floor_row" widgets
5. Customize each floor_row's label ("34", "33"..."1", "P3", "P2", "P1")

**OR generate via code** (recommended):
- Export the base structure
- Add C code to generate 37 floor rows programmatically

### **Step 4: Customize Floor Rows**

For each floor_row widget:
1. Click the floor_label
2. Change text: "34", "33", etc.
3. For top floor (34): Hide UP button
4. For bottom floor (1): Hide DOWN button
5. For parking (P3, P2, P1): Hide UP button, set labels

### **Step 5: Add Event Handlers**

You'll need to add these in code:
- `btn_up` click → Toggle UP call (green/gray)
- `btn_down` click → Toggle DOWN call (red/gray)
- `floor_card` click → Toggle LOAD call (orange text)
- Nav buttons → Switch screens

### **Step 6: Export Code**

When ready:
1. File → Export
2. Choose: C files for Arduino
3. Output location: Your crowpanel-display project
4. Merge with existing `elevator_ui.cpp`

## Floor Distribution:

```
Column 0 (left):   Floors 34-23  (12 floors)
Column 1 (middle): Floors 22-12  (11 floors)
Column 2 (right):  Floors 11-1, P3, P2, P1  (14 floors)
```

## Key Features to Implement:

### Visual States:
- **Inactive UP/DOWN**: Gray (#9ea3b4)
- **Active UP**: Green (#2ecc71)
- **Active DOWN**: Red (#e74c3c)
- **Active LOAD**: Orange text (#f39c12)
- **Current Floor**: Blue background (#3498db) + white outline

### Touch Interactions:
- Tap UP button → Toggle UP call
- Tap DOWN button → Toggle DOWN call
- Tap floor card → Toggle LOAD call
- Tap nav buttons → Switch views

## Integration with Existing Code:

After exporting from LVGL Editor:

1. **Copy generated UI code** to `crowpanel-display/src/`
2. **Keep existing:**
   - I2C communication (`main.cpp:275-313`)
   - Event handlers (`elevator_ui.cpp:117-169`)
   - Hardware initialization (`main.cpp:75-102`)
3. **Merge:**
   - New UI structure with existing callbacks
   - Style definitions
   - Widget creation logic

## Testing Workflow:

1. **Design in LVGL Editor** (visual)
2. **Export code** (generate C files)
3. **Test in simulator** (`lv_port_linux/`)
4. **Flash to hardware** (`pio run --target upload`)
5. **Iterate** (refine and re-export)

## Reference Documentation:

All detailed specs are in the parent `lvgl-design/` folder:
- `COMPONENT_BREAKDOWN.md` - Widget hierarchy
- `STYLES_REFERENCE.md` - Complete style specs
- `COLOR_PALETTE.md` - All colors
- `EVENT_HANDLERS.md` - Callbacks and I2C

## Next Steps:

1. ✅ Project configured (DONE)
2. ⏳ Open in LVGL Editor
3. ⏳ Add 3 columns to panel
4. ⏳ Add floor_row widgets (37 total)
5. ⏳ Customize floor labels
6. ⏳ Export code
7. ⏳ Merge with existing crowpanel-display
8. ⏳ Test on hardware

## Notes:

- The XML files use LVGL Editor's format
- Colors and constants are referenced by name (e.g., `UI_COLOR_BG`)
- Fonts need to be added manually to `fonts/` folder
- The layout is optimized for 800×480 (after rotation)
- All sizes match the existing working code

---

**Ready to open in LVGL Editor!** Press `Ctrl+Shift+P` → "LVGL: Open Editor" in VSCode.
