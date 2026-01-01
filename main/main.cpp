#include "board_config.h"
#include <display_driver.h>
#include <touch_driver.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <ui_events.hpp>
#include <ui_main.hpp>


static esp_lcd_panel_handle_t lcd_panel = NULL;

static i2c_master_bus_handle_t my_bus = NULL;
static esp_lcd_panel_io_handle_t touch_io_handle = NULL;
static esp_lcd_touch_handle_t touch_handle = NULL;

/* LVGL display and touch */
static lv_display_t *lvgl_disp = NULL;
static lv_indev_t *lvgl_touch_indev = NULL;

void hardware_sim_task(void *pvarg)
{
    ui_events::unit_state_msg_t state_msg;
    ui_events::unit_event_msg_t evt_msg;
    evt_msg.evt_id = ui_events::E_OK;
    while (1)
    {
        if (xQueueReceive(unit_state_queue, &state_msg, portMAX_DELAY) == pdPASS)
        {
            xQueueSend(unit_event_queue, &evt_msg, 10);
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(display_driver_lcd_init(&lcd_panel));
    ESP_ERROR_CHECK(touch_driver_init(&my_bus, &touch_io_handle, &touch_handle));
    ESP_ERROR_CHECK(display_driver_lvgl_init(lcd_panel, touch_handle, &lvgl_disp, &lvgl_touch_indev));

    lvgl_port_lock(0);
    ui_main_init();
    lvgl_port_unlock();
    xTaskCreate(hardware_sim_task, "hardware_sim", 2048, NULL, 1, NULL);
}