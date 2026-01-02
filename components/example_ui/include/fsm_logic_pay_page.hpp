/**
 * \file            fsm_logic_pay_page.hpp
 * \brief           Header-only FSM module for the pay page (second page shown)
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
#ifndef FSM_LOGIC_PAYCONTROLLER_HPP
#define FSM_LOGIC_PAYCONTROLLER_HPP

#include "fsm_logic.hpp"
#include <lvgl.h>

namespace pay_strings
{
    static constexpr const char init[] = "Initializing payment module";
    static constexpr const char wait_card[] = "Waiting for card...";
    static constexpr const char auth[] = "Waiting for authorization...";
    static constexpr const char saldo[] = "Checking card saldo...";
    static constexpr const char success[] = "Payment succesfully processed...";

    static constexpr const char *stage_msg[] = {
        init,
        wait_card,
        auth,
        saldo,
        success};
} // namespace pay_strings


class PayController
{
public:
    PayController() = default;

    const char *run_payment(ui_events::unit_event_msg_t &msg)
    {
        if (!stage_sent)
        {
            send_stage_information(_curr_stage, kPaymentAmount);
            stage_sent = true;
        }

        if (xQueueReceive(unit_event_queue, &msg, 0) != pdPASS)
            return current_msg();

        if (msg.evt_id == ui_events::E_OK)
        {
            advance_stage();
        }
        else if (is_valid_error(msg.evt_id))
        {
            show_error(unit_event_msgs[msg.evt_id]);
        }

        return current_msg();
    }

    void reset_status()
    {
        _curr_stage = ui_events::PAY_STAGE_INIT;
        stage_sent = false;
    }

private:
    static constexpr int kErrorCountdown = 5;
    static constexpr float kPaymentAmount = 0.6f;

    void close_error_dialog()
    {
        stop_error_timer();

        if (error_mbox)
        {
            lv_msgbox_close(error_mbox); // release modal grab
            lv_obj_del(error_mbox);
            error_mbox = nullptr;
            cancel_btn = nullptr;
        }

        notify_payment_finished();

        lv_scr_load_anim(
            objects.cappucino_chooser_page,
            LV_SCR_LOAD_ANIM_MOVE_LEFT,
            300,
            0,
            false);
    }

    void stop_error_timer()
    {
        if (error_timer)
        {
            lv_timer_del(error_timer);
            error_timer = nullptr;
        }
    }

    void handle_error_countdown()
    {
        if (!error_mbox || !cancel_btn)
            return;

        if (--countdown <= 0)
        {
            close_error_dialog();
            return;
        }

        char buf[32];
        lv_snprintf(buf, sizeof(buf), "Cancel (%d)", countdown);
        lv_label_set_text(lv_obj_get_child(cancel_btn, 0), buf);
    }

    static void error_timer_cb(lv_timer_t *timer)
    {
        auto *self = static_cast<PayController *>(
            lv_timer_get_user_data(timer));

        if (self)
            self->handle_error_countdown();
    }

    static void cancel_btn_cb(lv_event_t *e)
    {
        auto *self = static_cast<PayController *>(
            lv_event_get_user_data(e));

        if (self)
            self->close_error_dialog();
    }

    void show_error(const char *text)
    {
        if (!text || error_mbox)
            return;

        countdown = kErrorCountdown;

        error_mbox = lv_msgbox_create(nullptr);
        lv_msgbox_add_title(error_mbox, "Payment");
        lv_msgbox_add_text(error_mbox, text);

        cancel_btn = lv_msgbox_add_footer_button(
            error_mbox,
            "Cancel (5)");

        lv_obj_add_event_cb(
            cancel_btn,
            cancel_btn_cb,
            LV_EVENT_CLICKED,
            this);

        error_timer = lv_timer_create(
            error_timer_cb,
            1000,
            this);
    }

    void advance_stage()
    {
        stage_sent = false;

        if (_curr_stage < ui_events::PAY_STAGE_FINISH)
        {
            _curr_stage =
                static_cast<ui_events::pay_unit_stages>(_curr_stage + 1);
            return;
        }

        _curr_stage = ui_events::PAY_STAGE_INIT;

        lv_scr_load_anim(
            objects.prepare_coffee_page,
            LV_SCR_LOAD_ANIM_MOVE_LEFT,
            300,
            200,
            false);
    }

    void send_stage_information(ui_events::pay_unit_stages stage, float amount)
    {
        ui_events::unit_state_msg_t state{};
        state.evt_id = stage;
        state.payload.amount = amount;
        xQueueSend(unit_state_queue, &state, 0);
    }

    void notify_payment_finished()
    {
        ui_events::unit_state_msg_t state{};
        state.evt_id = ui_events::PAY_STAGE_FINISH;
        xQueueSend(unit_state_queue, &state, 0);
    }

    bool is_valid_error(uint32_t evt) const
    {
        return evt < (sizeof(unit_event_msgs) / sizeof(unit_event_msgs[0]));
    }

    const char *current_msg() const
    {
        return pay_strings::stage_msg[_curr_stage];
    }

    bool stage_sent = false;
    ui_events::pay_unit_stages _curr_stage = ui_events::PAY_STAGE_INIT;

    lv_timer_t *error_timer = nullptr;
    lv_obj_t *error_mbox = nullptr;
    lv_obj_t *cancel_btn = nullptr;

    int countdown = kErrorCountdown;
};

#endif /* FSM_LOGIC_PAYCONTROLLER_HPP */
