/**
 * @file elevator_3screen.c
 * @brief 3-Screen LVGL Elevator System for 480x800 Display
 * 
 * SCREEN 1: Shaft View - Two columns of floors (16-30, 1-15) with call buttons
 *                        Current floor is highlighted (no car graphic)
 * SCREEN 2: Floor Grid - Complete floor status overview (8x4 grid)
 * SCREEN 3: Controls - Statistics, auto mode, and packet log
 */

#include "lvgl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLOOR_COUNT 30
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 800

// Colors
#define COLOR_BG lv_color_hex(0x667eea)
#define COLOR_PANEL lv_color_hex(0xFFFFFF)
#define COLOR_SHAFT lv_color_hex(0x2c3e50)
#define COLOR_ELEVATOR lv_color_hex(0x667eea)
#define COLOR_UP lv_color_hex(0x2ecc71)
#define COLOR_DOWN lv_color_hex(0xe74c3c)
#define COLOR_LOAD lv_color_hex(0xf39c12)
#define COLOR_ACTIVE lv_color_hex(0xFFFF00)
#define COLOR_NAV lv_color_hex(0x34495e)

// Call types
typedef enum {
    CALL_NONE = 0,
    CALL_UP = 1,
    CALL_DOWN = 2,
    CALL_LOAD = 4
} call_type_t;

// Elevator state
typedef struct {
    uint8_t current_floor;
    uint8_t target_floor;
    bool is_moving;
    bool auto_mode;
    uint8_t calls[FLOOR_COUNT + 1];
    uint32_t total_calls;
    uint32_t active_calls;
    uint32_t auto_cleared;
} elev_state_t;

// Screens
static lv_obj_t *screen_shaft;
static lv_obj_t *screen_grid;
static lv_obj_t *screen_controls;

// Shaft screen elements
static lv_obj_t *shaft_container;
static lv_obj_t *shaft_floor_labels[FLOOR_COUNT + 1];
static lv_obj_t *shaft_buttons[FLOOR_COUNT + 1][3];

// Grid screen elements
static lv_obj_t *grid_cells[FLOOR_COUNT + 1];
static lv_obj_t *grid_indicators[FLOOR_COUNT + 1][3];

// Control screen elements
static lv_obj_t *stat_labels[6];
static lv_obj_t *log_area;
static lv_obj_t *btn_auto;

// State
static elev_state_t state = {
    .current_floor = 1,
    .target_floor = 1,
    .is_moving = false,
    .auto_mode = false,
    .total_calls = 0,
    .active_calls = 0,
    .auto_cleared = 0
};

// Forward declarations
static void update_elevator_position(void);
static void update_stats(void);
static void place_call(uint8_t floor, call_type_t type);
static void clear_call(uint8_t floor, call_type_t type);
static void log_msg(const char *msg);
static void switch_screen(uint8_t screen_num);

// =============================================================================
// UTILITY FUNCTIONS
// =============================================================================

static int16_t calc_rssi(uint8_t floor) {
    int16_t dist = abs(state.current_floor - floor);
    int16_t rssi = -50 - (dist * 10) + ((rand() % 20) - 10);
    return (rssi < -120) ? -120 : rssi;
}

static void log_msg(const char *msg) {
    if (!log_area) return;
    
    static uint32_t count = 0;
    char buf[128];
    snprintf(buf, sizeof(buf), "[%04lu] %s\n", count++, msg);
    lv_textarea_add_text(log_area, buf);
    
    // Trim to last 600 chars
    const char *text = lv_textarea_get_text(log_area);
    if (strlen(text) > 600) {
        lv_textarea_set_text(log_area, text + strlen(text) - 600);
    }
}

// =============================================================================
// CALL MANAGEMENT
// =============================================================================

