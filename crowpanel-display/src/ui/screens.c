#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 800);
    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // shaft_column_1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.shaft_column_1 = obj;
            lv_obj_set_pos(obj, -1, 0);
            lv_obj_set_size(obj, LV_PCT(32), 740);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_grid_row_align(obj, LV_GRID_ALIGN_STRETCH, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_grid_column_align(obj, LV_GRID_ALIGN_STRETCH, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_grow(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f2933), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // floor_
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor_ = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj0 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj1 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_1
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_1 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj2 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__1
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__1 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj3 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj4 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_2
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_2 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj5 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__2
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__2 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj6 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj7 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_3
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_3 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj8 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__3
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__3 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj9 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj10 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_4
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_4 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj11 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__4
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__4 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj12 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj13 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_5
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_5 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj14 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__5
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__5 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj15 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj16 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_6
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_6 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj17 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__6
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__6 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj18 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj19 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_7
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_7 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj20 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__7
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__7 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj21 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj22 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_8
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_8 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj23 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__8
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__8 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj24 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj25 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_9
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_9 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj26 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__9
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__9 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj27 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj28 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_10
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_10 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj29 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__10
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__10 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj30 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj31 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_11
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_11 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj32 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__11
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__11 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj33 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj34 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_12
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_12 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj35 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__12
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__12 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj36 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj37 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_13
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_13 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj38 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__13
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__13 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj39 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj40 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_14
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_14 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj41 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__14
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__14 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj42 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj43 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_15
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_15 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj44 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__15
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__15 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj45 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj46 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_16
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_16 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj47 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__16
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__16 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj48 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj49 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_17
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_17 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj50 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__17
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__17 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj51 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj52 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_18
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_18 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj53 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__18
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__18 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj54 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj55 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_19
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_19 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj56 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__19
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__19 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj57 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj58 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_20
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_20 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj59 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
            }
        }
        {
            // shaft_column_2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.shaft_column_2 = obj;
            lv_obj_set_pos(obj, 166, 2);
            lv_obj_set_size(obj, LV_PCT(32), 740);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_grow(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_grid_column_align(obj, LV_GRID_ALIGN_STRETCH, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f2933), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // floor__20
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__20 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj60 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj61 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_21
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_21 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj62 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__21
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__21 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj63 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj64 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_22
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_22 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj65 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__22
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__22 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj66 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj67 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_23
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_23 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj68 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__23
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__23 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj69 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj70 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_24
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_24 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj71 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__24
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__24 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj72 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj73 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_25
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_25 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj74 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__25
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__25 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj75 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj76 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_26
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_26 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj77 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__26
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__26 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj78 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj79 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_27
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_27 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj80 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__27
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__27 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj81 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj82 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_28
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_28 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj83 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__28
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__28 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj84 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj85 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_29
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_29 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj86 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__29
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__29 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj87 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj88 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_30
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_30 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj89 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__30
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__30 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj90 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj91 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_31
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_31 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj92 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__31
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__31 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj93 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj94 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_32
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_32 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj95 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__32
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__32 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj96 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj97 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_33
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_33 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj98 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__33
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__33 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj99 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj100 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_34
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_34 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj101 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__34
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__34 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj102 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj103 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_35
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_35 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj104 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__35
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__35 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj105 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj106 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_36
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_36 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj107 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__36
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__36 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj108 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj109 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_37
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_37 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj110 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__37
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__37 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj111 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj112 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_38
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_38 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj113 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__38
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__38 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj114 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj115 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_39
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_39 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj116 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__39
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__39 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj117 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj118 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_40
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_40 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj119 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
            }
        }
        {
            // shaft_column_3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.shaft_column_3 = obj;
            lv_obj_set_pos(obj, 331, 2);
            lv_obj_set_size(obj, LV_PCT(32), 740);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_COLUMN, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_main_place(obj, LV_FLEX_ALIGN_START, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_row(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_flex_grow(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_grid_column_align(obj, LV_GRID_ALIGN_STRETCH, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1f2933), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_letter_space(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // floor__40
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__40 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj120 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj121 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_41
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_41 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj122 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__41
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__41 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj123 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj124 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_42
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_42 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj125 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__42
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__42 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj126 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj127 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_43
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_43 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj128 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__43
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__43 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj129 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj130 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_44
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_44 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj131 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__44
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__44 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj132 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj133 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_45
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_45 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj134 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__45
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__45 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj135 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj136 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_46
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_46 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj137 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__46
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__46 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj138 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj139 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_47
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_47 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj140 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__47
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__47 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj141 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj142 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_48
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_48 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj143 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__48
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__48 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj144 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj145 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_49
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_49 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj146 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__49
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__49 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj147 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj148 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_50
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_50 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj149 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__50
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__50 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj150 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj151 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_51
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_51 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj152 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__51
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__51 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj153 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj154 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_52
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_52 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj155 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__52
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__52 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj156 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj157 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_53
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_53 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj158 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__53
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__53 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj159 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj160 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_54
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_54 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj161 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__54
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__54 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj162 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj163 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_55
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_55 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj164 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__55
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__55 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj165 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj166 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_56
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_56 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj167 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__56
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__56 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj168 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj169 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_57
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_57 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj170 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__57
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__57 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj171 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj172 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_58
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_58 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj173 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__58
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__58 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj174 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj175 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_59
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_59 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj176 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
                {
                    // floor__59
                    lv_obj_t *obj = lv_obj_create(parent_obj);
                    objects.floor__59 = obj;
                    lv_obj_set_pos(obj, 1, 742);
                    lv_obj_set_size(obj, LV_PCT(100), 34);
                    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                    lv_obj_set_style_flex_flow(obj, LV_FLEX_FLOW_ROW, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_layout(obj, LV_LAYOUT_FLEX, LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj177 = obj;
                            lv_obj_set_pos(obj, 348, -1);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2ecc71), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj178 = obj;
                            lv_obj_set_pos(obj, 153, -120);
                            lv_obj_set_size(obj, 40, LV_PCT(100));
                            lv_obj_set_style_flex_grow(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfffafbfd), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff3498db), LV_PART_MAIN | LV_STATE_CHECKED);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_CHECKED);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // Floor Number_60
                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                    objects.floor_number_60 = obj;
                                    lv_obj_set_pos(obj, 65, 0);
                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                    lv_label_set_text(obj, "");
                                }
                            }
                        }
                        {
                            lv_obj_t *obj = lv_btn_create(parent_obj);
                            objects.obj179 = obj;
                            lv_obj_set_pos(obj, -144, 7);
                            lv_obj_set_size(obj, LV_PCT(15), LV_PCT(100));
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffe74c3c), LV_PART_MAIN | LV_STATE_CHECKED);
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 480, 800);
    
    tick_screen_settings();
}

