/**
 * \file            ui_events_pay_page.cpp
 * \brief           Hooks from LVGL pay-page events to the fsm_logic_pay_page module
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
#include "fsm_logic_pay_page.hpp"

/* -------------------------------------------------------------------------- */
/*  Globals                                                                    */
/* -------------------------------------------------------------------------- */

static PayController ctrl;
static lv_timer_t *pay_status_timer = nullptr;

/* -------------------------------------------------------------------------- */
/*  LVGL callbacks                                                             */
/* -------------------------------------------------------------------------- */

extern "C" void update_pay_status(lv_timer_t *)
{
    ui_events::unit_event_msg_t msg{};
    const char *new_text = ctrl.run_payment(msg);
    const char *current = lv_label_get_text(objects.pin_status_lbl);

    if (lv_strcmp(current, new_text) != 0)
    {
        lv_label_set_text(objects.pin_status_lbl, new_text);
    }
}

extern "C" void action_pay_page_loaded(lv_event_t *)
{
    printf("pay_page_loaded\n");

    if (!pay_status_timer)
    {
        pay_status_timer = lv_timer_create(update_pay_status, 500, nullptr);
    }
}

extern "C" void action_pay_page_unloaded(lv_event_t *)
{
    printf("pay_page_unloaded\n");

    ctrl.reset_status();

    if (pay_status_timer)
    {
        lv_timer_delete(pay_status_timer);
        pay_status_timer = nullptr;
    }
}

extern "C" void action_menu_back_button(lv_event_t *)
{
    printf("going back one page\n");

    lv_scr_load_anim(
        objects.cappucino_chooser_page,
        LV_SCR_LOAD_ANIM_MOVE_LEFT,
        300,
        0,
        false);
}
