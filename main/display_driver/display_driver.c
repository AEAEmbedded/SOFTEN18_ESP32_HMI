/**
 * \file            display_driver.c
 * \brief           Display screen driver implementation
 */
/*
 *  Copyright 2025 (C) Victor Hogeweij <victor.hogeweij@han.nl>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * This file is part of the SOFTEN18_ESP32_HMI code
 *
 * Author:          Victor Hogeweij <victor.hogeweij@han.nl>
 */

#include "display_driver.h"
#include <config/board_config.h>
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_touch_gt911.h"

/* LCD settings */
#define BSP_LCD_PANEL_TIMING()         \
    (esp_lcd_rgb_timing_t)             \
    {                                  \
        .pclk_hz = 16000000,           \
        .h_res = BSP_LCD_H_RES,        \
        .v_res = BSP_LCD_V_RES,        \
        .hsync_pulse_width = 30,       \
        .hsync_back_porch = 16,        \
        .hsync_front_porch = 20,       \
        .vsync_pulse_width = 13,       \
        .vsync_back_porch = 10,        \
        .vsync_front_porch = 22,       \
        .flags.pclk_active_neg = true, \
    }

#define APP_LCD_LVGL_FULL_REFRESH (0)
#define APP_LCD_LVGL_DIRECT_MODE (1)
#define APP_LCD_LVGL_AVOID_TEAR (1)
#define APP_LCD_RGB_BOUNCE_BUFFER_MODE (1)
#define APP_LCD_DRAW_BUFF_DOUBLE (0)
#define APP_LCD_DRAW_BUFF_HEIGHT (100)
#define APP_LCD_RGB_BUFFER_NUMS (2)
#define APP_LCD_RGB_BOUNCE_BUFFER_HEIGHT (10)
static const char TAG[] = "display_driver";

esp_err_t display_driver_lcd_init(esp_lcd_panel_handle_t *lp)
{
    esp_err_t ret = ESP_OK;

    ESP_LOGI(TAG, "Initialize RGB panel");
    const esp_lcd_rgb_panel_config_t conf = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .timings = BSP_LCD_PANEL_TIMING(),
        .data_width = 16,
        .num_fbs = APP_LCD_RGB_BUFFER_NUMS,
#ifdef APP_LCD_RGB_BOUNCE_BUFFER_MODE
        .bounce_buffer_size_px = BSP_LCD_H_RES * APP_LCD_RGB_BOUNCE_BUFFER_HEIGHT,
#endif
        .hsync_gpio_num = BSP_LCD_GPIO_HSYNC,
        .vsync_gpio_num = BSP_LCD_GPIO_VSYNC,
        .de_gpio_num = BSP_LCD_GPIO_DE,
        .pclk_gpio_num = BSP_LCD_GPIO_PCLK,
        .disp_gpio_num = BSP_LCD_GPIO_DISP,
        .data_gpio_nums = BSP_LCD_GPIO_DATA(),
        .flags.fb_in_psram = 1,
    };
    ESP_GOTO_ON_ERROR(esp_lcd_new_rgb_panel(&conf, lp),
                      err, TAG, "RGB init failed");
    ESP_GOTO_ON_ERROR(esp_lcd_panel_init(*lp),
                      err, TAG, "LCD init failed");
    const gpio_config_t bk_light = {
        .pin_bit_mask = (1 << BSP_LCD_GPIO_BK_LIGHT),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&bk_light));
    gpio_set_level(BSP_LCD_GPIO_BK_LIGHT, BSP_LCD_BK_LIGHT_ON_LEVEL);
    return ret;

err:
    if (*lp)
    {
        esp_lcd_panel_del(*lp);
    }
    return ret;
}

esp_err_t display_driver_lvgl_init(esp_lcd_panel_handle_t lp, esp_lcd_touch_handle_t tp,
                                   lv_display_t **lv_disp, lv_indev_t **lv_touch_indev)
{
    /* Initialize LVGL */
    const lvgl_port_cfg_t lvgl_cfg = {
        .task_priority = 4,       /* LVGL task priority */
        .task_stack = 8192,       /* LVGL task stack size */
        .task_affinity = -1,      /* LVGL task pinned to core (-1 is no affinity) */
        .task_max_sleep_ms = 500, /* Maximum sleep in LVGL task */
        .timer_period_ms = 5      /* LVGL timer tick period in ms */
    };
    ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_cfg), TAG, "LVGL port initialization failed");

    uint32_t buff_size = BSP_LCD_H_RES * APP_LCD_DRAW_BUFF_HEIGHT;
#if APP_LCD_LVGL_FULL_REFRESH || APP_LCD_LVGL_DIRECT_MODE
    buff_size = BSP_LCD_H_RES * BSP_LCD_V_RES;
#endif

    /* Add LCD screen */
    ESP_LOGD(TAG, "Add LCD screen");
    const lvgl_port_display_cfg_t disp_cfg = {
        .panel_handle = lp,
        .buffer_size = buff_size,
        .double_buffer = APP_LCD_DRAW_BUFF_DOUBLE,
        .hres = BSP_LCD_H_RES,
        .vres = BSP_LCD_V_RES,
        .monochrome = false,
#if LVGL_VERSION_MAJOR >= 9
        .color_format = LV_COLOR_FORMAT_RGB565,
#endif
        .rotation = {
            .swap_xy = false,
            .mirror_x = false,
            .mirror_y = false,
        },
        .flags = {
            .buff_dma = false,
            .buff_spiram = false,
#if APP_LCD_LVGL_FULL_REFRESH
            .full_refresh = true,
#elif APP_LCD_LVGL_DIRECT_MODE
            .direct_mode = true,
#endif
#if LVGL_VERSION_MAJOR >= 9
            .swap_bytes = false,
#endif
        }};
    const lvgl_port_display_rgb_cfg_t rgb_cfg = {
        .flags = {
#if APP_LCD_RGB_BOUNCE_BUFFER_MODE
            .bb_mode = true,
#else
            .bb_mode = false,
#endif
#if APP_LCD_LVGL_AVOID_TEAR
            .avoid_tearing = true,
#else
            .avoid_tearing = false,
#endif
        }};
    *lv_disp = lvgl_port_add_disp_rgb(&disp_cfg, &rgb_cfg);
    if (tp != NULL)
    {
        /* Add touch input (for selected screen) */
        const lvgl_port_touch_cfg_t touch_cfg = {
            .disp = *lv_disp,
            .handle = tp,
        };
        *lv_touch_indev = lvgl_port_add_touch(&touch_cfg);
    }
    return ESP_OK;
}
