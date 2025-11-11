#include "elevator_ui.h"

#include "ui/ui.h"
#include "ui/screens.h"

#include <Arduino.h>

// Access the EEZ generated objects (defined in screens.c with C linkage)
extern "C" {
  extern objects_t objects;
}

namespace {
ElevatorCallHandler s_call_handler = nullptr;

// Floor mapping structure - maps floor number to UI objects
struct FloorUIObjects {
  lv_obj_t* row_container;     // Floor row container
  lv_obj_t* up_button;         // UP button object
  lv_obj_t* down_button;       // DOWN button object
  lv_obj_t* load_button;       // LOAD button object
  lv_obj_t* floor_label;       // Floor number label
};

// Array to store UI object mappings for all floors
FloorUIObjects floor_ui_map[TOTAL_FLOORS + 1];

// Colors for button states (from EEZ Studio design)
const lv_color_t COLOR_INACTIVE = lv_color_hex(0x000000);  // Black (default state)
const lv_color_t COLOR_LOAD_INACTIVE = lv_color_hex(0xFAFBFD); // Almost white (load default)
const lv_color_t COLOR_UP_ACTIVE = lv_color_hex(0x2ECC71); // Green (UP checked)
const lv_color_t COLOR_DOWN_ACTIVE = lv_color_hex(0xE74C3C); // Red (DOWN checked)
const lv_color_t COLOR_LOAD_ACTIVE = lv_color_hex(0x3498DB); // Blue (LOAD checked)

// Touch event handler
void button_event_handler(lv_event_t* e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code != LV_EVENT_CLICKED) return;

  void* user_data = lv_event_get_user_data(e);
  if (!user_data) return;

  // user_data format: (floor << 8) | button_type
  uint16_t data = reinterpret_cast<uintptr_t>(user_data);
  uint8_t floor = (data >> 8) & 0xFF;
  uint8_t button_type = data & 0xFF;

  if (!s_call_handler) {
    Serial.printf("Button clicked: Floor %u, Type %u (no handler set)\n", floor, button_type);
    return;
  }

  // Convert button type to ElevatorCallType
  ElevatorCallType call_type;
  switch (button_type) {
    case 1:
      call_type = ElevatorCallType::Up;
      break;
    case 2:
      call_type = ElevatorCallType::Down;
      break;
    case 3:
      call_type = ElevatorCallType::Load;
      break;
    default:
      return;
  }

  // Call the handler - toggle the call state
  Serial.printf("Button clicked: Floor %u, Type %u\n", floor, button_type);
  s_call_handler(floor, call_type, true);  // Activate call
}

// Helper function to attach touch handler to a button
void attach_button_handler(lv_obj_t* btn, uint8_t floor, uint8_t button_type) {
  if (!btn) return;

  // Create user data: (floor << 8) | button_type
  uint16_t user_data = (floor << 8) | button_type;

  lv_obj_add_event_cb(btn, button_event_handler, LV_EVENT_CLICKED,
                      reinterpret_cast<void*>(static_cast<uintptr_t>(user_data)));

  // Make the object clickable
  lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
}

// Get floor number label text
const char* get_floor_label_text(uint8_t floor) {
  static char label_buf[8];

  // Special floor mappings (from QUICK_START.md)
  if (floor == 253) return "P3";
  if (floor == 254) return "P2";
  if (floor == 255) return "P1";
  if (floor == 1) return "G";

  // Regular floors (1-based becomes 2-based: floor 1 = "1", floor 2 = "2", etc.)
  snprintf(label_buf, sizeof(label_buf), "%u", floor - 1);
  return label_buf;
}

