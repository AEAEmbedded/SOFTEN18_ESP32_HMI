/**
 * \file            test_dut_pay_logic.cpp
 * \brief           Scenario-based DUT test of the Pay page and FSM.
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

static void prepare_pay_page(void)
{
    flush_queue<ui_events::unit_event_msg_t>(unit_event_queue);
    flush_queue<ui_events::unit_state_msg_t>(unit_state_queue);

    lv_scr_load_anim(
        objects.pay_page,
        LV_SCR_LOAD_ANIM_MOVE_LEFT,
        300, 0, false);
}

TEST_CASE("Payment completes successfully", "[pay_unit]")
{
    prepare_pay_page();

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_state(ui_events::PAY_STAGE_FINISH,
                       pdMS_TO_TICKS(15000)),
        "PAY_STAGE_FINISH was never reached");

    simulate_event(ui_events::E_OK);

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_screen(objects.prepare_coffee_page,
                        pdMS_TO_TICKS(5000)),
        "Did not enter prepare page after successful payment");

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_screen_settled(objects.prepare_coffee_page,
                                pdMS_TO_TICKS(5000),
                                pdMS_TO_TICKS(300)),
        "Prepare page transition did not settle");
}

TEST_CASE("Payment fails on authorization error", "[pay_unit]")
{
    prepare_pay_page();

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_state(ui_events::PAY_STAGE_CARD_AUTHORIZATION,
                       pdMS_TO_TICKS(10000)),
        "Authorization stage not reached");

    ui_events::unit_event_msg_t evt{};
    evt.evt_id = ui_events::E_CARD_NOT_VALID;
    xQueueSend(unit_event_queue, &evt, 0);

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_state(ui_events::PAY_STAGE_FINISH, pdMS_TO_TICKS(8000)),
        "Payment error handling did not finish");

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_screen(objects.cappucino_chooser_page,
                        pdMS_TO_TICKS(8000)),
        "Did not return to cappuccino page after insufficient saldo");

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_screen_settled(objects.cappucino_chooser_page,
                                pdMS_TO_TICKS(5000),
                                pdMS_TO_TICKS(300)),
        "Cappuccino page transition did not settle after saldo failure");
}

TEST_CASE("Payment fails on insufficient saldo", "[pay_unit]")
{
    prepare_pay_page();

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_state(ui_events::PAY_STAGE_SALDO_CHECK,
                       pdMS_TO_TICKS(12000)),
        "Saldo check stage not reached");

    ui_events::unit_event_msg_t evt{};
    evt.evt_id = ui_events::E_CARD_NOT_ENOUGH_SALDO;
    xQueueSend(unit_event_queue, &evt, 0);

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_state(ui_events::PAY_STAGE_FINISH, pdMS_TO_TICKS(8000)),
        "Payment error handling did not finish");
    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_screen(objects.cappucino_chooser_page,
                        pdMS_TO_TICKS(8000)),
        "Did not return to cappuccino page after insufficient saldo");

    TEST_ASSERT_TRUE_MESSAGE(
        wait_for_screen_settled(objects.cappucino_chooser_page,
                                pdMS_TO_TICKS(5000),
                                pdMS_TO_TICKS(300)),
        "Cappuccino page transition did not settle after saldo failure");
}
