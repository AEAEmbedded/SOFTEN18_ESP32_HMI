extern "C" {
#include <lvgl.h>
#include <screens.h>
}

#include <stdio.h>
#include "ui_logic_paycontroller.hpp"

/* -------------------------------------------------------------------------- */
/*  Globals                                                                    */
/* -------------------------------------------------------------------------- */

static PayController ctrl;
static lv_timer_t* pay_status_timer = nullptr;

/* -------------------------------------------------------------------------- */
/*  Unit event messages (ONE definition, cpp-only)                             */
/* -------------------------------------------------------------------------- */

const char* const unit_event_msgs[] = {
    "",
    "Has failed to initialize.\nPlease consult your local service technician for help.",
    "No card was detected!\nPlease tap the card against the cardreader.",
    "The card detected is not supported!\nPlease use a supported card.",
    "Not enough saldo, please try again later!",
    "No cup was detected.\nPlease place a cup under the machine and press confirm.",
    "The water tank is empty, please refill it.",
    "The coffee bean reservoir is empty, please refill it.",
    "The milk powder reservoir is empty, please refill it.",
    "The coffee bean hopper got stuck, please unblock it."
};

/* -------------------------------------------------------------------------- */
/*  LVGL callbacks                                                             */
/* -------------------------------------------------------------------------- */

extern "C" void update_pay_status(lv_timer_t*)
{
    ui_events::unit_event_msg_t msg{};
    const char* new_text = ctrl.run_payment(msg);
    const char* current  = lv_label_get_text(objects.pin_status_lbl);

    if (lv_strcmp(current, new_text) != 0) {
        lv_label_set_text(objects.pin_status_lbl, new_text);
    }
}

extern "C" void action_pay_page_loaded(lv_event_t*)
{
    printf("pay_page_loaded\n");

    if (!pay_status_timer) {
        pay_status_timer = lv_timer_create(update_pay_status, 500, nullptr);
    }
}

extern "C" void action_pay_page_unloaded(lv_event_t*)
{
    printf("pay_page_unloaded\n");

    ctrl.reset_status();

    if (pay_status_timer) {
        lv_timer_delete(pay_status_timer);
        pay_status_timer = nullptr;
    }
}

extern "C" void action_menu_back_button(lv_event_t*)
{
    printf("going back one page\n");

    lv_scr_load_anim(
        objects.cappucino_chooser_page,
        LV_SCR_LOAD_ANIM_MOVE_LEFT,
        300,
        0,
        false
    );
}
