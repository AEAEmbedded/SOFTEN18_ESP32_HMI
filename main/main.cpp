#include "config/board_config.h"
#include "display_driver/display_driver.h"
#include "touch_driver/touch_driver.h"
#include <esp_log.h>

static esp_lcd_panel_handle_t lcd_panel = NULL;

static i2c_master_bus_handle_t my_bus = NULL;
static esp_lcd_panel_io_handle_t touch_io_handle = NULL;
static esp_lcd_touch_handle_t touch_handle = NULL;

/* LVGL display and touch */
static lv_display_t *lvgl_disp = NULL;
static lv_indev_t *lvgl_touch_indev = NULL;

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(display_driver_lcd_init(&lcd_panel));
    ESP_ERROR_CHECK(touch_driver_init(&my_bus, &touch_io_handle, &touch_handle));
    ESP_ERROR_CHECK(display_driver_lvgl_init(lcd_panel, touch_handle, &lvgl_disp, &lvgl_touch_indev));

    lvgl_port_lock(0);

    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_bg_opa(label, LV_OPA_TRANSP, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFF0000), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lvgl_port_unlock();
}