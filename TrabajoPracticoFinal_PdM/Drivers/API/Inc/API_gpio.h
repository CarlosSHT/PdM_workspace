/*
 * API_gpio.h
 *
 *  Created on: Apr 9, 2022
 *      Author: carlos
 */

#ifndef API_INC_API_GPIO_H_
#define API_INC_API_GPIO_H_
#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

typedef bool bool_t;

/**
 * @fn bool_t gpiosinit()
 * @brief	Configure clock and parameters
 * 			for 2 GPIO pins G2,G3 and it enable
 * 			to activate I2C mode in ADXL345
 *
 * @return
 */
bool_t gpiosinit();

/**
 * @fn void BSP_LEDs_On(bool_t, bool_t, bool_t)
 * @brief On each led : LED1, LED2, LED3 by bool flag
 *
 * @param led1	flag true (ON) or false (OFF)
 * @param led2	flag true (ON) or false (OFF)
 * @param led3	flag true (ON) or false (OFF)
 */
void BSP_LEDs_On(bool_t led1, bool_t led2, bool_t led3);
#endif /* API_INC_API_GPIO_H_ */
