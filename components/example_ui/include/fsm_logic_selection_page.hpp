/**
 * \file            fsm_logic_selection_page.hpp
 * \brief           Header-only FSM module for the (cappuccino) selection page (first page shown)
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
#ifndef FSM_LOGIC_SELECTION_PAGE_HPP
#define FSM_LOGIC_SELECTION_PAGE_HPP

#include "fsm_logic.hpp"
#include <lvgl.h>

class SelectionController
{
public:
	SelectionController() = default;

	void run_selection(ui_events::unit_event_msg_t &msg)
	{
		if (xQueueReceive(unit_event_queue, &msg, 0) != pdPASS)
			return;

		switch (msg.evt_id)
		{
		case ui_events::E_OK:
			go_to_pay_page();
			break;

		case ui_events::E_SELECTION_UNIT_NOT_ENOUGH_WATER:
		case ui_events::E_SELECTION_UNIT_NOT_ENOUGH_BEANS:
		case ui_events::E_SELECTION_UNIT_NOT_ENOUGH_MILK:
			show_error(unit_event_msgs[msg.evt_id]);
			break;

		default:
			break;
		}
	}

private:
	static constexpr int kErrorCountdown = 5;

	void go_to_pay_page()
	{
		lv_scr_load_anim(
			objects.pay_page,
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

	void dismiss_error_dialog_no_signal()
	{
		stop_error_timer();

		if (error_mbox)
		{
			lv_msgbox_close(error_mbox);
			lv_obj_del(error_mbox);
			error_mbox = nullptr;
			cancel_btn = nullptr;
		}
	}

	void close_error_dialog()
	{
		if (!error_mbox && !error_timer)
			return;

		dismiss_error_dialog_no_signal();

		notify_selection_finished();

		lv_scr_load_anim(
			objects.cappucino_chooser_page,
			LV_SCR_LOAD_ANIM_MOVE_LEFT,
			300,
			0,
			false);
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
		lv_snprintf(buf, sizeof(buf), "OK (%d)", countdown);
		lv_label_set_text(lv_obj_get_child(cancel_btn, 0), buf);
	}

	static void error_timer_cb(lv_timer_t *timer)
	{
		auto *self = static_cast<SelectionController *>(
			lv_timer_get_user_data(timer));

		if (self)
			self->handle_error_countdown();
	}

	static void ok_btn_cb(lv_event_t *e)
	{
		auto *self = static_cast<SelectionController *>(
			lv_event_get_user_data(e));

		if (self)
			self->close_error_dialog();
	}

	void show_error(const char *text)
	{
		if (!text || error_mbox)
			return;

		dismiss_error_dialog_no_signal();

		countdown = kErrorCountdown;

		error_mbox = lv_msgbox_create(nullptr);
		lv_msgbox_add_title(error_mbox, "Selection");
		lv_msgbox_add_text(error_mbox, text);

		cancel_btn = lv_msgbox_add_footer_button(
			error_mbox,
			"OK (5)");

		lv_obj_add_event_cb(
			cancel_btn,
			ok_btn_cb,
			LV_EVENT_CLICKED,
			this);

		error_timer = lv_timer_create(
			error_timer_cb,
			1000,
			this);
	}

	void notify_selection_finished()
	{
		ui_events::unit_state_msg_t state{};
		state.evt_id = ui_events::SELECTION_STAGE_STOP;
		xQueueSend(unit_state_queue, &state, 0);
	}

	lv_timer_t *error_timer = nullptr;
	lv_obj_t *error_mbox = nullptr;
	lv_obj_t *cancel_btn = nullptr;

	int countdown = kErrorCountdown;
};

#endif /* FSM_LOGIC_SELECTION_PAGE_HPP */
