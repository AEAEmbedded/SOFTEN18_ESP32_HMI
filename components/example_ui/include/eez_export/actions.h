#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_increase_strength(lv_event_t * e);
extern void action_decrease_coffee_strength(lv_event_t * e);
extern void action_increase_coffee_sugar_content(lv_event_t * e);
extern void action_increase_coffee_milk_content(lv_event_t * e);
extern void action_decrease_coffee_milk_content(lv_event_t * e);
extern void action_decrease_coffee_sugar_content(lv_event_t * e);
extern void action_coffee_start_event(lv_event_t * e);
extern void action_pay_page_loaded(lv_event_t * e);
extern void action_pay_page_unloaded(lv_event_t * e);
extern void action_menu_back_button(lv_event_t * e);
extern void action_prepare_page_loaded(lv_event_t * e);
extern void action_prepare_page_unloaded(lv_event_t * e);
extern void action_cappuccino_page_loaded(lv_event_t * e);
extern void action_cappuccino_page_unloaded(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/