#include <ui.h>
#include <ui_events.hpp>

QueueHandle_t unit_state_queue;
QueueHandle_t unit_event_queue;

void ui_main_init() {
	unit_state_queue = xQueueCreate(10, sizeof(ui_events::unit_state_msg_t));
    unit_event_queue = xQueueCreate(10, sizeof(ui_events::unit_event_msg_t));
	ui_init();
}