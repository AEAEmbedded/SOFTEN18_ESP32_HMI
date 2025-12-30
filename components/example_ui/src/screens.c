#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_cappucino_chooser_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.cappucino_chooser_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff242424), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // coffee_slider_and_buttons_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.coffee_slider_and_buttons_panel = obj;
            lv_obj_set_pos(obj, 400, 80);
            lv_obj_set_size(obj, 355, 322);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff434241), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // strength_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.strength_lbl = obj;
                    lv_obj_set_pos(obj, 86, 6);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Strength");
                }
                {
                    // sugar_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.sugar_lbl = obj;
                    lv_obj_set_pos(obj, 86, 71);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Sugar");
                }
                {
                    // milk_lbl
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.milk_lbl = obj;
                    lv_obj_set_pos(obj, 86, 132);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Milk");
                }
                {
                    // milk_content_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.milk_content_slider = obj;
                    lv_obj_set_pos(obj, 81, 161);
                    lv_obj_set_size(obj, 150, 10);
                    lv_slider_set_range(obj, 1, 3);
                    lv_slider_set_value(obj, 2, LV_ANIM_OFF);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff8900), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // coffee_strength_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.coffee_strength_slider = obj;
                    lv_obj_set_pos(obj, 86, 41);
                    lv_obj_set_size(obj, 150, 10);
                    lv_slider_set_range(obj, 1, 3);
                    lv_slider_set_value(obj, 2, LV_ANIM_OFF);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff8900), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                }
                {
                    // sugar_content_slider
                    lv_obj_t *obj = lv_slider_create(parent_obj);
                    objects.sugar_content_slider = obj;
                    lv_obj_set_pos(obj, 86, 100);
                    lv_obj_set_size(obj, 150, 10);
                    lv_slider_set_range(obj, 1, 3);
                    lv_slider_set_value(obj, 2, LV_ANIM_OFF);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff8900), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                }
                {
                    // strength_increase_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.strength_increase_btn = obj;
                    lv_obj_set_pos(obj, 258, 22);
                    lv_obj_set_size(obj, 59, 37);
                    lv_obj_add_event_cb(obj, action_increase_strength, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // strength_btn_p_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.strength_btn_p_label = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "+");
                        }
                    }
                }
                {
                    // sugar_increase_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.sugar_increase_btn = obj;
                    lv_obj_set_pos(obj, 258, 86);
                    lv_obj_set_size(obj, 59, 37);
                    lv_obj_add_event_cb(obj, action_increase_coffee_sugar_content, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // sugar_btn_p_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.sugar_btn_p_lbl = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "+");
                        }
                    }
                }
                {
                    // milk_increase_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.milk_increase_btn = obj;
                    lv_obj_set_pos(obj, 258, 148);
                    lv_obj_set_size(obj, 59, 37);
                    lv_obj_add_event_cb(obj, action_increase_coffee_milk_content, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // milk_btn_p_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.milk_btn_p_lbl = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "+");
                        }
                    }
                }
                {
                    // strength_decrease_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.strength_decrease_btn = obj;
                    lv_obj_set_pos(obj, 0, 22);
                    lv_obj_set_size(obj, 59, 37);
                    lv_obj_add_event_cb(obj, action_decrease_coffee_strength, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // strenth_btn_n_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.strenth_btn_n_lbl = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // sugar_content_decrease_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.sugar_content_decrease_btn = obj;
                    lv_obj_set_pos(obj, 0, 85);
                    lv_obj_set_size(obj, 59, 37);
                    lv_obj_add_event_cb(obj, action_decrease_coffee_sugar_content, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // sugar_btn_n_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.sugar_btn_n_lbl = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // milk_content_decrease_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.milk_content_decrease_btn = obj;
                    lv_obj_set_pos(obj, 0, 147);
                    lv_obj_set_size(obj, 59, 37);
                    lv_obj_add_event_cb(obj, action_decrease_coffee_milk_content, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // milk_btn_n_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.milk_btn_n_lbl = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // coffee_start_btn
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.coffee_start_btn = obj;
                    lv_obj_set_pos(obj, 111, 232);
                    lv_obj_set_size(obj, 100, 50);
                    lv_obj_add_event_cb(obj, action_coffee_start_event, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff8900), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // coffee_start_btn_lbl
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.coffee_start_btn_lbl = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Start");
                        }
                    }
                }
            }
        }
        {
            // coffee_img
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.coffee_img = obj;
            lv_obj_set_pos(obj, 23, 60);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_cappuccino);
        }
        {
            // coffee_offer_name_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.coffee_offer_name_lbl = obj;
            lv_obj_set_pos(obj, 119, 384);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Cappuccino");
        }
        {
            // coffee_offer_price_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.coffee_offer_price_lbl = obj;
            lv_obj_set_pos(obj, 172, 435);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0,60 EUR-,");
        }
        {
            // date_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.date_lbl = obj;
            lv_obj_set_pos(obj, 23, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "6 Jan 2026");
        }
        {
            // time_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.time_lbl = obj;
            lv_obj_set_pos(obj, 119, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "12:00");
        }
        {
            // div_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.div_lbl = obj;
            lv_obj_set_pos(obj, 107, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffee6f08), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "|");
        }
    }
    
    tick_screen_cappucino_chooser_page();
}

