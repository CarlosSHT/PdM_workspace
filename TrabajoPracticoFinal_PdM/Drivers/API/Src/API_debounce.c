#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h"

#define	DELAY_DB	40	//	Retardo en milisegundos

typedef enum {
	BUTTON_UP, BUTTON_FALLING, BUTTON_DOWN, BUTTON_RAISING,
} debounceState_t;

static debounceState_t estadoActual_DB;

static delay_t struct_delayDB;
static bool_t flag_falling, flag_rising;

static void buttonPressed();			// debe togglear el LED1
static void buttonReleased();		// debe togglear el LED3

// Inicialización del debounce
void debounceFSM_init() {
	delayInit(&struct_delayDB, DELAY_DB); 		// Inicializa delay 40 ms

	estadoActual_DB = BUTTON_UP;				// Estado de maquina inicial BUTTON UP

	BSP_PB_Init(BUTTON_UP, BUTTON_MODE_GPIO);	// Inicialización del boton de usuario
}

void debounceFSM_update() {
	uint8_t button_value = BSP_PB_GetState(BUTTON_USER) ^ 1; //? 0:1
	switch (estadoActual_DB) {
	case BUTTON_UP:									// Estado de maquina boton sin presionar
		if (button_value == 0) {
			estadoActual_DB = BUTTON_FALLING;
//			delayInit(&struct_delayDB, DELAY_DB);
			delayRead(&struct_delayDB);
		}
		break;

	case BUTTON_FALLING:							// Estado de maquina rebote bajada
		if (button_value == 1) {
			estadoActual_DB = BUTTON_UP;
		} else {
			if (delayRead(&struct_delayDB)) {		// Verifica antirebote por 40ms
				estadoActual_DB = BUTTON_DOWN;
				buttonPressed();
			}
		}
		break;

	case BUTTON_DOWN:								// Estado de maquina boton presionado
		if (button_value == 1) {
			estadoActual_DB = BUTTON_RAISING;
			delayRead(&struct_delayDB);
//			delayInit(&struct_delayDB, DELAY_DB);
		}
		break;

	case BUTTON_RAISING:							// Estado de maquina rebote subida
		if (button_value == 0) {
			estadoActual_DB = BUTTON_DOWN;
		} else {
			if (delayRead(&struct_delayDB)) {		// Verifica antirebote por 40ms
				estadoActual_DB = BUTTON_UP;
				buttonReleased();
			}
		}
		break;

	default:
		estadoActual_DB = BUTTON_UP;
		BSP_LED_Off(LED1);
		BSP_LED_Off(LED1);
		flag_falling = false;
		flag_rising = false;
		break;
	}
}

static void buttonPressed() {
	flag_falling = true;
//	BSP_LED_Toggle(LED1);
}

static void buttonReleased() {
	flag_rising = true;
//	BSP_LED_Toggle(LED3);
}

// Función verificación flanco bajada
bool_t readKey() {
	bool_t aux_flag = flag_falling;
	if (flag_falling)
		flag_falling = false;
//	flag_falling = flag_falling? 0:1;
	return aux_flag;
}


// Función verificación flanco subida
bool_t readKey_rise() {
	bool_t aux_flag = flag_rising;
	if (flag_rising)
		flag_rising = false;
	return aux_flag;
}