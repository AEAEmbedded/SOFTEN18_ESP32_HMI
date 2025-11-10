/**
 * \file            display_driver.h
 * \brief           Display driver prototypes
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

#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include "esp_lvgl_port.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Initialize the RGB LCD panel.
     *
     * This function configures and initializes the ESP-IDF RGB LCD panel driver
     * using board-specific timing and GPIO settings. It allocates and sets up the
     * panel handle, then performs the low-level panel initialization sequence.
     *
     * On failure, the function attempts to clean up by deleting any allocated panel
     * handle before returning the corresponding error code.
     *
     * @param[out] lp Pointer to a panel handle that will be populated on success.
     *
     * @return
     *      - ESP_OK on success
     *      - ESP_ERR_xxx if initialization or panel creation fails
     */
    esp_err_t display_driver_lcd_init(esp_lcd_panel_handle_t *lp);

    /**
     * @brief Initialize LVGL and register the LCD panel and touch driver.
     *
     * This function sets up the LVGL port, creates display buffers, registers the
     * RGB display driver, and attaches the touch input driver. It outputs the LVGL
     * display and input device handles for later use in the application.
     *
     * The configuration used for LVGL scheduling, buffering, color format, and
     * panel behavior is based on compile-time board settings.
     *
     * @param[in]  lp              LCD panel handle created by `display_driver_lcd_init()`.
     * @param[in]  tp              Touch driver handle to attach as LVGL input.
     * @param[out] lv_disp         Pointer to a variable that will receive the LVGL display handle.
     * @param[out] lv_touch_indev  Pointer to a variable that will receive the LVGL touch input device handle.
     *
     * @return
     *      - ESP_OK on success
     *      - ESP_ERR_xxx if LVGL port initialization or display/touch registration fails
     */
    esp_err_t display_driver_lvgl_init(esp_lcd_panel_handle_t lp,
                                       esp_lcd_touch_handle_t tp,
                                       lv_display_t **lv_disp,
                                       lv_indev_t **lv_touch_indev);
#ifdef __cplusplus
}
#endif
#endif /* DISPLAY_DRIVER_H */