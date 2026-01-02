/**
 * \file            ui_events_prepare_page.hpp
 * \brief           Hooks from LVGL prepare-page events to the fsm_logic_prepare_page module
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
#include "fsm_logic.hpp"
#include "fsm_logic_brew_page.hpp"

extern "C"
{
#include <lvgl.h>
#include <screens.h>
}

#include <stdio.h>

static BrewController brew_ctrl;
static lv_timer_t *prepare_status_timer = nullptr;

extern "C" void update_brew_progress(lv_timer_t *)
{
    char progress_str[8]; // "100 %" + '\0' fits

    uint8_t progress = brew_ctrl.run_brew();

    lv_bar_set_value(
        objects.coffee_prepare_progress_bar,
        progress,
        LV_ANIM_OFF);

    lv_snprintf(progress_str, sizeof(progress_str), "%u %%", progress);
    lv_label_set_text(objects.progress_percentage_lbl, progress_str);
}

extern "C" void action_prepare_page_loaded(lv_event_t *)
{
    printf("prepare_page_loaded\n");

    if (!prepare_status_timer)
    {
        prepare_status_timer =
            lv_timer_create(update_brew_progress, 500, nullptr);
    }
}

extern "C" void action_prepare_page_unloaded(lv_event_t *)
{
    printf("prepare_page_unloaded\n");
    brew_ctrl.reset_status();
    if (prepare_status_timer)
    {
        lv_timer_delete(prepare_status_timer);
        prepare_status_timer = nullptr;
    }
}