static void place_call(uint8_t floor, call_type_t type) {
    if (floor < 1 || floor > FLOOR_COUNT || (state.calls[floor] & type)) return;
    
    state.calls[floor] |= type;
    state.total_calls++;
    state.active_calls++;
    
    // Update shaft buttons
    int idx = (type == CALL_UP) ? 0 : (type == CALL_DOWN) ? 1 : 2;
    if (shaft_buttons[floor][idx]) {
        lv_obj_add_state(shaft_buttons[floor][idx], LV_STATE_CHECKED);
    }
    
    // Update grid indicators
    if (grid_indicators[floor][idx]) {
        lv_obj_clear_flag(grid_indicators[floor][idx], LV_OBJ_FLAG_HIDDEN);
    }
    
    // Log
    char msg[64];
    const char *type_str = (type == CALL_UP) ? "UP" : (type == CALL_DOWN) ? "DOWN" : "LOAD";
    snprintf(msg, sizeof(msg), "CALL: Floor %d %s (RSSI: %d dBm)", floor, type_str, calc_rssi(floor));
    log_msg(msg);
    
    update_stats();
}

static void clear_call(uint8_t floor, call_type_t type) {
    if (floor < 1 || floor > FLOOR_COUNT || !(state.calls[floor] & type)) return;
    
    state.calls[floor] &= ~type;
    state.active_calls--;
    
    // Update shaft buttons
    int idx = (type == CALL_UP) ? 0 : (type == CALL_DOWN) ? 1 : 2;
    if (shaft_buttons[floor][idx]) {
        lv_obj_clear_state(shaft_buttons[floor][idx], LV_STATE_CHECKED);
    }
    
    // Update grid indicators
    if (grid_indicators[floor][idx]) {
        lv_obj_add_flag(grid_indicators[floor][idx], LV_OBJ_FLAG_HIDDEN);
    }
    
    update_stats();
}

static void clear_floor(uint8_t floor) {
    if (state.calls[floor] & CALL_UP) clear_call(floor, CALL_UP);
    if (state.calls[floor] & CALL_DOWN) clear_call(floor, CALL_DOWN);
    if (state.calls[floor] & CALL_LOAD) clear_call(floor, CALL_LOAD);
}

// =============================================================================
// ELEVATOR CONTROL
// =============================================================================

static void update_elevator_position(void) {
    // Clear all floor highlights
    for (uint8_t f = 1; f <= FLOOR_COUNT; f++) {
        if (shaft_floor_labels[f]) {
            lv_obj_set_style_bg_color(shaft_floor_labels[f], lv_color_hex(0x34495e), 0);
            lv_obj_set_style_text_color(shaft_floor_labels[f], lv_color_hex(0xFFFFFF), 0);
        }
    }
    
    // Highlight current floor
    if (shaft_floor_labels[state.current_floor]) {
        lv_obj_set_style_bg_color(shaft_floor_labels[state.current_floor], COLOR_ELEVATOR, 0);
        lv_obj_set_style_text_color(shaft_floor_labels[state.current_floor], lv_color_hex(0xFFFFFF), 0);
    }
    
    update_stats();
}

static void update_stats(void) {
    if (!stat_labels[0]) return;
    
    char buf[32];
    snprintf(buf, sizeof(buf), "Total Calls: %lu", state.total_calls);
    lv_label_set_text(stat_labels[0], buf);
    
    snprintf(buf, sizeof(buf), "Active Calls: %lu", state.active_calls);
    lv_label_set_text(stat_labels[1], buf);
    
    snprintf(buf, sizeof(buf), "Current Floor: %d", state.current_floor);
    lv_label_set_text(stat_labels[2], buf);
    
    snprintf(buf, sizeof(buf), "Target Floor: %d", state.target_floor);
    lv_label_set_text(stat_labels[3], buf);
    
    snprintf(buf, sizeof(buf), "Auto Cleared: %lu", state.auto_cleared);
    lv_label_set_text(stat_labels[4], buf);
    
    snprintf(buf, sizeof(buf), "Status: %s", state.is_moving ? "MOVING" : "IDLE");
    lv_label_set_text(stat_labels[5], buf);
}

// =============================================================================
// TIMERS
// =============================================================================

