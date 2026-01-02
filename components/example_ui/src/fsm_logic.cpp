/**
 * \file            fsm_logic.cpp
 * \brief           Declaration of queue's and msgs used by FSM
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
#include <fsm_logic.hpp>

const char *const unit_event_msgs[17] = {
	"",
	"Has failed to initialize.\nPlease consult your local service technician for help.",
	"The water tank is empty, please refill it.",
	"The coffee bean reservoir is empty, please refill it.",
	"The milk powder reservoir is empty, please refill it.",
	"No card was detected!\nPlease tap the card against the cardreader.",
	"The card detected is not supported!\nPlease use a supported card.",
	"Not enough saldo, please try again later!",
	"No cup was detected.\nPlease place a cup under the machine and press confirm.",
	"Water intake is blocked, please turn-off the machine and check it.",
	"Water heater has failed, please contact a local service engineer to fix it.",
	"Bean intake has failed, please turn-off the machine and unblock the passage.",
	"The coffee bean hopper got stuck, please unblock it.",
	"The milk intake has failed, please turn-off the machine \n and check the intake of the milk heater \nfor blockages.",
	"The milk heater has failed, please contact a local service engineer to fix it.",
	"The milk heater output tube seems to be blocked\n, please unblock it.",
	"The coffee filter seems to be blocked, \nunblock it and try again."};

QueueHandle_t unit_state_queue;
QueueHandle_t unit_event_queue;


esp_err_t fsm_logic_queues_init()
{
	unit_state_queue = xQueueCreate(10, sizeof(ui_events::unit_state_msg_t));
	unit_event_queue = xQueueCreate(10, sizeof(ui_events::unit_event_msg_t));
	int success = (unit_event_queue && unit_state_queue) ? ESP_OK : ESP_FAIL;
	return success;
}