#include "elevator_ui.h"

#include "ui/ui.h"

#include <Arduino.h>

namespace {
ElevatorCallHandler s_call_handler = nullptr;
}

void elevator_ui_init() {
  ui_init();
}

void elevator_ui_set_call_handler(ElevatorCallHandler handler) {
  s_call_handler = handler;
}

void elevator_ui_apply_floor_state(uint8_t,
                                   bool,
                                   bool,
                                   bool,
                                   bool) {
  // TODO: bind generated UI widgets to floor state
}

void elevator_ui_set_current_floor(uint8_t, bool) {}

void elevator_ui_log_message(const char *msg) {
  if (msg) {
    Serial.println(msg);
  }
}

void elevator_ui_tick(void) { ui_tick(); }