void tick_screen_cappucino_chooser_page() {
}

void create_screen_pay_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.pay_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_add_event_cb(obj, action_pay_page_loaded, LV_EVENT_SCREEN_LOADED, (void *)0);
    lv_obj_add_event_cb(obj, action_pay_page_unloaded, LV_EVENT_SCREEN_UNLOADED, (void *)0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff242424), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // pay_progress_spinner
            lv_obj_t *obj = lv_spinner_create(parent_obj);
            objects.pay_progress_spinner = obj;
            lv_obj_set_pos(obj, 289, 108);
            lv_obj_set_size(obj, 223, 219);
            lv_spinner_set_anim_params(obj, 1000, 60);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xfff77a00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // pin_status_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pin_status_lbl = obj;
            lv_obj_set_pos(obj, 302, 356);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Starting pin transaction...");
        }
        {
            // total_to_pay_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.total_to_pay_lbl = obj;
            lv_obj_set_pos(obj, 197, 31);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Total to pay: ");
        }
        {
            // total_pay_amount_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.total_pay_amount_lbl = obj;
            lv_obj_set_pos(obj, 400, 31);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "0,60 EUR-,");
        }
        {
            // pay_page_back_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.pay_page_back_btn = obj;
            lv_obj_set_pos(obj, 11, 419);
            lv_obj_set_size(obj, 69, 50);
            lv_obj_add_event_cb(obj, action_menu_back_button, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff8900), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "<");
                }
            }
        }
    }
    
    tick_screen_pay_page();
}

void tick_screen_pay_page() {
}

void create_screen_prepare_coffee_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.prepare_coffee_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff242424), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // coffee_prepare_progress_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.coffee_prepare_progress_bar = obj;
            lv_obj_set_pos(obj, 60, 386);
            lv_obj_set_size(obj, 671, 47);
            lv_bar_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfff3a521), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff3a521), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // preparing_coffee_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.preparing_coffee_lbl = obj;
            lv_obj_set_pos(obj, 60, 35);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Preparing your coffee..");
        }
        {
            // progress_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.progress_lbl = obj;
            lv_obj_set_pos(obj, 71, 361);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Progress:");
        }
        {
            // progress_percentage_lbl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.progress_percentage_lbl = obj;
            lv_obj_set_pos(obj, 148, 361);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "10 %");
        }
        {
            // coffee_prepare_img
            lv_obj_t *obj = lv_image_create(parent_obj);
            objects.coffee_prepare_img = obj;
            lv_obj_set_pos(obj, 85, -18);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_meme);
            lv_image_set_scale(obj, 128);
        }
        {
            // coffee_prepare_text_lbl
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.coffee_prepare_text_lbl = obj;
            lv_obj_set_pos(obj, 68, 99);
            lv_obj_set_size(obj, 223, 246);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "Share your coffee experience!\n\nScan this QR-code and share with us how much you liked your freshly set coffee:");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2b2b2b), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // qrcode
            lv_obj_t *obj = lv_qrcode_create(parent_obj);
            objects.qrcode = obj;
            lv_obj_set_pos(obj, 125, 231);
            lv_obj_set_size(obj, 99, 96);
            lv_qrcode_set_size(obj, 96);
            lv_qrcode_set_dark_color(obj, lv_color_hex(0xff000000));
            lv_qrcode_set_light_color(obj, lv_color_hex(0xffe2f5fe));
            lv_qrcode_update(obj, "https://youtu.be/dQw4w9WgXcQ?si=gkEPvFd_P8U4kmHw", 48);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
        }
    }
    
    tick_screen_prepare_coffee_page();
}

void tick_screen_prepare_coffee_page() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_cappucino_chooser_page,
    tick_screen_pay_page,
    tick_screen_prepare_coffee_page,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_cappucino_chooser_page();
    create_screen_pay_page();
    create_screen_prepare_coffee_page();
}
