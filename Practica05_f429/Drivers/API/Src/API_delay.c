#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo_144.h"


void delayInit(delay_t *delay, tick_t duration) {

	// Verifica que las entradas sean correctas
	if (delay == NULL || duration == 0) {
		Error_Handler_API_delay();
	}
//	delay->startTime=HAL_GetTick();
	delay->running=false;	// se inicializa estado apagado
	delay->duration = duration; // se actualiza la duración distinto a cero
}

// delay no bloqueante de un solo tiro
bool_t delayRead(delay_t *delay) {

	bool_t flag = false;

	// Verifica delay no sea nulo
	if (delay == NULL) {
		Error_Handler_API_delay();
	}

	// Si duración del delay es 0 devuelve falso
	if (delay->duration == 0) {
		return flag;
	}


	if (!delay->running) {
		delay->startTime = HAL_GetTick(); 	// establece tiempo de inicio
		delay->running = true;				// establece delay en funcionamiento
		flag=false;
	}
	else {
		if (HAL_GetTick() - delay->startTime >= delay->duration) { // intervalo completado?
			delay->running = false;			// se apaga el delay
			flag = true;					// se devuelve que ocurrió un delay
//			delay->startTime = HAL_GetTick();
		}
	}
	return flag;
}

void delayWrite(delay_t *delay, tick_t duration) {

	// Verifica entrada delay no nula
	if (delay == NULL) {
		Error_Handler_API_delay();
	}

	// Establece duración
	if (delay->running) {
		delay->duration = duration;
	}
}

void Error_Handler_API_delay(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED_RED);
	while (1) {
	}
}
