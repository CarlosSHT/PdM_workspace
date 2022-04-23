/*
 * adxl345_FSM.h
 *
 *  Created on: Apr 23, 2022
 *      Author: carlos
 */

#ifndef ADXL345_FSM_H_
#define ADXL345_FSM_H_
#include "main.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
/**
 * @enum rx_cmds_t
 * @brief Enumerate index commands list received
 *
 */
typedef enum {
	rx_Start, rx_Idle, rx_Config,
} rx_cmds_t;

/**
 * @enum projectState_t
 * @brief Machine states from program
 *
 */
typedef enum {
	FSM_reset, IDLE, CONFIG, SAMPLING,
} projectState_t;

/**
 * @fn void adxl345_FSM_init()
 * @brief 	Send Initialize State message,
 * 			initialize FSM adxl345 loading
 * 			default values and set state machine
 * 			to IDLE
 *
 */
void adxl345_FSM_init();

/**
 * @fn void adxl345_FSM_update()
 * @brief	FSM machine with waiting state (IDLE),
 * 			configuration state (CONFIG) and samples
 * 			transmission (SAMPLING) every SAMPLE_DELAY
 * 			milliseconds
 *
 */
void adxl345_FSM_update();




#endif /* ADXL345_FSM_H_ */
