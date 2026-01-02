/**
 * \file            test_helpers.hpp
 * \brief           Commonly used functions in the DUT-tests to help navigate the FSM and Queue logic.
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
#ifndef TEST_HELPERS_HPP
#define TEST_HELPERS_HPP

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <stdint.h>
#include <lvgl.h>

template <typename T>
static inline void flush_queue(QueueHandle_t q)
{
	if (!q)
		return;

	T tmp;
	while (xQueueReceive(q, &tmp, 0) == pdPASS)
	{
		// discard
	}
}

static inline bool wait_for_screen(lv_obj_t *screen,
								   TickType_t timeout)
{
	TickType_t start = xTaskGetTickCount();

	while ((xTaskGetTickCount() - start) < timeout)
	{
		vTaskDelay(pdMS_TO_TICKS(50));

		if (lv_scr_act() == screen)
			return true;
	}
	return false;
}

/**
 * Wait until a screen becomes active AND stays active
 * for at least `stable_time`.
 *
 * This prevents overlapping lv_scr_load_anim() calls
 * between sequential tests.
 */
static inline bool wait_for_screen_settled(lv_obj_t *screen,
										   TickType_t timeout,
										   TickType_t stable_time)
{
	TickType_t start = xTaskGetTickCount();
	TickType_t stable_start = 0;

	while ((xTaskGetTickCount() - start) < timeout)
	{
		vTaskDelay(pdMS_TO_TICKS(50));

		if (lv_scr_act() == screen)
		{
			if (stable_start == 0)
				stable_start = xTaskGetTickCount();

			if ((xTaskGetTickCount() - stable_start) >= stable_time)
				return true;
		}
		else
		{
			stable_start = 0;
		}
	}
	return false;
}

/**
 * Wait for a specific unit_state evt_id to appear on a queue.
 * Used for PAY_STAGE_FINISH, SELECTION_STAGE_STOP, etc.
 */
static inline bool wait_for_state(uint32_t expected_evt,
								  TickType_t timeout)
{
	ui_events::unit_state_msg_t state{};
	ui_events::unit_event_msg_t evt{};
	TickType_t start = xTaskGetTickCount();

	while ((xTaskGetTickCount() - start) < timeout)
	{
		if (xQueueReceive(unit_state_queue, &state, pdMS_TO_TICKS(200)) == pdPASS)
		{
			if (state.evt_id == expected_evt)
				return true;
			evt.evt_id = ui_events::E_OK;
			xQueueSend(unit_event_queue, &evt, 0);
		}
	}
	return false;
}

static inline void simulate_event(uint32_t event)
{
	ui_events::unit_event_msg_t evt{};
	evt.evt_id = event;
	xQueueSend(unit_event_queue, &evt, 0);
}

#endif /* TEST_HELPERS_HPP */