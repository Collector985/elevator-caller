# Component Breakdown

## Screen Hierarchy

```
shaft_screen (lv_obj)
├── panel (lv_obj) - White container
│   ├── column[0] (lv_obj) - Left column
│   │   ├── floor_row[34] (lv_obj)
│   │   │   ├── btn_up (lv_btn) - UP button
│   │   │   ├── floor_card (lv_btn) - Floor number card
│   │   │   │   └── label (lv_label) - "34"
│   │   │   └── btn_down (lv_btn) - DOWN button
│   │   ├── floor_row[33]...
│   │   └── floor_row[23]
│   │
│   ├── column[1] (lv_obj) - Middle column
│   │   ├── floor_row[22]...
│   │   └── floor_row[12]
│   │
│   └── column[2] (lv_obj) - Right column
│       ├── floor_row[11]...
│       ├── floor_row[1]
│       ├── floor_row[P3] (37)
│       ├── floor_row[P2] (36)
│       └── floor_row[P1] (35)
│
└── nav_bar (lv_obj) - Bottom navigation
    ├── nav_btn[0] (lv_btn) - "SHAFT"
    ├── nav_btn[1] (lv_btn) - "GRID"
    └── nav_btn[2] (lv_btn) - "CONTROL"
```

## Component Specifications

### 1. Main Screen (`shaft_screen`)
```c
Type:        lv_obj
Size:        480 × 800 (full screen)
Background:  #667eea (purple)
Flags:       ~LV_OBJ_FLAG_SCROLLABLE
Padding:     0
```

### 2. Panel Container (`panel`)
```c
Type:        lv_obj
Size:        460 × 720
Alignment:   LV_ALIGN_TOP_MID, offset_y: -4
Background:  #FFFFFF (white)
Radius:      12px
Padding:     16px
Border:      none
Flags:       ~LV_OBJ_FLAG_SCROLLABLE
```

### 3. Column Containers (`columns[0-2]`)
```c
Type:           lv_obj
Size:           ~133 × 624 (auto-calculated)
Position:       margin: 12px, gap: 12px
Background:     LV_OPA_TRANSP
Border:         none
Padding:        0
Row padding:    4px
Flex flow:      LV_FLEX_FLOW_COLUMN
Flex align:     LV_FLEX_ALIGN_START
Flags:          ~LV_OBJ_FLAG_SCROLLABLE
```

**Width Calculation:**
```
usable_width = panel_width - 2*margin - gap*(columns-1)
             = 460 - 2*12 - 12*2
             = 460 - 24 - 24
             = 412px

column_width = usable_width / 3
             = 412 / 3
             = ~137px per column
```

**Height Calculation:**
```
column_height = panel_height - 64
              = 720 - 64
              = 656px (adjusted to 624px if needed)
```

### 4. Floor Row (`floor_row`)
```c
Type:           lv_obj
Size:           100% width × 34px height
Background:     LV_OPA_TRANSP
Border:         none
Padding left:   4px
Padding right:  4px
Column gap:     6px
Flex flow:      LV_FLEX_FLOW_ROW
Flex align:     LV_FLEX_ALIGN_SPACE_BETWEEN,
                LV_FLEX_ALIGN_CENTER,
                LV_FLEX_ALIGN_CENTER
Flags:          ~LV_OBJ_FLAG_SCROLLABLE

Children (in order):
  1. UP button (28×28)
  2. Floor card (58×32, flex_grow=1)
  3. DOWN button (28×28)
```

### 5. UP/DOWN Call Buttons (`btn_up`, `btn_down`)
```c
Type:           lv_btn
Size:           28 × 28
Background:     LV_OPA_TRANSP
Border:         none
Padding:        0
Radius:         0

Symbol:         LV_SYMBOL_UP or LV_SYMBOL_DOWN
Symbol color:   #9ea3b4 (inactive)
                #2ecc71 (UP active)
                #e74c3c (DOWN active)

Events:         LV_EVENT_CLICKED → call_button_cb
User data:      (floor | (mask << 8))

Special cases:
  - btn_up hidden if floor >= 34
  - btn_down hidden if floor <= 1
```