static void elevator_timer_cb(lv_timer_t *t) {
    if (!state.is_moving || state.current_floor == state.target_floor) {
        state.is_moving = false;
        return;
    }
    
    // Move one floor
    if (state.current_floor < state.target_floor) {
        state.current_floor++;
    } else {
        state.current_floor--;
    }
    
    update_elevator_position();
    
    char msg[64];
    snprintf(msg, sizeof(msg), "POSITION: Floor %d", state.current_floor);
    log_msg(msg);
    
    // Auto-clear if close
    for (int i = 0; i < 3; i++) {
        call_type_t type = (1 << i);
        if (state.calls[state.current_floor] & type) {
            if (calc_rssi(state.current_floor) > -70) {
                clear_call(state.current_floor, type);
                state.auto_cleared++;
                snprintf(msg, sizeof(msg), "AUTO-CLEAR: Floor %d", state.current_floor);
                log_msg(msg);
            }
        }
    }
}

static void auto_mode_timer_cb(lv_timer_t *t) {
    if (!state.auto_mode || state.is_moving) return;
    
    // Find nearest call
    int16_t nearest = -1;
    int16_t min_dist = 999;
    
    for (uint8_t f = 1; f <= FLOOR_COUNT; f++) {
        if (state.calls[f]) {
            int16_t dist = abs(state.current_floor - f);
            if (dist < min_dist) {
                min_dist = dist;
                nearest = f;
            }
        }
    }
    
    if (nearest > 0) {
        state.target_floor = nearest;
        state.is_moving = true;
        
        char msg[64];
        snprintf(msg, sizeof(msg), "AUTO: Moving to floor %d", nearest);
        log_msg(msg);
    }
}

// =============================================================================
// EVENT HANDLERS
// =============================================================================

static void call_btn_cb(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    uint32_t data = (uint32_t)lv_obj_get_user_data(btn);
    uint8_t floor = data & 0xFF;
    call_type_t type = (call_type_t)((data >> 8) & 0xFF);
    
    if (state.calls[floor] & type) {
        clear_call(floor, type);
    } else {
        place_call(floor, type);
    }
}

static void grid_cell_cb(lv_event_t *e) {
    lv_obj_t *cell = lv_event_get_target(e);
    uint8_t floor = (uint8_t)(uint32_t)lv_obj_get_user_data(cell);
    
    if (state.calls[floor]) {
        clear_floor(floor);
        char msg[64];
        snprintf(msg, sizeof(msg), "CLEAR: Floor %d all calls", floor);
        log_msg(msg);
    }
}

static void nav_btn_cb(lv_event_t *e) {
    lv_obj_t *btn = lv_event_get_target(e);
    uint8_t screen_num = (uint8_t)(uint32_t)lv_obj_get_user_data(btn);
    switch_screen(screen_num);
}

static void auto_mode_cb(lv_event_t *e) {
    state.auto_mode = !state.auto_mode;
    
    if (state.auto_mode) {
        lv_label_set_text(lv_obj_get_child(btn_auto, 0), "STOP AUTO");
        lv_obj_set_style_bg_color(btn_auto, COLOR_DOWN, 0);
        log_msg("AUTO MODE: Started");
    } else {
        lv_label_set_text(lv_obj_get_child(btn_auto, 0), "AUTO MODE");
        lv_obj_set_style_bg_color(btn_auto, COLOR_UP, 0);
        state.is_moving = false;
        log_msg("AUTO MODE: Stopped");
    }
}

static void clear_all_cb(lv_event_t *e) {
    for (uint8_t f = 1; f <= FLOOR_COUNT; f++) {
        clear_floor(f);
    }
    log_msg("CLEAR ALL: All calls cleared");
}

static void random_calls_cb(lv_event_t *e) {
    for (int i = 0; i < 5; i++) {
        uint8_t floor = (rand() % FLOOR_COUNT) + 1;
        call_type_t type = (1 << (rand() % 3));
        place_call(floor, type);
    }
    log_msg("RANDOM: 5 calls placed");
}

// =============================================================================
// SCREEN CREATION
// =============================================================================

