#include "API_debounce.h"
#include "API_delay.h"

#define	DELAY_DB	40	//	Retardo en milisegundos

typedef enum {
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;

static debounceState_t estadoActual_DB;

static delay_t struct_delayDB;
static bool_t flag_falling;

static void buttonPressed();			// debe togglear el LED1
//static void buttonReleased();		// debe togglear el LED3

void debounceFSM_init() {
	delayInit(&struct_delayDB, DELAY_DB);
	estadoActual_DB = BUTTON_UP;

	BSP_PB_Init(BUTTON_UP, BUTTON_MODE_GPIO);
}

void debounceFSM_update() {
	uint8_t button_value = BSP_PB_GetState(BUTTON_USER) ^ 1; //? 0:1
	switch (estadoActual_DB) {
	case BUTTON_UP:
		if (button_value == 0) {
			estadoActual_DB = BUTTON_FALLING;
//			delayInit(&struct_delayDB, DELAY_DB);
			delayRead(&struct_delayDB);
		} else {
			estadoActual_DB = BUTTON_UP;
		}
		break;
	case BUTTON_FALLING:
		if (button_value == 1) {
			estadoActual_DB = BUTTON_UP;
		} else {
			if (delayRead(&struct_delayDB)) {

				estadoActual_DB = BUTTON_DOWN;
				buttonPressed();
			}
		}

	case BUTTON_DOWN:
		if (button_value == 1) {
			estadoActual_DB = BUTTON_RAISING;
			delayRead(&struct_delayDB);
//			delayInit(&struct_delayDB, DELAY_DB);
		}
		break;

	case BUTTON_RAISING:
		if (button_value == 0) {
			estadoActual_DB = BUTTON_DOWN;
		} else {
			if (delayRead(&struct_delayDB)) {
				estadoActual_DB = BUTTON_UP;
//					buttonReleased();
			}
		}
	default:
		break;
	}
}

static void buttonPressed() {
	flag_falling = true;
}

//void buttonReleased() {
//	BSP_LED_Toggle(LED3);
//}

bool_t readKey()
{
	bool_t aux_flag = flag_falling;
	if (flag_falling)
		flag_falling = false;
//	flag_falling = flag_falling? 0:1;
	return aux_flag;
}