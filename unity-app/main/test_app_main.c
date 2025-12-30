/*
 * SPDX-FileCopyrightText: 2015-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "unity.h"
#include <touch_driver.h>
#include <display_driver.h>
#include <ui.h>

static esp_lcd_panel_handle_t lcd_panel = NULL;

static i2c_master_bus_handle_t my_bus = NULL;
static esp_lcd_panel_io_handle_t touch_io_handle = NULL;
static esp_lcd_touch_handle_t touch_handle = NULL;

/* LVGL display and touch */
static lv_display_t *lvgl_disp = NULL;
static lv_indev_t *lvgl_touch_indev = NULL;

void app_main(void)
{
    ESP_ERROR_CHECK(display_driver_lcd_init(&lcd_panel));
    ESP_ERROR_CHECK(touch_driver_init(&my_bus, &touch_io_handle, &touch_handle));
    ESP_ERROR_CHECK(display_driver_lvgl_init(lcd_panel, touch_handle, &lvgl_disp, &lvgl_touch_indev));

    lvgl_port_lock(0);
    ui_init();
    lvgl_port_unlock();
    unity_run_menu();
}