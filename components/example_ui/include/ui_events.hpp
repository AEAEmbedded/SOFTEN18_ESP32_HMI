#ifndef UI_EVENTS_HPP
#define UI_EVENTS_HPP
#include <freertos/FreeRTOS.h>

namespace ui_events
{

	enum pay_unit_stages
	{
		PAY_STAGE_INIT,
		PAY_STAGE_CARD_DETECTION,
		PAY_STAGE_CARD_AUTHORIZATION,
		PAY_STAGE_SALDO_CHECK,
		PAY_STAGE_FINISH,
	};
	enum brew_unit_stages
	{
		BREW_STAGE_INIT,
		BREW_STAGE_CUP_DETECTION,
		BREW_STAGE_WATER_INTAKE,
		BREW_STAGE_WATER_HEAT,
		BREW_STAGE_BEAN_INTAKE,
		BREW_STAGE_BEAN_GRIND,
		BREW_STAGE_MILK_INTAKE,
		BREW_STAGE_MILK_HEAT,
		BREW_STAGE_MILK_OUTTAKE,
		BREW_STAGE_COFFEE_EXTRACTION,
		BREW_STAGE_STOP,
	};

	enum unit_event_codes
	{
		E_OK,
		E_UNIT_INIT_FAIL,
		E_CARD_TIMEOUT,
		E_CARD_NOT_VALID,
		E_CARD_NOT_ENOUGH_SALDO,
		E_BREW_UNIT_NO_CUP_DETECTED,
		E_BREW_UNIT_NOT_ENOUGH_WATER,
		E_BREW_UNIT_NOT_ENOUGH_BEANS,
		E_BREW_UNIT_NOT_ENOUGH_MILK,
		E_BREW_UNIT_HOPPER_GOT_STUCK,

	};

	typedef struct
	{
		uint32_t evt_id;
		union  {
			float amount;
			uint32_t selection;
		} payload;
	} unit_state_msg_t;

	typedef struct
	{
		uint32_t evt_id;
		uint32_t payload;
	} unit_event_msg_t;
};

extern QueueHandle_t unit_state_queue;
extern QueueHandle_t unit_event_queue;
extern const char* const unit_event_msgs[];
#endif /* UI_EVENTS_HPP */