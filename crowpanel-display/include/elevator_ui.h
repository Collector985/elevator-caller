#pragma once

#include <lvgl.h>
#include <stdint.h>

enum class ElevatorCallType : uint8_t {
  Up = 0x01,
  Down = 0x02,
  Load = 0x04,
};

using ElevatorCallHandler =
    void (*)(uint8_t floor, ElevatorCallType type, bool active);

void elevator_ui_init();
void elevator_ui_set_call_handler(ElevatorCallHandler handler);
void elevator_ui_apply_floor_state(uint8_t floor,
                                   bool up,
                                   bool down,
                                   bool load,
                                   bool log_event = false);
void elevator_ui_set_current_floor(uint8_t floor, bool log_event = false);
void elevator_ui_log_message(const char *msg);
void elevator_ui_tick(void);

// Test mode function
void elevator_ui_test_random_calls(uint8_t num_calls);
