#ifndef UI_LOGIC_BREWCONTROLLER_HPP
#define UI_LOGIC_BREWCONTROLLER_HPP

#include "ui_events.hpp"
#include <screens.h>
#include <lvgl.h>

/* -------------------------------------------------------------------------- */
/*  Brew stage → progress mapping                                              */
/* -------------------------------------------------------------------------- */

namespace brew_progress {

static constexpr uint8_t stage[] = {
    0,    // BREW_STAGE_INIT
    5,    // BREW_STAGE_CUP_DETECTION
    10,   // BREW_STAGE_WATER_INTAKE
    20,   // BREW_STAGE_WATER_HEAT
    30,   // BREW_STAGE_BEAN_INTAKE
    45,   // BREW_STAGE_BEAN_GRIND
    60,   // BREW_STAGE_MILK_INTAKE
    70,   // BREW_STAGE_MILK_HEAT
    80,   // BREW_STAGE_MILK_OUTTAKE
    90,   // BREW_STAGE_COFFEE_EXTRACTION
    100   // BREW_STAGE_STOP
};

} // namespace brew_progress

/* -------------------------------------------------------------------------- */
/*  BrewController                                                             */
/* -------------------------------------------------------------------------- */

class BrewController {
public:
    BrewController() = default;

    uint8_t run_brew()
    {
        if (!stage_sent) {
            send_stage_information(_curr_stage);
            stage_sent = true;
        }

        ui_events::unit_event_msg_t msg;
        if (xQueueReceive(unit_event_queue, &msg, 0) != pdPASS)
            return current_progress();

        if (msg.evt_id == ui_events::E_OK) {
            advance_stage();
        }

        return current_progress();
    }

private:
    void advance_stage()
    {
        stage_sent = false;

        if (_curr_stage < ui_events::BREW_STAGE_STOP) {
            _curr_stage = static_cast<ui_events::brew_unit_stages>(_curr_stage + 1);
            return;
        }

        // STOP → INIT transition
        _curr_stage = ui_events::BREW_STAGE_INIT;
        lv_scr_load_anim(
            objects.cappucino_chooser_page,
            LV_SCR_LOAD_ANIM_MOVE_LEFT,
            300,
            200,
            false
        );
    }

    void send_stage_information(ui_events::brew_unit_stages stage)
    {
        ui_events::unit_state_msg_t state{};
        state.evt_id = stage;
        state.payload.amount = brew_progress::stage[stage] / 100.0f;
        xQueueSend(unit_state_queue, &state, 0);
    }

    uint8_t current_progress() const
    {
        return brew_progress::stage[_curr_stage];
    }

    bool stage_sent = false;
    ui_events::brew_unit_stages _curr_stage = ui_events::BREW_STAGE_INIT;
};

#endif /* UI_LOGIC_BREWCONTROLLER_HPP */
