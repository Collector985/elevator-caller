/**
 * @file lv_conf.h
 * Configuration file for LVGL v8.3.x
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*====================
   COLOR SETTINGS
 *====================*/

/* Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888) */
#define LV_COLOR_DEPTH 16

/* Draw engine tuning */
#define LV_DRAW_COMPLEX 1
#define LV_SHADOW_CACHE_SIZE 0
#define LV_ANTIALIASING 1

/* Swap the 2 bytes of RGB565 color. Useful if the display has an 8-bit interface (e.g. SPI) */
#define LV_COLOR_16_SWAP 1

/*=========================
   MEMORY SETTINGS
 *=========================*/

/* 1: use custom malloc/free, 0: use the built-in `lv_mem_alloc()` and `lv_mem_free()` */
#define LV_MEM_CUSTOM 0

#if LV_MEM_CUSTOM == 0
    /* Size of the memory available for `lv_mem_alloc()` in bytes (>= 2kB) */
    #define LV_MEM_SIZE (128U * 1024U) /* 128KB */

    /* Set an address for the memory pool instead of allocating it as a normal array. */
    #define LV_MEM_ADR 0
#else
    #define LV_MEM_CUSTOM_INCLUDE <stdlib.h>
    #define LV_MEM_CUSTOM_ALLOC   malloc
    #define LV_MEM_CUSTOM_FREE    free
    #define LV_MEM_CUSTOM_REALLOC realloc
#endif

/*====================
   HAL SETTINGS
 *====================*/

/* Default display refresh period. LVG will redraw changed areas with this period */
#define LV_DISP_DEF_REFR_PERIOD 30 /* ms */

/* Input device read period in milliseconds */
#define LV_INDEV_DEF_READ_PERIOD 30 /* ms */

/* Default Dot Per Inch. Used to initialize default sizes such as widgets sized, style paddings */
#define LV_DPI_DEF 130

/*=======================
   FEATURE CONFIGURATION
 *=======================*/

/* 1: Enable animations */
#define LV_USE_ANIMATION 1

/* 1: Enable shadow drawing on rectangles */
#define LV_USE_SHADOW 1

/* 1: Enable outline drawing on rectangles */
#define LV_USE_OUTLINE 1

/* 1: Enable pattern drawing on rectangles */
#define LV_USE_PATTERN 1

/* 1: Enable value string drawing on rectangles */
#define LV_USE_VALUE_STR 1

/* 1: Use other blend modes than normal (`LV_BLEND_MODE_...`) */
#define LV_USE_BLEND_MODES 1

/* 1: Use the `opa_scale` style property to set the opacity of an object and its children at once */
#define LV_USE_OPA_SCALE 1

/* 1: Enable object groups (for keyboards) */
#define LV_USE_GROUP 1

/* 1: Enable GPU interface */
#define LV_USE_GPU 0

/* 1: Enable file system (might be required for images */
#define LV_USE_FILESYSTEM 0

/* 1: Enable indexed (palette) images */
#define LV_USE_IMG_CF_INDEXED 1

/* 1: Enable alpha indexed images */
#define LV_USE_IMG_CF_ALPHA 1

/* Default image cache size. */
#define LV_IMG_CACHE_DEF_SIZE 1

/* Maximum buffer size to allocate for rotation. */
#define LV_DISP_ROT_MAX_BUF (10 * 1024)

/*===================
   LOG SETTINGS
 *===================*/

/* Enable the log module */
#define LV_USE_LOG 1

#if LV_USE_LOG
    /* How important log should be added:
     * LV_LOG_LEVEL_TRACE       A lot of logs to give detailed information
     * LV_LOG_LEVEL_INFO        Log important events
     * LV_LOG_LEVEL_WARN        Log if something unwanted happened but didn't cause a problem
     * LV_LOG_LEVEL_ERROR       Only critical issue, when the system may fail
     * LV_LOG_LEVEL_USER        Only logs added by the user
     * LV_LOG_LEVEL_NONE        Do not log anything */
    #define LV_LOG_LEVEL LV_LOG_LEVEL_INFO

    /* 1: Print the log with 'printf';
     * 0: User need to register a callback with `lv_log_register_print_cb()`*/
    #define LV_LOG_PRINTF 0

    /* Enable/disable LV_LOG_TRACE in modules that produces a huge number of logs */
    #define LV_LOG_TRACE_MEM        0
    #define LV_LOG_TRACE_TIMER      0
    #define LV_LOG_TRACE_INDEV      0
    #define LV_LOG_TRACE_DISP_REFR  0
    #define LV_LOG_TRACE_EVENT      0
    #define LV_LOG_TRACE_OBJ_CREATE 0
    #define LV_LOG_TRACE_LAYOUT     0
    #define LV_LOG_TRACE_ANIM       0
#endif

