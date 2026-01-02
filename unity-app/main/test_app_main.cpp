/**
 * \file            test_app_main.cpp
 * \brief           Scenario-based DUT test main, with menu-selection that helps you select the right tests
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
#include "unity.h"
#include <touch_driver.h>
#include <display_driver.h>
#include <ui_main.hpp>

static esp_lcd_panel_handle_t lcd_panel = NULL;

static i2c_master_bus_handle_t my_bus = NULL;
static esp_lcd_panel_io_handle_t touch_io_handle = NULL;
static esp_lcd_touch_handle_t touch_handle = NULL;

/* LVGL display and touch */
static lv_display_t *lvgl_disp = NULL;
static lv_indev_t *lvgl_touch_indev = NULL;

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(display_driver_lcd_init(&lcd_panel));
    ESP_ERROR_CHECK(touch_driver_init(&my_bus, &touch_io_handle, &touch_handle));
    ESP_ERROR_CHECK(display_driver_lvgl_init(lcd_panel, touch_handle, &lvgl_disp, &lvgl_touch_indev));

    lvgl_port_lock(0);
    ui_main_init();
    lvgl_port_unlock();
    unity_run_menu();
}