### 6. Floor Card (`floor_card`)
```c
Type:           lv_btn (with checkable behavior)
Size:           58 × 32
Background:     #34495e (normal)
                #3498db (current floor)
Border:         none
Outline:        2px white @ 80% opacity (current floor only)
Radius:         8px
Padding:        4px
Flex grow:      1

Events:         LV_EVENT_CLICKED → floor_card_cb
User data:      floor number

Child:          lv_label (floor number)
```

### 7. Floor Label (`label`)
```c
Type:           lv_label
Text:           "1"-"34" or "P3", "P2", "P1"
Font:           lv_font_montserrat_22
Color:          #FFFFFF (normal)
                #f39c12 (LOAD active)
Alignment:      LV_ALIGN_CENTER
```

**Floor Label Logic:**
```c
if (floor >= 35 && floor <= 37) {
    // Parking floors
    labels = {"P3" (floor 35), "P2" (36), "P1" (37)}
} else {
    // Standard floors
    snprintf(buf, sizeof(buf), "%u", floor);
}
```

### 8. Navigation Bar (`nav_bar`)
```c
Type:           lv_obj
Size:           480 × 60
Alignment:      LV_ALIGN_BOTTOM_MID, offset: 0
Background:     #34495e
Radius:         0
Padding:        10px
Flags:          ~LV_OBJ_FLAG_SCROLLABLE

Children:       3 nav buttons (140×40 each)
```

### 9. Navigation Buttons (`nav_btn[0-2]`)
```c
Type:           lv_btn
Size:           140 × 40
Background:     #2c3e50 (inactive)
                #3498db (active)
Radius:         10px
Border:         none
Font:           lv_font_montserrat_18
Text color:     #FFFFFF

Labels:         "SHAFT", "GRID", "CONTROL"
Events:         LV_EVENT_CLICKED → nav_btn_cb
User data:      button index (0, 1, 2)

Active:         nav_btn[0] ("SHAFT") by default
```

## Floor Distribution Across Columns

**Total floors**: 37 (34 standard + 3 parking)

**Column distribution**:
```
Column 0 (left):   Floors 34-23 (12 floors)
Column 1 (middle): Floors 22-12 (11 floors)
Column 2 (right):  Floors 11-1, P3, P2, P1 (14 floors)
```

**Floor order** (top to bottom):
```
34, 33, 32, ..., 3, 2, 1, P3, P2, P1
```

## State Management

### Floor State Tracking
```c
struct FloorState {
    bool upActive;      // UP call active
    bool downActive;    // DOWN call active
    bool loadActive;    // LOAD call active (changes text color)
    int8_t rssi;        // Signal strength
};

FloorState floorStates[TOTAL_FLOORS + 1];
```

### Current Floor
```c
uint8_t currentElevatorFloor = 1;

// When updated:
// - Remove style_floor_current from all floor cards
// - Add style_floor_current to new current floor card
```

### Widget Tracking
```c
struct FloorWidgets {
    lv_obj_t *card;     // Floor card button
    lv_obj_t *label;    // Floor number label
    lv_obj_t *btnUp;    // UP button (null if floor >= 34)
    lv_obj_t *btnDown;  // DOWN button (null if floor <= 1)
};

FloorWidgets floor_widgets[TOTAL_FLOORS + 1];
```

## Touch Targets

All touch targets meet minimum 28×28px requirement:
- UP/DOWN buttons: 28×28 ✓
- Floor cards: 58×32 ✓
- Nav buttons: 140×40 ✓

## Responsive Calculations

All sizes are calculated dynamically:
```c
lv_coord_t usable_width = panel_width - 2*margin - gap*(columns-1);
lv_coord_t column_width = usable_width / kColumnCount;
lv_coord_t column_height = panel_height - 64;
```

This ensures proper layout even if panel dimensions change.
