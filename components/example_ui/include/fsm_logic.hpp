/**
 * \file            fsm_logic.hpp
 * \brief           FSM stages and events definitions 
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
#ifndef FSM_LOGIC_HPP
#define FSM_LOGIC_HPP
#include <freertos/FreeRTOS.h>
#include "esp_err.h"
namespace ui_events
{

	enum pay_unit_stages
	{
		PAY_STAGE_INIT,
		PAY_STAGE_CARD_DETECTION,
		PAY_STAGE_CARD_AUTHORIZATION,
		PAY_STAGE_SALDO_CHECK,
		PAY_STAGE_FINISH,
	};
	enum brew_unit_stages
	{
		BREW_STAGE_INIT,
		BREW_STAGE_CUP_DETECTION,
		BREW_STAGE_WATER_INTAKE,
		BREW_STAGE_WATER_HEAT,
		BREW_STAGE_BEAN_INTAKE,
		BREW_STAGE_BEAN_GRIND,
		BREW_STAGE_MILK_INTAKE,
		BREW_STAGE_MILK_HEAT,
		BREW_STAGE_MILK_OUTTAKE,
		BREW_STAGE_COFFEE_EXTRACTION,
		BREW_STAGE_STOP,
	};

	enum selection_unit_stages
	{
		SELECTION_STAGE_INIT,
		SELECTION_STAGE_SELECTION_VERIFY,
		SELECTION_STAGE_STOP
	};

	enum unit_event_codes
	{
		E_OK,
		E_UNIT_INIT_FAIL,
		E_SELECTION_UNIT_NOT_ENOUGH_WATER,
		E_SELECTION_UNIT_NOT_ENOUGH_BEANS,
		E_SELECTION_UNIT_NOT_ENOUGH_MILK,
		E_CARD_TIMEOUT,
		E_CARD_NOT_VALID,
		E_CARD_NOT_ENOUGH_SALDO,
		E_BREW_UNIT_NO_CUP_DETECTED,
		E_BREW_UNIT_WATER_INTAKE_FAILED,
		E_BREW_UNIT_WATER_HEATER_FAILED,
		E_BREW_UNIT_BEAN_INTAKE_BLOCKED,
		E_BREW_UNIT_HOPPER_GOT_STUCK,
		E_BREW_UNIT_MILK_INTAKE_FAILED,
		E_BREW_UNIT_MILK_HEATER_FAILED,
		E_BREW_UNIT_MILK_OUT_PIPE_BLOCKED,
		E_BREW_UNIT_COFFEE_FILTER_BLOCKED
	};

	typedef struct
	{
		uint32_t evt_id;
		union
		{
			float amount;
			uint32_t selection;
		} payload;
	} unit_state_msg_t;

	typedef struct
	{
		uint32_t evt_id;
		uint32_t payload;
	} unit_event_msg_t;
};


extern const char *const unit_event_msgs[17];

extern QueueHandle_t unit_state_queue;
extern QueueHandle_t unit_event_queue;

/**
 * @brief initializes both the state and event queue. 
 * @return ESP_OK if okay, ESP_FAIL when not initialized properly
 */
esp_err_t fsm_logic_queues_init();

#endif /* FSM_LOGIC_HPP */