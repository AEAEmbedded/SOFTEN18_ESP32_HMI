/**
 * \file            test_dut_selection_logic.cpp
 * \brief           Scenario-based DUT test of the (cappuccino) Selection page and FSM.
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
#include <limits.h>
#include "unity.h"
#include <ui_main.hpp>
#include <fsm_logic.hpp>
#include <screens.h>
#include "test_helpers.hpp"

static void prepare_selection_page(void)
{
	flush_queue<ui_events::unit_event_msg_t>(unit_event_queue);
	flush_queue<ui_events::unit_state_msg_t>(unit_state_queue);

	lv_scr_load_anim(
		objects.cappucino_chooser_page,
		LV_SCR_LOAD_ANIM_MOVE_LEFT,
		300, 0, false);
}

static void simulate_start_button(void)
{
	ui_events::unit_state_msg_t state{};
	state.evt_id = ui_events::SELECTION_STAGE_SELECTION_VERIFY;
	xQueueSend(unit_state_queue, &state, 0);
}

TEST_CASE("Selection start succeeds and enters pay page", "[selection_unit]")
{
	prepare_selection_page();

	simulate_start_button();

	simulate_event(ui_events::E_OK);

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen(objects.pay_page, pdMS_TO_TICKS(5000)),
		"Did not enter pay page after successful selection verification");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen_settled(objects.pay_page,
								pdMS_TO_TICKS(5000),
								pdMS_TO_TICKS(300)),
		"Pay page transition did not settle");
}

TEST_CASE("Selection fails due to missing water", "[selection_unit]")
{
	prepare_selection_page();

	simulate_start_button();

	simulate_event(ui_events::E_SELECTION_UNIT_NOT_ENOUGH_WATER);

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::SELECTION_STAGE_STOP, pdMS_TO_TICKS(8000)),
		"Selection error dialog did not close");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen(objects.cappucino_chooser_page, pdMS_TO_TICKS(8000)),
		"Selection page not restored after water error");
}

TEST_CASE("Selection fails due to missing beans", "[selection_unit]")
{
	prepare_selection_page();

	simulate_start_button();

	simulate_event(ui_events::E_SELECTION_UNIT_NOT_ENOUGH_BEANS);

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::SELECTION_STAGE_STOP, pdMS_TO_TICKS(8000)),
		"Selection error dialog did not close");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen(objects.cappucino_chooser_page, pdMS_TO_TICKS(8000)),
		"Selection page not restored after beans error");
}

TEST_CASE("Selection fails due to missing milk", "[selection_unit]")
{
	prepare_selection_page();

	simulate_start_button();

	simulate_event(ui_events::E_SELECTION_UNIT_NOT_ENOUGH_MILK);

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::SELECTION_STAGE_STOP, pdMS_TO_TICKS(8000)),
		"Selection error dialog did not close");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen(objects.cappucino_chooser_page, pdMS_TO_TICKS(8000)),
		"Selection page not restored after milk error");
}
