/**
 * \file            ui_events_selection_page.hpp
 * \brief           Hooks from LVGL selection-page events to the fsm_logic_selection_page module
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
extern "C"
{
#include <lvgl.h>
#include <screens.h>
}
#include <stdio.h>
#include <fsm_logic_selection_page.hpp>
/* -------------------------------------------------------------------------- */
/*  LVGL callbacks                                                             */
/* -------------------------------------------------------------------------- */
static SelectionController selection_ctrl;
static lv_timer_t *selection_status_timer = nullptr;

extern "C" void update_selection_status(lv_timer_t *)
{
    if (lv_scr_act() != objects.cappucino_chooser_page)
        return;
    ui_events::unit_event_msg_t msg{};
    selection_ctrl.run_selection(msg);
}

static void adjust_slider(lv_obj_t *slider, int delta)
{
    int32_t value = lv_slider_get_value(slider);
    int32_t min = lv_slider_get_min_value(slider);
    int32_t max = lv_slider_get_max_value(slider);

    int32_t new_value = value + delta;

    if (new_value < min || new_value > max)
        return;

    printf("Current value: %ld\n", value);
    lv_slider_set_value(slider, new_value, LV_ANIM_OFF);
    printf("New value: %ld\n", new_value);
}

extern "C"
{

    void action_increase_strength(lv_event_t *)
    {
        adjust_slider(objects.coffee_strength_slider, +1);
    }

    void action_decrease_coffee_strength(lv_event_t *)
    {
        adjust_slider(objects.coffee_strength_slider, -1);
    }

    void action_increase_coffee_sugar_content(lv_event_t *)
    {
        adjust_slider(objects.sugar_content_slider, +1);
    }

    void action_decrease_coffee_sugar_content(lv_event_t *)
    {
        adjust_slider(objects.sugar_content_slider, -1);
    }

    void action_increase_coffee_milk_content(lv_event_t *)
    {
        adjust_slider(objects.milk_content_slider, +1);
    }

    void action_decrease_coffee_milk_content(lv_event_t *)
    {
        adjust_slider(objects.milk_content_slider, -1);
    }

    void action_coffee_start_event(lv_event_t *)
    {
        ui_events::unit_state_msg_t state{};
        state.evt_id = ui_events::SELECTION_STAGE_SELECTION_VERIFY;
        xQueueSend(unit_state_queue, &state, 0);
    }

    void action_cappuccino_page_loaded(lv_event_t *e)
    {
        printf("selection_page_loaded\n");

        if (!selection_status_timer)
        {
            selection_status_timer =
                lv_timer_create(update_selection_status, 300, nullptr);
        }
    }

    void action_cappuccino_page_unloaded(lv_event_t *e)
    {
        printf("selection_page_unloaded\n");

        if (selection_status_timer)
        {
            lv_timer_delete(selection_status_timer);
            selection_status_timer = nullptr;
        }
    }

} // extern "C"
