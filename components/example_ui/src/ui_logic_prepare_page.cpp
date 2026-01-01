#include "ui_events.hpp"
#include "ui_logic_brewcontroller.hpp"

extern "C" {
#include <lvgl.h>
#include <screens.h>
}

#include <stdio.h>

/* -------------------------------------------------------------------------- */
/*  Globals                                                                    */
/* -------------------------------------------------------------------------- */

static BrewController brew_ctrl;
static lv_timer_t* prepare_status_timer = nullptr;

/* -------------------------------------------------------------------------- */
/*  LVGL callbacks                                                             */
/* -------------------------------------------------------------------------- */

extern "C" void update_brew_progress(lv_timer_t*)
{
    char progress_str[8]; // "100 %" + '\0' fits

    uint8_t progress = brew_ctrl.run_brew();

    lv_bar_set_value(
        objects.coffee_prepare_progress_bar,
        progress,
        LV_ANIM_OFF
    );

    lv_snprintf(progress_str, sizeof(progress_str), "%u %%", progress);
    lv_label_set_text(objects.progress_percentage_lbl, progress_str);
}

extern "C" void action_prepare_page_loaded(lv_event_t*)
{
    printf("prepare_page_loaded\n");

    if (!prepare_status_timer) {
        prepare_status_timer =
            lv_timer_create(update_brew_progress, 500, nullptr);
    }
}

extern "C" void action_prepare_page_unloaded(lv_event_t*)
{
    printf("prepare_page_unloaded\n");

    if (prepare_status_timer) {
        lv_timer_delete(prepare_status_timer);
        prepare_status_timer = nullptr;
    }
}
