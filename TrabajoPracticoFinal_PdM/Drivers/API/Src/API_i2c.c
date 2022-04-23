/*
 * API_i2c.c
 *
 *  Created on: Apr 9, 2022
 *      Author: carlos
 */

#include "API_i2c.h"
#include "stm32f4xx_hal_i2c.h"

#define	i2c_TIMEOUT	200				//!< Timeout I2C in miliseconds

I2C_HandleTypeDef I2CApiHandle;		//!< Instance Handle I2C

bool_t i2cinit() {

	bool_t init_flag = false;

	GPIO_InitTypeDef GPIO_InitStruct;

	/* I2C1 clock enable */
	__HAL_RCC_I2C1_CLK_ENABLE();

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	I2CApiHandle.Instance = I2C1;
	I2CApiHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2CApiHandle.Init.ClockSpeed = 100000;
	I2CApiHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2CApiHandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2CApiHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
	I2CApiHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
	I2CApiHandle.Init.OwnAddress1 = 0;
	I2CApiHandle.Init.OwnAddress2 = 0;

	if (HAL_I2C_Init(&I2CApiHandle) == HAL_OK)
		init_flag = true;

	return init_flag;
}

bool_t i2c_checkDevice(uint16_t ApiDevAddress) {
	bool_t devAvailable = false;
	HAL_StatusTypeDef returnflag;
	returnflag = HAL_I2C_IsDeviceReady(&I2CApiHandle, ApiDevAddress, 2,
	i2c_TIMEOUT);
	if (returnflag == HAL_OK) {
		devAvailable = true;
	}

	return devAvailable;
}

void i2c_masterRead(uint8_t dev_address, uint8_t reg_address,
		uint8_t *val_pData, uint8_t n_bytes) {
	HAL_I2C_Mem_Read(&I2CApiHandle, (uint16_t) dev_address,
			(uint8_t) reg_address, I2C_MEMADD_SIZE_8BIT, val_pData, n_bytes,
			i2c_TIMEOUT);

}

void i2c_masterWrite(uint8_t dev_address, uint8_t reg_address,
		uint8_t *val_pData) {
	HAL_I2C_Mem_Write(&I2CApiHandle, (uint16_t) dev_address,
			(uint8_t) reg_address, I2C_MEMADD_SIZE_8BIT, val_pData, 1,
			i2c_TIMEOUT);
}
