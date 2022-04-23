/*
 * adxl_345.c
 *
 *  Created on: 22 abr. 2022
 *      Author: carlos
 */

#include "API_i2c.h"
#include "API_uart.h"
#include "adxl_345.h"

#define 	ADXL345			0x53<<1		//!< ADXL345 ADDRESS left shifted
#define 	ADXL345_DEVID	0b11100101	//!< DEVID in binary from ADXL345
#define 	LOW_POWER_BIT	0			//!< Low power Bit in 0x2C BWRATE
#define 	WK_UP_BYTE		0b00001000	//!< Byte to wake up accelerometer

typedef uint8_t valReg_type;

//!< Private representative variable
//! adxl345 with information
static adxl345_d adxl345_sensor;

/**
 * @fn uint8_t adxl345_getValReg(adxl345_reg)
 * @brief Protected register read ADXL345 function
 *
 * @param reg_address	Value from enumerate adxl345_reg
 * @return				Unsigned 8 bit value from address
 */
static uint8_t adxl345_getValReg(adxl345_reg reg_address);

/**
 * @fn void adxl345_setValReg(adxl345_reg, valReg_type)
 * @brief Protected update value in ADXL345 register address
 *
 * @param reg_address	Register to update
 * @param val_reg		Unsigned 8 bit value to write
 */
static void adxl345_setValReg(adxl345_reg reg_address, valReg_type val_reg);

bool_t adxl345_init() {
	uint8_t id_val = 0;

	if (i2c_checkDevice(ADXL345)) {
		id_val = adxl345_getID();
	}

	if (id_val != ADXL345_DEVID) {
		return false;
	}

	adxl345_sensor = (adxl345_d ) { .devId = id_val, .acc_On = false, .g_Range =
					gRange_2g, .data_Rate = Data_Rate_0025_00_Hz, .val_x = 0,
					.val_y = 0, .val_z = 0, };
	adxl345_Enable(adxl345_sensor.acc_On);
	adxl345_setRange(adxl345_sensor.g_Range);
	adxl345_setRate(adxl345_sensor.data_Rate);

	return true;

}

uint8_t adxl345_getID() {
	uint8_t val_address = 0;

	i2c_masterRead(ADXL345, address_DEVID, &val_address, 1);

	return val_address;
}

void adxl345_Enable(bool_t state_pwr) {
	uint8_t aux_wkUP = 0;

	aux_wkUP = adxl345_getValReg(address_POWER_CTL);
	if (state_pwr) {
		aux_wkUP = aux_wkUP | WK_UP_BYTE;
	} else {
		aux_wkUP = aux_wkUP & ~WK_UP_BYTE;
	}
	adxl345_setValReg(address_POWER_CTL, aux_wkUP);
}

static uint8_t adxl345_getValReg(adxl345_reg reg_address) {
	uint8_t temp_vreg = 0;

	i2c_masterRead(ADXL345, reg_address, &temp_vreg, 1);

	return temp_vreg;
}

static void adxl345_setValReg(adxl345_reg reg_address, valReg_type val_reg) {
	i2c_masterWrite(ADXL345, reg_address, &val_reg);
}

uint8_t adxl345_getRange() {
	uint8_t val_reg = 0;

	val_reg = adxl345_getValReg(address_DATA_FORMAT);

	return val_reg;
}

void adxl345_setRange(adxl345_ranges range) {
	uint8_t val_reg = 0;
	adxl345_sensor.g_Range = range;
	val_reg = adxl345_getRange();
	val_reg = (val_reg & 0b11111100) | adxl345_sensor.g_Range;
	adxl345_setValReg(address_DATA_FORMAT, val_reg);
}

uint8_t adxl345_getRate() {
	uint8_t val_reg = 0;
	val_reg = adxl345_getValReg(address_BW_RATE);
	return val_reg;
}

void adxl345_setRate(adxl345_rates rate) {
	uint8_t val_reg = 0;

	adxl345_sensor.data_Rate = rate;
	val_reg = LOW_POWER_BIT << 4 | adxl345_sensor.data_Rate;
	i2c_masterWrite(ADXL345, address_BW_RATE, &val_reg);

}

void adxl345_getVals(int16_t *x, int16_t *y, int16_t *z) {
	uint8_t x_buffer[2] = { 0 };
	uint8_t y_buffer[2] = { 0 };
	uint8_t z_buffer[2] = { 0 };

	if (!adxl345_sensor.acc_On) {
		adxl345_Enable(true);
	}

	i2c_masterRead(ADXL345, address_DATAX0, x_buffer, 2);
	i2c_masterRead(ADXL345, address_DATAY0, y_buffer, 2);
	i2c_masterRead(ADXL345, address_DATAZ0, z_buffer, 2);

	*x = x_buffer[1] << 8 | x_buffer[0];
	*y = y_buffer[1] << 8 | y_buffer[0];
	*z = z_buffer[1] << 8 | z_buffer[0];

}