void tick_screen_settings() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
}


static const char *screen_names[] = { "Main", "settings" };
static const char *object_names[] = { "main", "settings", "shaft_column_1", "floor_", "obj0", "obj1", "floor_number_1", "obj2", "floor__1", "obj3", "obj4", "floor_number_2", "obj5", "floor__2", "obj6", "obj7", "floor_number_3", "obj8", "floor__3", "obj9", "obj10", "floor_number_4", "obj11", "floor__4", "obj12", "obj13", "floor_number_5", "obj14", "floor__5", "obj15", "obj16", "floor_number_6", "obj17", "floor__6", "obj18", "obj19", "floor_number_7", "obj20", "floor__7", "obj21", "obj22", "floor_number_8", "obj23", "floor__8", "obj24", "obj25", "floor_number_9", "obj26", "floor__9", "obj27", "obj28", "floor_number_10", "obj29", "floor__10", "obj30", "obj31", "floor_number_11", "obj32", "floor__11", "obj33", "obj34", "floor_number_12", "obj35", "floor__12", "obj36", "obj37", "floor_number_13", "obj38", "floor__13", "obj39", "obj40", "floor_number_14", "obj41", "floor__14", "obj42", "obj43", "floor_number_15", "obj44", "floor__15", "obj45", "obj46", "floor_number_16", "obj47", "floor__16", "obj48", "obj49", "floor_number_17", "obj50", "floor__17", "obj51", "obj52", "floor_number_18", "obj53", "floor__18", "obj54", "obj55", "floor_number_19", "obj56", "floor__19", "obj57", "obj58", "floor_number_20", "obj59", "shaft_column_2", "floor__20", "obj60", "obj61", "floor_number_21", "obj62", "floor__21", "obj63", "obj64", "floor_number_22", "obj65", "floor__22", "obj66", "obj67", "floor_number_23", "obj68", "floor__23", "obj69", "obj70", "floor_number_24", "obj71", "floor__24", "obj72", "obj73", "floor_number_25", "obj74", "floor__25", "obj75", "obj76", "floor_number_26", "obj77", "floor__26", "obj78", "obj79", "floor_number_27", "obj80", "floor__27", "obj81", "obj82", "floor_number_28", "obj83", "floor__28", "obj84", "obj85", "floor_number_29", "obj86", "floor__29", "obj87", "obj88", "floor_number_30", "obj89", "floor__30", "obj90", "obj91", "floor_number_31", "obj92", "floor__31", "obj93", "obj94", "floor_number_32", "obj95", "floor__32", "obj96", "obj97", "floor_number_33", "obj98", "floor__33", "obj99", "obj100", "floor_number_34", "obj101", "floor__34", "obj102", "obj103", "floor_number_35", "obj104", "floor__35", "obj105", "obj106", "floor_number_36", "obj107", "floor__36", "obj108", "obj109", "floor_number_37", "obj110", "floor__37", "obj111", "obj112", "floor_number_38", "obj113", "floor__38", "obj114", "obj115", "floor_number_39", "obj116", "floor__39", "obj117", "obj118", "floor_number_40", "obj119", "shaft_column_3", "floor__40", "obj120", "obj121", "floor_number_41", "obj122", "floor__41", "obj123", "obj124", "floor_number_42", "obj125", "floor__42", "obj126", "obj127", "floor_number_43", "obj128", "floor__43", "obj129", "obj130", "floor_number_44", "obj131", "floor__44", "obj132", "obj133", "floor_number_45", "obj134", "floor__45", "obj135", "obj136", "floor_number_46", "obj137", "floor__46", "obj138", "obj139", "floor_number_47", "obj140", "floor__47", "obj141", "obj142", "floor_number_48", "obj143", "floor__48", "obj144", "obj145", "floor_number_49", "obj146", "floor__49", "obj147", "obj148", "floor_number_50", "obj149", "floor__50", "obj150", "obj151", "floor_number_51", "obj152", "floor__51", "obj153", "obj154", "floor_number_52", "obj155", "floor__52", "obj156", "obj157", "floor_number_53", "obj158", "floor__53", "obj159", "obj160", "floor_number_54", "obj161", "floor__54", "obj162", "obj163", "floor_number_55", "obj164", "floor__55", "obj165", "obj166", "floor_number_56", "obj167", "floor__56", "obj168", "obj169", "floor_number_57", "obj170", "floor__57", "obj171", "obj172", "floor_number_58", "obj173", "floor__58", "obj174", "obj175", "floor_number_59", "obj176", "floor__59", "obj177", "obj178", "floor_number_60", "obj179" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_settings,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_settings();
}
