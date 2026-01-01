extern "C"
{
#include <lvgl.h>
#include <screens.h>
}
#include <stdio.h>

static void adjust_slider(lv_obj_t* slider, int delta)
{
    int32_t value = lv_slider_get_value(slider);
    int32_t min   = lv_slider_get_min_value(slider);
    int32_t max   = lv_slider_get_max_value(slider);

    int32_t new_value = value + delta;

    if (new_value < min || new_value > max)
        return;

    printf("Current value: %ld\n", value);
    lv_slider_set_value(slider, new_value, LV_ANIM_OFF);
    printf("New value: %ld\n", new_value);
}


extern "C" {

void action_increase_strength(lv_event_t*)
{
    adjust_slider(objects.coffee_strength_slider, +1);
}

void action_decrease_coffee_strength(lv_event_t*)
{
    adjust_slider(objects.coffee_strength_slider, -1);
}

void action_increase_coffee_sugar_content(lv_event_t*)
{
    adjust_slider(objects.sugar_content_slider, +1);
}

void action_decrease_coffee_sugar_content(lv_event_t*)
{
    adjust_slider(objects.sugar_content_slider, -1);
}

void action_increase_coffee_milk_content(lv_event_t*)
{
    adjust_slider(objects.milk_content_slider, +1);
}

void action_decrease_coffee_milk_content(lv_event_t*)
{
    adjust_slider(objects.milk_content_slider, -1);
}

void action_coffee_start_event(lv_event_t*)
{
    lv_scr_load_anim(
        objects.pay_page,
        LV_SCR_LOAD_ANIM_MOVE_LEFT,
        300,
        0,
        false
    );
}

} // extern "C"
