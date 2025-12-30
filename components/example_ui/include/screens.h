#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *cappucino_chooser_page;
    lv_obj_t *pay_page;
    lv_obj_t *prepare_coffee_page;
    lv_obj_t *coffee_slider_and_buttons_panel;
    lv_obj_t *strength_lbl;
    lv_obj_t *sugar_lbl;
    lv_obj_t *milk_lbl;
    lv_obj_t *milk_content_slider;
    lv_obj_t *coffee_strength_slider;
    lv_obj_t *sugar_content_slider;
    lv_obj_t *strength_increase_btn;
    lv_obj_t *strength_btn_p_label;
    lv_obj_t *sugar_increase_btn;
    lv_obj_t *sugar_btn_p_lbl;
    lv_obj_t *milk_increase_btn;
    lv_obj_t *milk_btn_p_lbl;
    lv_obj_t *strength_decrease_btn;
    lv_obj_t *strenth_btn_n_lbl;
    lv_obj_t *sugar_content_decrease_btn;
    lv_obj_t *sugar_btn_n_lbl;
    lv_obj_t *milk_content_decrease_btn;
    lv_obj_t *milk_btn_n_lbl;
    lv_obj_t *coffee_start_btn;
    lv_obj_t *coffee_start_btn_lbl;
    lv_obj_t *coffee_img;
    lv_obj_t *coffee_offer_name_lbl;
    lv_obj_t *coffee_offer_price_lbl;
    lv_obj_t *date_lbl;
    lv_obj_t *time_lbl;
    lv_obj_t *div_lbl;
    lv_obj_t *pay_progress_spinner;
    lv_obj_t *pin_status_lbl;
    lv_obj_t *total_to_pay_lbl;
    lv_obj_t *total_pay_amount_lbl;
    lv_obj_t *pay_page_back_btn;
    lv_obj_t *coffee_prepare_progress_bar;
    lv_obj_t *preparing_coffee_lbl;
    lv_obj_t *progress_lbl;
    lv_obj_t *progress_percentage_lbl;
    lv_obj_t *coffee_prepare_img;
    lv_obj_t *coffee_prepare_text_lbl;
    lv_obj_t *qrcode;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_CAPPUCINO_CHOOSER_PAGE = 1,
    SCREEN_ID_PAY_PAGE = 2,
    SCREEN_ID_PREPARE_COFFEE_PAGE = 3,
};

void create_screen_cappucino_chooser_page();
void tick_screen_cappucino_chooser_page();

void create_screen_pay_page();
void tick_screen_pay_page();

void create_screen_prepare_coffee_page();
void tick_screen_prepare_coffee_page();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/