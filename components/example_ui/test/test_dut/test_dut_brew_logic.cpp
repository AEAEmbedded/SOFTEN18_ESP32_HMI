/**
 * \file            test_dut_brew_logic.cpp
 * \brief           Scenario-based DUT test of the Prepare/Brew page and FSM.
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

static void prepare_prepare_page(void)
{
	flush_queue<ui_events::unit_event_msg_t>(unit_event_queue);
	flush_queue<ui_events::unit_state_msg_t>(unit_state_queue);

	lv_scr_load_anim(
		objects.prepare_coffee_page,
		LV_SCR_LOAD_ANIM_MOVE_LEFT,
		300, 0, false);
}

TEST_CASE("Brew completes successfully", "[brew_unit]")
{
	prepare_prepare_page();

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::BREW_STAGE_STOP,
					   pdMS_TO_TICKS(30000)),
		"BREW_STAGE_STOP was never reached");

	simulate_event(ui_events::E_OK);
	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen(objects.cappucino_chooser_page,
						pdMS_TO_TICKS(8000)),
		"Did not return to cappuccino page after brew");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen_settled(objects.cappucino_chooser_page,
								pdMS_TO_TICKS(5000),
								pdMS_TO_TICKS(300)),
		"Cappuccino page transition did not settle after brew");
}

TEST_CASE("Brew fails due to no cup detected", "[brew_unit]")
{
	prepare_prepare_page();

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::BREW_STAGE_CUP_DETECTION,
					   pdMS_TO_TICKS(5000)),
		"Brew did not start");

	simulate_event(ui_events::E_BREW_UNIT_NO_CUP_DETECTED);

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::BREW_STAGE_STOP,
					   pdMS_TO_TICKS(8000)),
		"Brew did not stop after cup detection error");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen(objects.cappucino_chooser_page,
						pdMS_TO_TICKS(8000)),
		"Did not return to cappuccino page after brew error");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen_settled(objects.cappucino_chooser_page,
								pdMS_TO_TICKS(5000),
								pdMS_TO_TICKS(300)),
		"Cappuccino page transition did not settle after brew error");
}

TEST_CASE("Brew fails due to water heater error", "[brew_unit]")
{
	prepare_prepare_page();

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::BREW_STAGE_WATER_HEAT,
					   pdMS_TO_TICKS(10000)),
		"Did not reach water heat stage");

	simulate_event(ui_events::E_BREW_UNIT_WATER_HEATER_FAILED);

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_state(ui_events::BREW_STAGE_STOP,
					   pdMS_TO_TICKS(8000)),
		"Brew did not stop after water heater failure");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen(objects.cappucino_chooser_page,
						pdMS_TO_TICKS(8000)),
		"Did not return to cappuccino page after water heater failure");

	TEST_ASSERT_TRUE_MESSAGE(
		wait_for_screen_settled(objects.cappucino_chooser_page,
								pdMS_TO_TICKS(5000),
								pdMS_TO_TICKS(300)),
		"Cappuccino page transition did not settle after water heater failure");
}
