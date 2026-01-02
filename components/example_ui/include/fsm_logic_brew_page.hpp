/**
 * \file            fsm_logic_brew_page.hpp
 * \brief           Header-only FSM module for the brew page (third and last page shown)
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
#ifndef FSM_LOGIC_BREWCONTROLLER_HPP
#define FSM_LOGIC_BREWCONTROLLER_HPP

#include "fsm_logic.hpp"
#include <lvgl.h>
#include <screens.h>

class BrewController
{
public:
    BrewController() = default;

    /**
     * Run one brew FSM tick.
     * @return progress percentage (0–100)
     */
    uint8_t run_brew()
    {
        // If error popup active, just keep updating it
        if (error_mbox)
            return current_progress();

        // Send stage info once
        if (!stage_sent)
        {
            send_stage_information(_curr_stage);
            stage_sent = true;
        }

        // Consume events
        ui_events::unit_event_msg_t evt{};
        if (xQueueReceive(unit_event_queue, &evt, 0) == pdPASS)
        {
            if (evt.evt_id == ui_events::E_OK)
            {
                advance_stage();
            }
            else if (is_brew_error(evt.evt_id))
            {
                show_error(unit_event_msgs[evt.evt_id]);
            }
        }

        return current_progress();
    }

    void reset_status()
    {
        _curr_stage = ui_events::BREW_STAGE_INIT;
        stage_sent = false;

        close_error_dialog(false);
    }

private:
    void advance_stage()
    {
        stage_sent = false;

        if (_curr_stage < ui_events::BREW_STAGE_STOP)
        {
            _curr_stage =
                static_cast<ui_events::brew_unit_stages>(_curr_stage + 1);
            return;
        }

        // STOP reached → notify + navigate
        ui_events::unit_state_msg_t state{};
        state.evt_id = ui_events::BREW_STAGE_STOP;
        xQueueSend(unit_state_queue, &state, 0);

        lv_scr_load_anim(
            objects.cappucino_chooser_page,
            LV_SCR_LOAD_ANIM_MOVE_LEFT,
            300,
            200,
            false);
    }

    void show_error(const char *text)
    {
        if (!text || text[0] == '\0' || error_mbox)
            return;

        countdown = 5;

        error_mbox = lv_msgbox_create(nullptr);
        lv_msgbox_add_title(error_mbox, "Brewing error");
        lv_msgbox_add_text(error_mbox, text);

        ok_btn = lv_msgbox_add_footer_button(error_mbox, "OK (5)");
        lv_obj_add_event_cb(ok_btn, ok_btn_cb, LV_EVENT_CLICKED, this);

        error_timer = lv_timer_create(error_timer_cb, 1000, this);
    }

    void handle_error_countdown()
    {
        if (!error_mbox || !ok_btn)
            return;

        if (--countdown <= 0)
        {
            close_error_dialog(true);
            return;
        }

        char buf[16];
        lv_snprintf(buf, sizeof(buf), "OK (%d)", countdown);
        lv_label_set_text(lv_obj_get_child(ok_btn, 0), buf);
    }

    void close_error_dialog(bool stop_brew)
    {
        if (error_timer)
        {
            lv_timer_del(error_timer);
            error_timer = nullptr;
        }

        if (error_mbox)
        {
            lv_msgbox_close(error_mbox);
            lv_obj_del(error_mbox);
            error_mbox = nullptr;
            ok_btn = nullptr;
        }

        if (stop_brew)
        {
            _curr_stage = ui_events::BREW_STAGE_STOP;
            stage_sent = false;

            ui_events::unit_state_msg_t state{};
            state.evt_id = ui_events::BREW_STAGE_STOP;
            xQueueSend(unit_state_queue, &state, 0);

            lv_scr_load_anim(
                objects.cappucino_chooser_page,
                LV_SCR_LOAD_ANIM_MOVE_LEFT,
                300,
                0,
                false);
        }
    }

    static void error_timer_cb(lv_timer_t *t)
    {
        auto *self =
            static_cast<BrewController *>(lv_timer_get_user_data(t));

        if (self)
            self->handle_error_countdown();
    }

    static void ok_btn_cb(lv_event_t *e)
    {
        auto *self =
            static_cast<BrewController *>(lv_event_get_user_data(e));

        if (self)
            self->close_error_dialog(true);
    }

    uint8_t current_progress() const
    {
        uint8_t stage = static_cast<uint8_t>(_curr_stage);

        if (stage >= ui_events::BREW_STAGE_STOP)
            return 100;

        return stage * 10;
    }

    void send_stage_information(ui_events::brew_unit_stages stage)
    {
        ui_events::unit_state_msg_t state{};
        state.evt_id = stage;
        xQueueSend(unit_state_queue, &state, 0);
    }

    bool is_brew_error(uint32_t evt) const
    {
        switch (evt)
        {
        case ui_events::E_BREW_UNIT_NO_CUP_DETECTED:
        case ui_events::E_BREW_UNIT_WATER_INTAKE_FAILED:
        case ui_events::E_BREW_UNIT_WATER_HEATER_FAILED:
        case ui_events::E_BREW_UNIT_BEAN_INTAKE_BLOCKED:
        case ui_events::E_BREW_UNIT_HOPPER_GOT_STUCK:
        case ui_events::E_BREW_UNIT_MILK_INTAKE_FAILED:
        case ui_events::E_BREW_UNIT_MILK_HEATER_FAILED:
        case ui_events::E_BREW_UNIT_MILK_OUT_PIPE_BLOCKED:
        case ui_events::E_BREW_UNIT_COFFEE_FILTER_BLOCKED:
            return true;
        default:
            return false;
        }
    }

    bool stage_sent = false;
    ui_events::brew_unit_stages _curr_stage =
        ui_events::BREW_STAGE_INIT;

    lv_timer_t *error_timer = nullptr;
    lv_obj_t *error_mbox = nullptr;
    lv_obj_t *ok_btn = nullptr;
    int countdown = 5;
};

#endif /* FSM_LOGIC_BREWCONTROLLER_HPP */
