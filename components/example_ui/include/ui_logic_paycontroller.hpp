#ifndef LOGIC_PAYCONTROLLER_HPP
#define LOGIC_PAYCONTROLLER_HPP

#include "ui_events.hpp"
#include <lvgl.h>

/* -------------------------------------------------------------------------- */
/*  Payment stage strings                                                      */
/* -------------------------------------------------------------------------- */

namespace pay_strings {

static constexpr const char init[]        = "Initializing payment module";
static constexpr const char wait_card[]   = "Waiting for card...";
static constexpr const char auth[]        = "Waiting for authorization...";
static constexpr const char saldo[]       = "Checking card saldo...";
static constexpr const char success[]     = "Payment succesfully processed...";

static constexpr const char* stage_msg[] = {
    init,
    wait_card,
    auth,
    saldo,
    success
};

} // namespace pay_strings

/* -------------------------------------------------------------------------- */
/*  PayController                                                              */
/* -------------------------------------------------------------------------- */

class PayController {
public:
    PayController() = default;

    const char* run_payment(ui_events::unit_event_msg_t& msg)
    {
        if (!stage_sent) {
            send_stage_information(_curr_stage, 0.6f);
            stage_sent = true;
        }

        if (xQueueReceive(unit_event_queue, &msg, 0) != pdPASS)
            return current_msg();

        if (msg.evt_id == ui_events::E_OK) {
            advance_stage();
        } else {
            show_error(unit_event_msgs[msg.evt_id]);
        }

        return current_msg();
    }

    void reset_status()
    {
        _curr_stage = ui_events::PAY_STAGE_INIT;
        stage_sent  = false;
    }

private:
    /* ----------------------------- LVGL helpers ---------------------------- */

    static void event_cb(lv_event_t* e)
    {
        lv_obj_t* btn = static_cast<lv_obj_t*>(lv_event_get_target(e));
        lv_obj_t* label = lv_obj_get_child(btn, 0);
        printf("Button %s clicked\n", lv_label_get_text(label));
    }


    static void show_error(const char* text)
    {
        lv_obj_t* mbox = lv_msgbox_create(nullptr);
        lv_msgbox_add_title(mbox, "Payment");
        lv_msgbox_add_text(mbox, text);
        lv_msgbox_add_close_button(mbox);

        lv_obj_t* btn;
        btn = lv_msgbox_add_footer_button(mbox, "Apply");
        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, nullptr);

        btn = lv_msgbox_add_footer_button(mbox, "Cancel");
        lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, nullptr);
    }

    /* ----------------------------- State logic ----------------------------- */

    void advance_stage()
    {
        stage_sent = false;

        if (_curr_stage < ui_events::PAY_STAGE_FINISH) {
            _curr_stage = static_cast<ui_events::pay_unit_stages>(_curr_stage + 1);
            return;
        }

        // FINISH → INIT transition
        _curr_stage = ui_events::PAY_STAGE_INIT;
        lv_scr_load_anim(
            objects.prepare_coffee_page,
            LV_SCR_LOAD_ANIM_MOVE_LEFT,
            300,
            200,
            false
        );
    }

    void send_stage_information(ui_events::pay_unit_stages stage, float amount)
    {
        ui_events::unit_state_msg_t state{};
        state.evt_id = stage;
        state.payload.amount = amount;
        xQueueSend(unit_state_queue, &state, 0);
    }

    const char* current_msg() const
    {
        return pay_strings::stage_msg[_curr_stage];
    }

    /* ----------------------------- Data members ----------------------------- */

    bool stage_sent = false;
    ui_events::pay_unit_stages _curr_stage = ui_events::PAY_STAGE_INIT;
};

#endif /* LOGIC_PAYCONTROLLER_HPP */
