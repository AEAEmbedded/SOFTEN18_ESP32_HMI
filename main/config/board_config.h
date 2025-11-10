/**
 * \file            board_config.h
 * \brief           Board-specific macro's/settings
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

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H
#include "driver/gpio.h"
#include "esp_check.h"
#ifdef __cplusplus
extern "C"
{
#endif

#define BSP_LCD_BK_LIGHT_ON_LEVEL 1
#define BSP_LCD_BK_LIGHT_OFF_LEVEL (!BSP_LCD_BK_LIGHT_ON_LEVEL)
#define BSP_LCD_GPIO_BK_LIGHT GPIO_NUM_2
#define BSP_LCD_GPIO_HSYNC GPIO_NUM_39
#define BSP_LCD_GPIO_VSYNC GPIO_NUM_40
#define BSP_LCD_GPIO_DE GPIO_NUM_41
#define BSP_LCD_GPIO_PCLK GPIO_NUM_42
#define BSP_LCD_GPIO_DATA() { \
    GPIO_NUM_15,              \
    GPIO_NUM_7,               \
    GPIO_NUM_6,               \
    GPIO_NUM_5,               \
    GPIO_NUM_4,               \
    GPIO_NUM_9,               \
    GPIO_NUM_46,              \
    GPIO_NUM_3,               \
    GPIO_NUM_8,               \
    GPIO_NUM_16,              \
    GPIO_NUM_1,               \
    GPIO_NUM_14,              \
    GPIO_NUM_21,              \
    GPIO_NUM_47,              \
    GPIO_NUM_48,              \
    GPIO_NUM_45,              \
}
#define BSP_LCD_GPIO_DISP GPIO_NUM_NC

// The pixel number in horizontal and vertical
#define BSP_LCD_H_RES 800
#define BSP_LCD_V_RES 480

#define BSP_TOUCH_GPIO_SCL GPIO_NUM_20
#define BSP_TOUCH_GPIO_SDA GPIO_NUM_19
#define BSP_TOUCH_GPIO_INT GPIO_NUM_NC
#define BSP_TOUCH_GPIO_RST GPIO_NUM_38

#ifdef __cplusplus
}
#endif

#endif /* BOARD_CONFIG_H */