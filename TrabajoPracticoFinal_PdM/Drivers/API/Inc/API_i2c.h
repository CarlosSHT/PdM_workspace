/*
 * API_i2c.h
 *
 *  Created on: Apr 9, 2022
 *      Author: carlos
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"

typedef bool bool_t;

/**
 * @fn bool_t i2cinit()
 * @brief Initialize, first GPIO from I2C after
 * I2C clock and parameters
 *
 * @return True if all is Ok, else false
 */
bool_t i2cinit();

/**
 * @fn bool_t i2c_checkDevice(uint16_t)
 * @brief Check recognized device on I2C bus
 *
 * @param ApiDevAddress: Address in 16bits max
 * @return	True if device is found, else false
 */
bool_t i2c_checkDevice(uint16_t ApiDevAddress);

/**
 * @fn void i2c_masterRead(uint8_t, uint8_t, uint8_t*, uint8_t)
 * @brief Memory reading operation
 *
 * @param dev_address:  Slave device address in bus
 * @param reg_address: 	Register address to read
 * @param val_pData:	variable updated with data
 * @param n_bytes:		number of words read
 */
void i2c_masterRead(uint8_t dev_address, uint8_t reg_address,
		uint8_t *val_pData, uint8_t n_bytes);

/**
 * @fn void i2c_masterWrite(uint8_t, uint8_t, uint8_t*)
 * @brief Memory write operation
 *
 * @param dev_address:	Slave device address in bus
 * @param reg_address	Register address to write
 * @param val_pData		Data to write
 */
void i2c_masterWrite(uint8_t dev_address, uint8_t reg_address,
		uint8_t *val_pData);

#endif /* API_INC_API_I2C_H_ */
