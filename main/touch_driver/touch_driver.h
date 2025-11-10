/**
 * \file            touch_driver.h
 * \brief           Touch screen driver prototypes
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

#ifndef TOUCH_DRIVER_H
#define TOUCH_DRIVER_H
#include <esp_lvgl_port.h>
#include "driver/i2c_master.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Initialize the GT911 touch controller over I2C and create the LVGL touch handle.
     *
     * This function ensures the I2C master bus, touch panel I/O interface, and
     * GT911 touch controller are properly created and initialized. If the provided
     * bus or panel I/O handles are NULL, the function will allocate and configure
     * them automatically using board-specific GPIO settings.
     *
     * The resulting `esp_lcd_touch_handle_t` can be registered with LVGL through
     * `lvgl_port_add_touch()`.
     *
     * @param[in,out] bus
     *      Pointer to an I2C master bus handle. If `*bus` is NULL, a new bus will be
     *      created and assigned here.
     *
     * @param[in,out] tp_io
     *      Pointer to a touch panel I/O handle. If `*tp_io` is NULL, a new I2C panel
     *      I/O interface for the GT911 will be created and assigned here.
     *
     * @param[out] tp
     *      Pointer to the resulting GT911 touch controller handle. On success,
     *      this will contain a valid `esp_lcd_touch_handle_t`.
     *
     * @return
     *      - ESP_OK on success
     *      - ESP_ERR_INVALID_ARG if parameters are invalid
     *      - esp_err_t codes from lower-level I2C, panel I/O, or touch driver failures
     *
     * @note This function configures the GT911 using board-defined resolution
     *       and GPIO constants from `board_config.h`.
     */
    esp_err_t touch_driver_init(i2c_master_bus_handle_t *bus,
                                esp_lcd_panel_io_handle_t *tp_io,
                                esp_lcd_touch_handle_t *tp);

#ifdef __cplusplus
}
#endif
#endif /* TOUCH_DRIVER_H */