static void create_nav_bar(lv_obj_t *parent) {
    lv_obj_t *nav = lv_obj_create(parent);
    lv_obj_set_size(nav, 480, 60);
    lv_obj_align(nav, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(nav, COLOR_NAV, 0);
    lv_obj_set_style_radius(nav, 0, 0);
    lv_obj_clear_flag(nav, LV_OBJ_FLAG_SCROLLABLE);
    
    const char *labels[] = {"SHAFT", "GRID", "CONTROL"};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *btn = lv_btn_create(nav);
        lv_obj_set_size(btn, 150, 50);
        lv_obj_set_pos(btn, 10 + (i * 157), 5);
        lv_obj_add_event_cb(btn, nav_btn_cb, LV_EVENT_CLICKED, (void*)(uint32_t)i);
        
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, labels[i]);
        lv_obj_center(label);
    }
}

static void create_screen_shaft(void) {
    screen_shaft = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_shaft, COLOR_BG, 0);
    
    // Main container
    shaft_container = lv_obj_create(screen_shaft);
    lv_obj_set_size(shaft_container, 460, 720);
    lv_obj_align(shaft_container, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_style_bg_color(shaft_container, COLOR_PANEL, 0);
    lv_obj_set_scroll_dir(shaft_container, LV_DIR_VER);
    
    // Create two columns of floors (floors 16-30 on left, 1-15 on right)
    // Left column: Floors 30 down to 16
    int row = 0;
    for (uint8_t f = 30; f >= 16; f--) {
        int y = 5 + (row * 48);
        
        // Floor number box (clickable to show it's the current floor)
        lv_obj_t *floor_box = lv_obj_create(shaft_container);
        lv_obj_set_size(floor_box, 40, 40);
        lv_obj_set_pos(floor_box, 5, y);
        lv_obj_set_style_bg_color(floor_box, lv_color_hex(0x34495e), 0);
        lv_obj_set_style_border_width(floor_box, 2, 0);
        lv_obj_clear_flag(floor_box, LV_OBJ_FLAG_SCROLLABLE);
        shaft_floor_labels[f] = floor_box;
        
        lv_obj_t *num = lv_label_create(floor_box);
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", f);
        lv_label_set_text(num, buf);
        lv_obj_set_style_text_color(num, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_font(num, &lv_font_montserrat_16, 0);
        lv_obj_center(num);
        
        // UP button
        if (f < 30) {
            lv_obj_t *btn = lv_btn_create(shaft_container);
            lv_obj_set_size(btn, 50, 40);
            lv_obj_set_pos(btn, 50, y);
            lv_obj_set_style_bg_color(btn, COLOR_UP, 0);
            lv_obj_set_style_bg_color(btn, COLOR_ACTIVE, LV_STATE_CHECKED);
            lv_obj_add_event_cb(btn, call_btn_cb, LV_EVENT_CLICKED, NULL);
            lv_obj_set_user_data(btn, (void*)(uint32_t)(f | (CALL_UP << 8)));
            shaft_buttons[f][0] = btn;
            
            lv_obj_t *lbl = lv_label_create(btn);
            lv_label_set_text(lbl, "UP");
            lv_obj_set_style_text_font(lbl, &lv_font_montserrat_12, 0);
            lv_obj_center(lbl);
        }
        
        // DOWN button
        if (f > 1) {
            lv_obj_t *btn = lv_btn_create(shaft_container);
            lv_obj_set_size(btn, 50, 40);
            lv_obj_set_pos(btn, 105, y);
            lv_obj_set_style_bg_color(btn, COLOR_DOWN, 0);
            lv_obj_set_style_bg_color(btn, COLOR_ACTIVE, LV_STATE_CHECKED);
            lv_obj_add_event_cb(btn, call_btn_cb, LV_EVENT_CLICKED, NULL);
            lv_obj_set_user_data(btn, (void*)(uint32_t)(f | (CALL_DOWN << 8)));
            shaft_buttons[f][1] = btn;
            
            lv_obj_t *lbl = lv_label_create(btn);
            lv_label_set_text(lbl, "DOWN");
            lv_obj_set_style_text_font(lbl, &lv_font_montserrat_10, 0);
            lv_obj_center(lbl);
        }
        
        // LOAD button
        lv_obj_t *btn = lv_btn_create(shaft_container);
        lv_obj_set_size(btn, 50, 40);
        lv_obj_set_pos(btn, 160, y);
        lv_obj_set_style_bg_color(btn, COLOR_LOAD, 0);
        lv_obj_set_style_bg_color(btn, COLOR_ACTIVE, LV_STATE_CHECKED);
        lv_obj_add_event_cb(btn, call_btn_cb, LV_EVENT_CLICKED, NULL);
        lv_obj_set_user_data(btn, (void*)(uint32_t)(f | (CALL_LOAD << 8)));
        shaft_buttons[f][2] = btn;
        
        lv_obj_t *lbl = lv_label_create(btn);
        lv_label_set_text(lbl, "LOAD");
        lv_obj_set_style_text_font(lbl, &lv_font_montserrat_10, 0);
        lv_obj_center(lbl);
        
        row++;
    }
    
    // Right column: Floors 15 down to 1
    row = 0;
    for (uint8_t f = 15; f >= 1; f--) {
        int y = 5 + (row * 48);
        
        // Floor number box
        lv_obj_t *floor_box = lv_obj_create(shaft_container);
        lv_obj_set_size(floor_box, 40, 40);
        lv_obj_set_pos(floor_box, 220, y);
        lv_obj_set_style_bg_color(floor_box, lv_color_hex(0x34495e), 0);
        lv_obj_set_style_border_width(floor_box, 2, 0);
        lv_obj_clear_flag(floor_box, LV_OBJ_FLAG_SCROLLABLE);
        shaft_floor_labels[f] = floor_box;
        
        lv_obj_t *num = lv_label_create(floor_box);
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", f);
        lv_label_set_text(num, buf);
        lv_obj_set_style_text_color(num, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_text_font(num, &lv_font_montserrat_16, 0);
        lv_obj_center(num);
        
        // UP button
        if (f < 30) {
            lv_obj_t *btn = lv_btn_create(shaft_container);
            lv_obj_set_size(btn, 50, 40);
            lv_obj_set_pos(btn, 265, y);
            lv_obj_set_style_bg_color(btn, COLOR_UP, 0);
            lv_obj_set_style_bg_color(btn, COLOR_ACTIVE, LV_STATE_CHECKED);
            lv_obj_add_event_cb(btn, call_btn_cb, LV_EVENT_CLICKED, NULL);
            lv_obj_set_user_data(btn, (void*)(uint32_t)(f | (CALL_UP << 8)));
            shaft_buttons[f][0] = btn;
            
            lv_obj_t *lbl = lv_label_create(btn);
            lv_label_set_text(lbl, "UP");
            lv_obj_set_style_text_font(lbl, &lv_font_montserrat_12, 0);
            lv_obj_center(lbl);
        }
        
        // DOWN button
        if (f > 1) {
            lv_obj_t *btn = lv_btn_create(shaft_container);
            lv_obj_set_size(btn, 50, 40);
            lv_obj_set_pos(btn, 320, y);
            lv_obj_set_style_bg_color(btn, COLOR_DOWN, 0);
            lv_obj_set_style_bg_color(btn, COLOR_ACTIVE, LV_STATE_CHECKED);
            lv_obj_add_event_cb(btn, call_btn_cb, LV_EVENT_CLICKED, NULL);
            lv_obj_set_user_data(btn, (void*)(uint32_t)(f | (CALL_DOWN << 8)));
            shaft_buttons[f][1] = btn;
            
            lv_obj_t *lbl = lv_label_create(btn);
            lv_label_set_text(lbl, "DOWN");
            lv_obj_set_style_text_font(lbl, &lv_font_montserrat_10, 0);
            lv_obj_center(lbl);
        }
        
        // LOAD button
        lv_obj_t *btn = lv_btn_create(shaft_container);
        lv_obj_set_size(btn, 50, 40);
        lv_obj_set_pos(btn, 375, y);
        lv_obj_set_style_bg_color(btn, COLOR_LOAD, 0);
        lv_obj_set_style_bg_color(btn, COLOR_ACTIVE, LV_STATE_CHECKED);
        lv_obj_add_event_cb(btn, call_btn_cb, LV_EVENT_CLICKED, NULL);
        lv_obj_set_user_data(btn, (void*)(uint32_t)(f | (CALL_LOAD << 8)));
        shaft_buttons[f][2] = btn;
        
        lv_obj_t *lbl = lv_label_create(btn);
        lv_label_set_text(lbl, "LOAD");
        lv_obj_set_style_text_font(lbl, &lv_font_montserrat_10, 0);
        lv_obj_center(lbl);
        
        row++;
    }
    
    create_nav_bar(screen_shaft);
}

static void create_screen_grid(void) {
    screen_grid = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_grid, COLOR_BG, 0);
    
    // Grid container (scrollable)
    lv_obj_t *grid = lv_obj_create(screen_grid);
    lv_obj_set_size(grid, 460, 720);
    lv_obj_align(grid, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_set_flex_flow(grid, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_all(grid, 10, 0);
    lv_obj_set_style_pad_gap(grid, 5, 0);
    
    // 8 columns, 30 floors
    for (uint8_t f = FLOOR_COUNT; f >= 1; f--) {
        lv_obj_t *cell = lv_btn_create(grid);
        lv_obj_set_size(cell, 50, 60);
        lv_obj_set_style_bg_color(cell, lv_color_hex(0xECF0F1), 0);
        lv_obj_add_event_cb(cell, grid_cell_cb, LV_EVENT_CLICKED, NULL);
        lv_obj_set_user_data(cell, (void*)(uint32_t)f);
        grid_cells[f] = cell;
        
        // Floor number
        lv_obj_t *num = lv_label_create(cell);
        char buf[8];
        snprintf(buf, sizeof(buf), "%d", f);
        lv_label_set_text(num, buf);
        lv_obj_set_style_text_font(num, &lv_font_montserrat_14, 0);
        lv_obj_align(num, LV_ALIGN_TOP_MID, 0, 3);
        
        // Indicators
        for (int i = 0; i < 3; i++) {
            lv_obj_t *ind = lv_obj_create(cell);
            lv_obj_set_size(ind, 10, 10);
            lv_obj_set_pos(ind, 5 + (i * 13), 35);
            lv_obj_set_style_radius(ind, LV_RADIUS_CIRCLE, 0);
            lv_obj_set_style_border_width(ind, 0, 0);
            
            if (i == 0) lv_obj_set_style_bg_color(ind, COLOR_UP, 0);
            else if (i == 1) lv_obj_set_style_bg_color(ind, COLOR_DOWN, 0);
            else lv_obj_set_style_bg_color(ind, COLOR_LOAD, 0);
            
            lv_obj_add_flag(ind, LV_OBJ_FLAG_HIDDEN);
            grid_indicators[f][i] = ind;
        }
    }
    
    create_nav_bar(screen_grid);
}

static void create_screen_controls(void) {
    screen_controls = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_controls, COLOR_BG, 0);
    
    // Stats panel
    lv_obj_t *stats = lv_obj_create(screen_controls);
    lv_obj_set_size(stats, 460, 200);
    lv_obj_align(stats, LV_ALIGN_TOP_MID, 0, 10);
    lv_obj_clear_flag(stats, LV_OBJ_FLAG_SCROLLABLE);
    
    lv_obj_t *title = lv_label_create(stats);
    lv_label_set_text(title, "ELEVATOR STATISTICS");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 5);
    
    for (int i = 0; i < 6; i++) {
        int x = (i % 2) * 230;
        int y = 40 + (i / 2) * 45;
        
        stat_labels[i] = lv_label_create(stats);
        lv_label_set_text(stat_labels[i], "-");
        lv_obj_set_style_text_font(stat_labels[i], &lv_font_montserrat_14, 0);
        lv_obj_set_pos(stat_labels[i], 10 + x, y);
    }
    
    // Control buttons
    lv_obj_t *btns = lv_obj_create(screen_controls);
    lv_obj_set_size(btns, 460, 100);
    lv_obj_align(btns, LV_ALIGN_TOP_MID, 0, 220);
    lv_obj_clear_flag(btns, LV_OBJ_FLAG_SCROLLABLE);
    
    btn_auto = lv_btn_create(btns);
    lv_obj_set_size(btn_auto, 200, 40);
    lv_obj_set_pos(btn_auto, 10, 10);
    lv_obj_set_style_bg_color(btn_auto, COLOR_UP, 0);
    lv_obj_add_event_cb(btn_auto, auto_mode_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *lbl_auto = lv_label_create(btn_auto);
    lv_label_set_text(lbl_auto, "AUTO MODE");
    lv_obj_center(lbl_auto);
    
    lv_obj_t *btn_rand = lv_btn_create(btns);
    lv_obj_set_size(btn_rand, 200, 40);
    lv_obj_set_pos(btn_rand, 240, 10);
    lv_obj_add_event_cb(btn_rand, random_calls_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *lbl_rand = lv_label_create(btn_rand);
    lv_label_set_text(lbl_rand, "RANDOM CALLS");
    lv_obj_center(lbl_rand);
    
    lv_obj_t *btn_clear = lv_btn_create(btns);
    lv_obj_set_size(btn_clear, 430, 40);
    lv_obj_set_pos(btn_clear, 10, 55);
    lv_obj_set_style_bg_color(btn_clear, COLOR_DOWN, 0);
    lv_obj_add_event_cb(btn_clear, clear_all_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *lbl_clear = lv_label_create(btn_clear);
    lv_label_set_text(lbl_clear, "CLEAR ALL CALLS");
    lv_obj_center(lbl_clear);
    
    // Log panel
    lv_obj_t *log_panel = lv_obj_create(screen_controls);
    lv_obj_set_size(log_panel, 460, 370);
    lv_obj_align(log_panel, LV_ALIGN_TOP_MID, 0, 330);
    
    lv_obj_t *log_title = lv_label_create(log_panel);
    lv_label_set_text(log_title, "PACKET LOG");
    lv_obj_set_style_text_font(log_title, &lv_font_montserrat_16, 0);
    lv_obj_align(log_title, LV_ALIGN_TOP_MID, 0, 5);
    
    log_area = lv_textarea_create(log_panel);
    lv_obj_set_size(log_area, 440, 330);
    lv_obj_align(log_area, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_textarea_set_text(log_area, "");
    
    create_nav_bar(screen_controls);
}

static void switch_screen(uint8_t num) {
    switch(num) {
        case 0: lv_scr_load(screen_shaft); break;
        case 1: lv_scr_load(screen_grid); break;
        case 2: lv_scr_load(screen_controls); break;
    }
}

// =============================================================================
// MAIN INIT
// =============================================================================

void elevator_init(void) {
    // Create all screens
    create_screen_shaft();
    create_screen_grid();
    create_screen_controls();
    
    // Start on shaft screen
    switch_screen(0);
    
    // Initialize timers
    lv_timer_create(elevator_timer_cb, 1000, NULL);
    lv_timer_create(auto_mode_timer_cb, 500, NULL);
    
    // Initialize stats
    update_stats();
    update_elevator_position();
    
    log_msg("SYSTEM: Elevator started - 30 floors");
    log_msg("SYSTEM: LoRa monitoring active");
    
    // Demo calls
    lv_timer_t *demo = lv_timer_create([](lv_timer_t *t) {
        place_call(25, CALL_DOWN);
        place_call(15, CALL_UP);
        place_call(8, CALL_LOAD);
        lv_timer_del(t);
    }, 1000, NULL);
    lv_timer_set_repeat_count(demo, 1);
}
