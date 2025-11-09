# Event Handlers & Callbacks

## Event Flow Overview

```
User Touch → LVGL Event → Callback Function → Update UI → Notify Gateway
                                                    ↓
                                            I2C Command Sent
```

## Event Callbacks

### 1. Floor Card Click (LOAD Toggle)

**Trigger:** User taps floor number card
**Purpose:** Toggle LOAD call on/off
**File:** `elevator_ui.cpp:129-141`

```cpp
void floor_card_cb(lv_event_t *e) {
    lv_obj_t *card = lv_event_get_target(e);
    uint8_t floor = static_cast<uint8_t>(
        reinterpret_cast<uintptr_t>(lv_event_get_user_data(e))
    );

    // Toggle checked state
    bool now_active = !lv_obj_has_state(card, LV_STATE_CHECKED);
    if (now_active) {
        lv_obj_add_state(card, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(card, LV_STATE_CHECKED);
    }

    // Update visual state
    set_load_state(floor, now_active);

    // Notify external handler
    notify_handler(floor, CALL_LOAD, now_active);
}
```

**Event Type:** `LV_EVENT_CLICKED`
**User Data:** Floor number (1-37)
**Visual Change:** Text color → Orange (#f39c12) when active

**Registration:**
```cpp
lv_obj_add_event_cb(card, floor_card_cb, LV_EVENT_CLICKED,
                    (void *)(uintptr_t)floor);
```

---

### 2. Call Button Click (UP/DOWN)

**Trigger:** User taps ▲ or ▼ button
**Purpose:** Toggle UP or DOWN call
**File:** `elevator_ui.cpp:117-127`

```cpp
void call_button_cb(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    uint32_t data = (uint32_t)lv_event_get_user_data(e);
    uint8_t floor = data & 0xFF;
    CallMask mask = static_cast<CallMask>((data >> 8) & 0xFF);

    // Check current state
    bool is_active = lv_obj_has_state(btn, LV_STATE_CHECKED);

    // Update button color
    set_button_state(btn, !is_active,
                     (mask == CALL_UP) ? UI_COLOR_UP : UI_COLOR_DOWN,
                     lv_color_hex(0x9ea3b4));

    // Notify external handler
    notify_handler(floor, mask, !is_active);
}
```

**Event Type:** `LV_EVENT_CLICKED`
**User Data Format:**
```
Bits 0-7:   Floor number (1-37)
Bits 8-15:  Call type (0x01=UP, 0x02=DOWN)
```

**Visual Change:**
- Inactive: #9ea3b4 (gray)
- Active UP: #2ecc71 (green)
- Active DOWN: #e74c3c (red)

**Registration:**
```cpp
lv_obj_add_event_cb(btn, call_button_cb, LV_EVENT_CLICKED,
                    (void *)(uintptr_t)(floor | (mask << 8)));
```

---

### 3. Navigation Button Click

**Trigger:** User taps SHAFT/GRID/CONTROL button
**Purpose:** Switch between views
**File:** `elevator_ui.cpp:154-169`

```cpp
void nav_btn_cb(lv_event_t *e) {
    uint8_t idx = static_cast<uint8_t>(
        reinterpret_cast<uintptr_t>(lv_event_get_user_data(e))
    );

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

    // Update active button style
    set_active_nav(0);  // Always show SHAFT as active (only view implemented)
}
```

**Event Type:** `LV_EVENT_CLICKED`
**User Data:** Button index (0=SHAFT, 1=GRID, 2=CONTROL)
**Current Status:** Only SHAFT view implemented

**Registration:**
```cpp
lv_obj_add_event_cb(btn, nav_btn_cb, LV_EVENT_CLICKED,
                    (void *)(uintptr_t)i);
```

---

## Helper Functions

### set_button_state()

**Purpose:** Update UP/DOWN button visual state
**File:** `elevator_ui.cpp:77-85`

```cpp
void set_button_state(lv_obj_t *btn, bool active,
                      lv_color_t active_color,
                      lv_color_t inactive_color) {
    if (!btn) return;
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    if (!label) return;
    lv_obj_set_style_text_color(label,
                                active ? active_color : inactive_color,
                                0);
}
```

**Usage:**
```cpp
set_button_state(floor_widgets[15].btnUp, true,
                 UI_COLOR_UP, lv_color_hex(0x9ea3b4));
```

---

### set_load_state()

**Purpose:** Update floor card text color for LOAD state
**File:** `elevator_ui.cpp:68-75`

```cpp
void set_load_state(uint8_t floor, bool active) {
    if (floor < kMinFloor || floor > kMaxFloor) return;
    lv_obj_t *label = floor_widgets[floor].label;
    if (!label) return;
    lv_obj_set_style_text_color(label,
                                active ? UI_COLOR_LOAD : lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN);
}
```

---

### notify_handler()

**Purpose:** Forward events to external callback
**File:** `elevator_ui.cpp:87-102`

```cpp
void notify_handler(uint8_t floor, CallMask type, bool active) {
    if (!call_handler) return;

    ElevatorCallType mapped = ElevatorCallType::Up;
    switch (type) {
        case CALL_UP:   mapped = ElevatorCallType::Up; break;
        case CALL_DOWN: mapped = ElevatorCallType::Down; break;
        case CALL_LOAD: mapped = ElevatorCallType::Load; break;
    }

    call_handler(floor, mapped, active);
}
```

**Integration with main.cpp:**
```cpp
// In main.cpp:255-273
static void handleUICall(uint8_t floor, ElevatorCallType type, bool active) {
    uint8_t mask = 0xFF;
    switch (type) {
        case ElevatorCallType::Up:   mask = 0x01; break;
        case ElevatorCallType::Down: mask = 0x02; break;
        case ElevatorCallType::Load: mask = 0x04; break;
    }

    if (!active) {
        sendClearCommand(floor, mask);
        elevator_ui_log_message("Display cleared call via touch");
    }
}
```

---

### highlight_current_floor()

**Purpose:** Update current elevator floor highlighting
**File:** `elevator_ui.cpp:104-115`

```cpp
void highlight_current_floor() {
    // Remove highlight from all floors
    for (uint8_t f = kMinFloor; f <= kMaxFloor; ++f) {
        if (!floor_widgets[f].card) continue;
        lv_obj_remove_style(floor_widgets[f].card, &style_floor_current, 0);
    }

    // Add highlight to current floor
    if (current_floor >= kMinFloor && current_floor <= kMaxFloor) {
        if (floor_widgets[current_floor].card) {
            lv_obj_add_style(floor_widgets[current_floor].card,
                            &style_floor_current, 0);
        }
    }
}
```

---

### set_active_nav()

**Purpose:** Update navigation button active state
**File:** `elevator_ui.cpp:143-152`

```cpp
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
```

---

## Public API Functions

### elevator_ui_init()

**Purpose:** Initialize entire UI
**File:** `elevator_ui.cpp:338-342`

```cpp
void elevator_ui_init(void) {
    build_shaft_screen();
    highlight_current_floor();
    log_msg("SHAFT view ready");
}
```

**Call from:** `main.cpp:94`

---

### elevator_ui_set_call_handler()

**Purpose:** Register external callback for UI events
**File:** `elevator_ui.cpp:344-346`

```cpp
void elevator_ui_set_call_handler(ElevatorCallHandler handler) {
    call_handler = handler;
}
```

**Usage in main.cpp:**
```cpp
elevator_ui_set_call_handler(handleUICall);
```

**Callback Signature:**
```cpp
typedef void (*ElevatorCallHandler)(uint8_t floor,
                                    ElevatorCallType type,
                                    bool active);
```

---

### elevator_ui_apply_floor_state()

**Purpose:** Update floor call states from gateway
**File:** `elevator_ui.cpp:348-359`

```cpp
void elevator_ui_apply_floor_state(uint8_t floor,
                                   bool up,
                                   bool down,
                                   bool load,
                                   bool log_event) {
    if (floor < kMinFloor || floor > kMaxFloor) return;
    set_button_state(floor_widgets[floor].btnUp, up, UI_COLOR_UP,
                     lv_color_hex(0x9ea3b4));
    set_button_state(floor_widgets[floor].btnDown, down, UI_COLOR_DOWN,
                     lv_color_hex(0x9ea3b4));
    set_load_state(floor, load);
}
```

**Called from:** `main.cpp:299` when gateway sends updates

---

### elevator_ui_set_current_floor()

**Purpose:** Update current elevator position
**File:** `elevator_ui.cpp:361-365`

```cpp
void elevator_ui_set_current_floor(uint8_t floor, bool log_event) {
    if (floor < kMinFloor || floor > kMaxFloor) return;
    current_floor = floor;
    highlight_current_floor();
}
```

**Called from:** `main.cpp:284` when gateway sends position

---

### elevator_ui_log_message()

**Purpose:** Log message to serial (placeholder for future log view)
**File:** `elevator_ui.cpp:367-369`

```cpp
void elevator_ui_log_message(const char *msg) {
    log_msg(msg);
}
```

---

## Event Flow Examples

### Example 1: User Presses UP Button on Floor 15

```
1. User touches UP button
   ↓
2. LVGL detects touch at coordinates (x, y)
   ↓
3. LVGL identifies target: floor_widgets[15].btnUp
   ↓
4. LV_EVENT_CLICKED triggered
   ↓
5. call_button_cb() called
   - floor = 15, mask = CALL_UP (0x01)
   ↓
6. set_button_state() changes color to green (#2ecc71)
   ↓
7. notify_handler() called with (15, CALL_UP, true)
   ↓
8. handleUICall() in main.cpp
   ↓
9. sendClearCommand() or I2C command sent to gateway
```

### Example 2: Gateway Sends Elevator Position Update

```
1. Gateway I2C packet received (main.cpp:276)
   ↓
2. Parse packet: floor=22, status=0x80 (elevator position)
   ↓
3. elevator_ui_set_current_floor(22) called
   ↓
4. highlight_current_floor() executes
   - Removes style_floor_current from all floors
   - Adds style_floor_current to floor 22
   ↓
5. Floor 22 card background changes to blue (#3498db)
   ↓
6. White outline appears around floor 22 card
```

### Example 3: User Taps Floor Card (LOAD Toggle)

```
1. User touches floor 8 card
   ↓
2. LV_EVENT_CLICKED on floor_widgets[8].card
   ↓
3. floor_card_cb() called with floor=8
   ↓
4. Toggle LV_STATE_CHECKED
   ↓
5. set_load_state(8, true) changes text to orange
   ↓
6. notify_handler(8, CALL_LOAD, true)
   ↓
7. handleUICall() sends I2C command
```

## I2C Communication Integration

### Sending Clear Command (Display → Gateway)

**File:** `main.cpp:307-313`

```cpp
static void sendClearCommand(uint8_t floor, uint8_t callTypeMask) {
    Wire.beginTransmission(I2C_MASTER_ADDRESS);  // 0x08
    Wire.write(floor);
    Wire.write(0x20);          // Clear command
    Wire.write(callTypeMask);  // 0x01=UP, 0x02=DOWN, 0x04=LOAD
    Wire.endTransmission();
}
```

### Receiving State Update (Gateway → Display)

**File:** `main.cpp:275-305`

```cpp
static void requestDataFromGateway() {
    Wire.requestFrom(I2C_MASTER_ADDRESS, sizeof(DisplayPacket));
    if (Wire.available() < sizeof(DisplayPacket)) return;

    DisplayPacket pkt;
    Wire.readBytes(reinterpret_cast<uint8_t *>(&pkt), sizeof(DisplayPacket));

    // Elevator position update
    if (pkt.status & 0x80) {
        currentElevatorFloor = pkt.floor;
        elevator_ui_set_current_floor(pkt.floor, false);
        return;
    }

    // Call state update
    if (pkt.floor < 1 || pkt.floor > TOTAL_FLOORS) return;

    bool up = pkt.status & 0x01;
    bool down = pkt.status & 0x02;
    bool load = pkt.status & 0x04;

    elevator_ui_apply_floor_state(pkt.floor, up, down, load, false);
}
```

**DisplayPacket Structure:**
```cpp
struct DisplayPacket {
    uint8_t floor;    // Floor number (1-37)
    uint8_t status;   // Bit0:UP, Bit1:DOWN, Bit2:LOAD, Bit7:ELEV_POS
    int8_t rssi;      // Signal strength
};
```

---

## Thread Safety

**Important:** All LVGL calls must happen from main loop thread!

```cpp
void loop() {
    // Update LVGL tick
    uint32_t now = millis();
    lv_tick_inc(now - lastTickUpdate);
    lastTickUpdate = now;

    // Process LVGL events (handles touch, callbacks, etc.)
    lv_timer_handler();

    // Your update logic
    if (new_data_available) {
        elevator_ui_set_current_floor(new_floor);  // ✓ Safe
    }

    delay(5);
}
```

**Do NOT call LVGL functions from:**
- I2C interrupts
- Timer interrupts
- Separate tasks (FreeRTOS)
