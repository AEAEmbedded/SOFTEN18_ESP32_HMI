#include <lvgl.h>
#include <screens.h>
#include <stdio.h>

void action_increase_strength(lv_event_t * e) {
	int32_t current_coffee_strength = lv_slider_get_value(objects.coffee_strength_slider);
	int32_t coffee_strength_max_val = lv_slider_get_max_value(objects.coffee_strength_slider);
	if(current_coffee_strength < coffee_strength_max_val) {
		printf("Current strength: %ld \n", current_coffee_strength);
		lv_slider_set_value(objects.coffee_strength_slider, (current_coffee_strength+1), LV_ANIM_OFF);
		printf("New strength: %ld \n", current_coffee_strength+1);
	}
}

void action_decrease_coffee_strength(lv_event_t * e) {
	int32_t current_coffee_strength = lv_slider_get_value(objects.coffee_strength_slider);
	int32_t coffee_strength_min_val = lv_slider_get_min_value(objects.coffee_strength_slider);
	if(current_coffee_strength > coffee_strength_min_val) {
		printf("Current strength: %ld \n", current_coffee_strength);
		lv_slider_set_value(objects.coffee_strength_slider, (current_coffee_strength-1), LV_ANIM_OFF);
		printf("New strength: %ld \n", current_coffee_strength-1);
	}

}

void action_increase_coffee_sugar_content(lv_event_t * e) {
	int32_t current_sugar_content = lv_slider_get_value(objects.sugar_content_slider);
	int32_t sugar_content_max_val = lv_slider_get_max_value(objects.sugar_content_slider);
	if(current_sugar_content < sugar_content_max_val) {
		printf("Current strength: %ld \n", current_sugar_content);
		lv_slider_set_value(objects.sugar_content_slider, (current_sugar_content+1), LV_ANIM_OFF);
		printf("New strength: %ld \n", current_sugar_content+1);
	}
}

void action_increase_coffee_milk_content(lv_event_t * e) {
	int32_t current_milk_content = lv_slider_get_value(objects.milk_content_slider);
	int32_t milk_content_max_val = lv_slider_get_max_value(objects.milk_content_slider);
	if(current_milk_content < milk_content_max_val) {
		printf("Current strength: %ld \n", current_milk_content);
		lv_slider_set_value(objects.milk_content_slider, (current_milk_content+1), LV_ANIM_OFF);
		printf("New strength: %ld \n", current_milk_content+1);
	}
}

void action_decrease_coffee_milk_content(lv_event_t * e) {
	int32_t current_milk_content = lv_slider_get_value(objects.milk_content_slider);
	int32_t milk_content_min_val = lv_slider_get_min_value(objects.milk_content_slider);
	if(current_milk_content > milk_content_min_val) {
		printf("Current strength: %ld \n", current_milk_content);
		lv_slider_set_value(objects.milk_content_slider, (current_milk_content-1), LV_ANIM_OFF);
		printf("New strength: %ld \n", current_milk_content-1);
	}
}

void action_decrease_coffee_sugar_content(lv_event_t * e) {
	int32_t current_sugar_content = lv_slider_get_value(objects.sugar_content_slider);
	int32_t sugar_content_min_val = lv_slider_get_min_value(objects.sugar_content_slider);
	if(current_sugar_content > sugar_content_min_val) {
		printf("Current strength: %ld \n", current_sugar_content);
		lv_slider_set_value(objects.sugar_content_slider, (current_sugar_content-1), LV_ANIM_OFF);
		printf("New strength: %ld \n", current_sugar_content-1);
	}
}

void action_coffee_start_event(lv_event_t * e) {
	lv_scr_load_anim(
        objects.pay_page,
        LV_SCR_LOAD_ANIM_MOVE_LEFT,
        300,   // animation time (ms)
        0,     // delay
        false  // do NOT auto-delete previous screen
    );
}

uint32_t pay_status = 0;
void update_pay_status(lv_timer_t * timer)
{
  /* Use the user_data */
  printf("my_timer called with data: %ld\n", pay_status);
  switch(pay_status) {
	case 1:
	{
		break;
	}
	case 2:
	{
		break;
	}
	case 5:{
		lv_scr_load_anim(
			objects.cappucino_chooser_page,
			LV_SCR_LOAD_ANIM_MOVE_LEFT,
			300,   // animation time (ms)
			0,     // delay
			false  // do NOT auto-delete previous screen
		);
		break;
	}
	default: {
		const char *waiting_for_card_txt = "Waiting for card...";
		char *current_text = lv_label_get_text(objects.pin_status_lbl);
		if(lv_strcmp(current_text, waiting_for_card_txt) != 0) {
			lv_label_set_text(objects.pin_status_lbl, waiting_for_card_txt);
		}
		break;
	}
  }
}
lv_timer_t * pay_status_timer; 

void action_pay_page_loaded(lv_event_t * e) {
	printf("pay_page_loaded\n");
	pay_status_timer = lv_timer_create(update_pay_status, 500,  NULL);
}

void action_pay_page_unloaded(lv_event_t * e) {
	printf("pay_page unloaded\n");
	lv_timer_delete(pay_status_timer);
}

void action_menu_back_button(lv_event_t * e) {
	printf("going back one page");
	lv_scr_load_anim(
			objects.cappucino_chooser_page,
			LV_SCR_LOAD_ANIM_MOVE_LEFT,
			300,   // animation time (ms)
			0,     // delay
			false  // do NOT auto-delete previous screen
	);
}