// Initialize floor UI mappings
void init_floor_ui_mappings() {
  // Map each floor to its UI objects
  // Based on the EEZ UI structure from screens.h
  // Pattern for each floor:
  //   floor_ (row), obj0 (up), obj1 (down), floor_number_X (label), obj2 (load)

  // Floor 1: obj0=UP, obj1=LOAD(contains floor_number_1), obj2=DOWN
  floor_ui_map[1].row_container = objects.floor_;
  floor_ui_map[1].up_button = objects.obj0;
  floor_ui_map[1].load_button = objects.obj1;
  floor_ui_map[1].down_button = objects.obj2;
  floor_ui_map[1].floor_label = objects.floor_number_1;

  // Floor 2: obj3=UP, obj4=LOAD(contains floor_number_2), obj5=DOWN
  floor_ui_map[2].row_container = objects.floor__1;
  floor_ui_map[2].up_button = objects.obj3;
  floor_ui_map[2].load_button = objects.obj4;
  floor_ui_map[2].down_button = objects.obj5;
  floor_ui_map[2].floor_label = objects.floor_number_2;

  // Floor 3: obj6=UP, obj7=LOAD(contains floor_number_3), obj8=DOWN
  floor_ui_map[3].row_container = objects.floor__2;
  floor_ui_map[3].up_button = objects.obj6;
  floor_ui_map[3].load_button = objects.obj7;
  floor_ui_map[3].down_button = objects.obj8;
  floor_ui_map[3].floor_label = objects.floor_number_3;

  // Continue pattern for remaining floors...
  // For now, only mapping first 3 floors as example
  // You'll need to complete this for all 60 floors based on the actual UI structure

  // Configure floor buttons and labels
  uint8_t max_floor = (TOTAL_FLOORS < 3) ? TOTAL_FLOORS : 3;
  for (uint8_t i = 1; i <= max_floor; i++) {
    // Set floor label text
    if (floor_ui_map[i].floor_label) {
      lv_label_set_text(floor_ui_map[i].floor_label, get_floor_label_text(i));
    }

    // Attach touch handlers: UP=1, DOWN=2, LOAD=3
    attach_button_handler(floor_ui_map[i].up_button, i, 1);
    attach_button_handler(floor_ui_map[i].down_button, i, 2);
    attach_button_handler(floor_ui_map[i].load_button, i, 3);

    // Buttons use EEZ-defined colors via CHECKED state
    // Default state is already set by EEZ (black for UP/DOWN, white for LOAD)
    // We control them via lv_obj_add_state/lv_obj_clear_state with LV_STATE_CHECKED
  }
}

}  // namespace

void elevator_ui_init() {
  ui_init();
  init_floor_ui_mappings();
  Serial.println("Elevator UI initialized with floor mappings");
}

void elevator_ui_set_call_handler(ElevatorCallHandler handler) {
  s_call_handler = handler;
  Serial.println("Call handler registered");
}

void elevator_ui_apply_floor_state(uint8_t floor,
                                   bool up,
                                   bool down,
                                   bool load,
                                   bool log_event) {
  if (floor < 1 || floor > TOTAL_FLOORS) return;

  // Check if this floor has mapped UI objects
  if (!floor_ui_map[floor].row_container) {
    if (log_event) {
      Serial.printf("Floor %u: No UI mapping (up=%d, down=%d, load=%d)\n",
                    floor, up, down, load);
    }
    return;
  }

  // Update UP button state (uses EEZ-defined colors)
  if (floor_ui_map[floor].up_button) {
    if (up) {
      lv_obj_add_state(floor_ui_map[floor].up_button, LV_STATE_CHECKED);
    } else {
      lv_obj_clear_state(floor_ui_map[floor].up_button, LV_STATE_CHECKED);
    }
  }

  // Update DOWN button state (uses EEZ-defined colors)
  if (floor_ui_map[floor].down_button) {
    if (down) {
      lv_obj_add_state(floor_ui_map[floor].down_button, LV_STATE_CHECKED);
    } else {
      lv_obj_clear_state(floor_ui_map[floor].down_button, LV_STATE_CHECKED);
    }
  }

  // Update LOAD button state (uses EEZ-defined colors)
  if (floor_ui_map[floor].load_button) {
    if (load) {
      lv_obj_add_state(floor_ui_map[floor].load_button, LV_STATE_CHECKED);
    } else {
      lv_obj_clear_state(floor_ui_map[floor].load_button, LV_STATE_CHECKED);
    }
  }

  if (log_event) {
    Serial.printf("Floor %u UI updated: UP=%d DOWN=%d LOAD=%d\n", floor, up, down, load);
  }
}

void elevator_ui_set_current_floor(uint8_t floor, bool log_event) {
  // TODO: Highlight current elevator position
  // Could add a border or background color to the floor row
  if (log_event) {
    Serial.printf("Elevator position: Floor %u\n", floor);
  }
}

void elevator_ui_log_message(const char *msg) {
  if (msg) {
    Serial.println(msg);
    // TODO: Could add to an on-screen log widget if available
  }
}

void elevator_ui_tick(void) {
  ui_tick();
}

// Test mode functions
void elevator_ui_test_random_calls(uint8_t num_calls) {
  Serial.printf("Test mode: Activating %u random calls\n", num_calls);

  uint8_t max_floor = (TOTAL_FLOORS < 3) ? TOTAL_FLOORS : 3;
  for (uint8_t i = 0; i < num_calls; i++) {
    uint8_t floor = random(1, max_floor + 1);
    uint8_t button = random(1, 4);  // 1=UP, 2=DOWN, 3=LOAD

    bool up = (button == 1);
    bool down = (button == 2);
    bool load = (button == 3);

    elevator_ui_apply_floor_state(floor, up, down, load, true);
    delay(100);
  }
}
