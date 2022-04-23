/*
 * API_gpio.c
 *
 *  Created on: Apr 9, 2022
 *      Author: carlos
 */

#include "API_gpio.h"
#include "stm32f4xx_hal_gpio.h"

#define PG2_PIN                                GPIO_PIN_2
#define PG2_GPIO_PORT                          GPIOG
#define PG2_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG2_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOG_CLK_DISABLE()

#define PG3_PIN                                GPIO_PIN_3
#define PG3_GPIO_PORT                          GPIOG
#define PG3_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOG_CLK_ENABLE()
#define PG3_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOG_CLK_DISABLE()

bool_t gpiosinit() {
	GPIO_InitTypeDef GPIO_InitStruct;

	PG2_GPIO_CLK_ENABLE();

	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = PG2_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(PG2_GPIO_PORT, &GPIO_InitStruct);

	PG3_GPIO_CLK_ENABLE();

	/* Configure the GPIO_LED pin */
	GPIO_InitStruct.Pin = PG3_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(PG3_GPIO_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(PG2_GPIO_PORT, PG2_PIN, GPIO_PIN_SET);

	//!<Set high value G3 for activate I2C MODE in ADXL345
	HAL_GPIO_WritePin(PG3_GPIO_PORT, PG3_PIN, GPIO_PIN_SET);

	return true;
}




void BSP_LEDs_On(bool_t led1, bool_t led2, bool_t led3)
{
	led1? BSP_LED_On(LED1): BSP_LED_Off(LED1);
	led2? BSP_LED_On(LED2): BSP_LED_Off(LED2);
	led3? BSP_LED_On(LED3): BSP_LED_Off(LED3);
//	if (led2) BSP_LED_On(LED2) else BSP_LED_Off(LED2);
//	if (led3) BSP_LED_On(LED3) else BSP_LED_Off(LED3);
}

