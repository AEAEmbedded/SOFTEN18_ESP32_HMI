/**
 * \file            touch_driver.c
 * \brief           Touch screen driver implementation
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

#include "touch_driver.h"
#include <config/board_config.h>
#include "esp_lcd_touch_gt911.h"

static const char TAG[] = "touch_driver";

esp_err_t touch_driver_init(i2c_master_bus_handle_t *bus,
                            esp_lcd_panel_io_handle_t *tp_io,
                            esp_lcd_touch_handle_t *tp)
{
    if (!*bus)
    {
        ESP_LOGI(TAG, "creating i2c master bus");
        const i2c_master_bus_config_t i2c_conf = {
            .i2c_port = -1,
            .sda_io_num = BSP_TOUCH_GPIO_SDA,
            .scl_io_num = BSP_TOUCH_GPIO_SCL,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
            .flags.enable_internal_pullup = 1,
        };
        ESP_RETURN_ON_ERROR(i2c_new_master_bus(&i2c_conf, bus),
                            TAG, "failed to create i2c master bus");
    }

    if (!*tp_io)
    {
        ESP_LOGI(TAG, "creating touch panel io");
        esp_lcd_panel_io_i2c_config_t tp_io_cfg =
            ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
        tp_io_cfg.scl_speed_hz = 400000;
        ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_i2c_v2(*bus, &tp_io_cfg, tp_io),
                            TAG, "Failed to crate touch panel io");
    }

    const esp_lcd_touch_config_t tp_cfg = {
        .x_max = BSP_LCD_H_RES,
        .y_max = BSP_LCD_V_RES,
        .rst_gpio_num = BSP_TOUCH_GPIO_RST,
        .int_gpio_num = BSP_TOUCH_GPIO_INT,
    };

    return esp_lcd_touch_new_i2c_gt911(*tp_io, &tp_cfg, tp);
}