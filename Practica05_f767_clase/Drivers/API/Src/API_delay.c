#include "API_delay.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144.h"

void delayInit(delay_t *delay, tick_t duration) {

	if (delay == NULL || duration == 0) {
		Error_Handler_API_delay();
	}
//	delay->startTime=HAL_GetTick();
	delay->running=false;
	delay->duration = duration;
}

bool_t delayRead(delay_t *delay) {

	bool_t flag = false;

	if (delay == NULL) {
		Error_Handler_API_delay();
	}

	if (delay->duration == 0) {
		return flag;
	}

	if (!delay->running) {
		delay->startTime = HAL_GetTick();
		delay->running = true;
		flag=false;
	}
	else {
		if (HAL_GetTick() - delay->startTime >= delay->duration) {
			delay->running = false;
			flag = true;
//			delay->startTime = HAL_GetTick();
		}
	}
	return flag;
}

void delayWrite(delay_t *delay, tick_t duration) {

	if (delay == NULL) {
		Error_Handler_API_delay();
	}

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
