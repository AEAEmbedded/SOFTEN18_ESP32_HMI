#include <limits.h>
#include "unity.h"
#include <ui.h>
#include <ui_events.hpp>

TEST_CASE("Check for insufficient saldo on card fails", "[pay_unit]")
{
    ui_events::unit_state_msg_t state_msg{};
    ui_events::unit_event_msg_t evt_msg{};

    const TickType_t timeout = pdMS_TO_TICKS(15000);
    TickType_t start = xTaskGetTickCount();

    bool saldo_stage_reached = false;

    while ((xTaskGetTickCount() - start) < timeout)
    {
        if (xQueueReceive(unit_state_queue, &state_msg, pdMS_TO_TICKS(500)) == pdPASS)
        {
            if (state_msg.evt_id == ui_events::PAY_STAGE_SALDO_CHECK)
            {
                evt_msg.evt_id = ui_events::E_CARD_NOT_ENOUGH_SALDO;
                xQueueSend(unit_event_queue, &evt_msg, 0);
                saldo_stage_reached = true;
                break;
            }

            // Normal progression
            evt_msg.evt_id = ui_events::E_OK;
            xQueueSend(unit_event_queue, &evt_msg, 0);
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(
        saldo_stage_reached,
        "PAY_STAGE_SALDO_CHECK was never reached");
}