/*==================
   FONT SETTINGS
 *==================*/

/* Montserrat fonts with ASCII range and some symbols using bpp = 4
 * https://fonts.google.com/specimen/Montserrat */
#define LV_FONT_MONTSERRAT_8  0
#define LV_FONT_MONTSERRAT_10 1
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 1
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 1
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/* Demonstrate special features */
#define LV_FONT_MONTSERRAT_12_SUBPX      0
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0  /*bpp = 3*/
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0  /*Hebrew, Arabic, Persian letters and all their forms*/
#define LV_FONT_SIMSUN_16_CJK            0  /*1000 most common CJK radicals*/

/* Pixel perfect monospace fonts */
#define LV_FONT_UNSCII_8  1
#define LV_FONT_UNSCII_16 0

/* Optionally declare custom fonts here.
 * You can use these fonts as default font too and they will be available globally.
 * E.g. #define LV_FONT_CUSTOM_DECLARE   LV_FONT_DECLARE(my_font_1) LV_FONT_DECLARE(my_font_2) */
#define LV_FONT_CUSTOM_DECLARE

/* Always set a default font */
#define LV_FONT_DEFAULT &lv_font_montserrat_16

/* Enable handling large font and/or fonts with a lot of characters.
 * The limit depends on the font size, font face and bpp.
 * Compiler error will be triggered if a font needs it. */
#define LV_FONT_FMT_TXT_LARGE 0

/* Enables/disables support for compressed fonts. */
#define LV_USE_FONT_COMPRESSED 0

/* Enable subpixel rendering */
#define LV_USE_FONT_SUBPX 0

/*=================
   TEXT SETTINGS
 *=================*/

/**
 * Select a character encoding for strings.
 * Your IDE or editor should have the same character encoding
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/* Can break (wrap) texts on these chars */
#define LV_TXT_BREAK_CHARS " ,.;:-_"

/* If a word is at least this long, will break wherever "prettiest" */
#define LV_TXT_LINE_BREAK_LONG_LEN 0

/* Minimum number of characters in a long word to put on a line before a break */
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3

/* Minimum number of characters in a long word to put on a line after a break */
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/* The control character to use for signalling text recoloring */
#define LV_TXT_COLOR_CMD "#"

/* Support bidirectional texts. Allows mixing Left-to-Right and Right-to-Left texts */
#define LV_USE_BIDI 0

/* Enable Arabic/Persian processing */
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*==================
   WIDGET USAGE
 *==================*/

#define LV_USE_OBJ          1

/*Container-like objects*/
#define LV_USE_CONT         1
#define LV_USE_PAGE         1
#define LV_USE_WIN          1
#define LV_USE_TABVIEW      1
#define LV_USE_TILEVIEW     1

/*Basic objects*/
#define LV_USE_ARC          1
#define LV_USE_BAR          1
#define LV_USE_BTN          1
#define LV_USE_BTNMATRIX    1
#define LV_USE_CALENDAR     1
#define LV_USE_CANVAS       1
#define LV_USE_CHECKBOX     1
#define LV_USE_CHART        1
#define LV_USE_DROPDOWN     1
#define LV_USE_GAUGE        1
#define LV_USE_IMG          1
#define LV_USE_IMGBTN       1
#define LV_USE_KEYBOARD     1
#define LV_USE_LABEL        1
#define LV_USE_LED          1
#define LV_USE_LINE         1
#define LV_USE_LIST         1
#define LV_USE_LINEMETER    1
#define LV_USE_MSGBOX       1
#define LV_USE_OBJMASK      1
#define LV_USE_ROLLER       1
#define LV_USE_SLIDER       1
#define LV_USE_SPINBOX      1
#define LV_USE_SPINNER      1
#define LV_USE_SWITCH       1
#define LV_USE_TEXTAREA     1
#define LV_USE_TABLE        1

/*==================
   USER DATA
 *==================*/

/* 1: Add a `user_data` to drivers and objects */
#define LV_USE_USER_DATA 1

/*==================
   DEBUG
 *==================*/

/* Check if the parameter is NULL. (Very fast, recommended) */
#define LV_USE_ASSERT_NULL 1

/* Checks if the memory is successfully allocated or no. (Very fast, recommended) */
#define LV_USE_ASSERT_MALLOC 1

/* Check if the styles are properly initialized. (Very fast, recommended) */
#define LV_USE_ASSERT_STYLE 0

/* Check the integrity of `lv_mem` after critical operations. (Slow) */
#define LV_USE_ASSERT_MEM_INTEGRITY 0

/* Check the objects (e.g. not deleted) in the input device drivers (Slow) */
#define LV_USE_ASSERT_OBJ 0

#define LV_USE_PERF_MONITOR 0
#define LV_USE_MEM_MONITOR 0

#endif /*LV_CONF_H*/
