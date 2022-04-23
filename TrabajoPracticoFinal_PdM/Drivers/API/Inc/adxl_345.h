/*
 * adxl_345.h
 *
 *  Created on: 22 abr. 2022
 *      Author: carlo
 */

#ifndef ADXL_345_H_
#define ADXL_345_H_

typedef bool bool_t;

/**
 * @enum adxl345_reg
 * @brief Numbered list of register addresses
 * from ADXL345
 *
 */
typedef enum {
	address_DEVID, /**< address_DEVID */
	address_THRESH_TAP = 29, /**< address_THRESH_TAP */
	address_OFSX, /**< address_OFSX */
	address_OFSY, /**< address_OFSY */
	address_OFSZ, /**< address_OFSZ */
	address_DUR, /**< address_DUR */
	address_Latent, /**< address_Latent */
	address_Window, /**< address_Window */
	address_THRESH_ACT, /**< address_THRESH_ACT */
	address_THRESH_INACT, /**< address_THRESH_INACT */
	address_TIME_INACT, /**< address_TIME_INACT */
	address_ACT_INACT_CTL, /**< address_ACT_INACT_CTL */
	address_THRESH_FF, /**< address_THRESH_FF */
	address_TIME_FF, /**< address_TIME_FF */
	address_TAP_AXES, /**< address_TAP_AXES */
	address_ACT_TAP_STATUS,/**< address_ACT_TAP_STATUS */
	address_BW_RATE, /**< address_BW_RATE */
	address_POWER_CTL, /**< address_POWER_CTL */
	address_INT_ENABLE, /**< address_INT_ENABLE */
	address_INT_MAP, /**< address_INT_MAP */
	address_INT_SOURCE, /**< address_INT_SOURCE */
	address_DATA_FORMAT, /**< address_DATA_FORMAT */
	address_DATAX0, /**< address_DATAX0 */
	address_DATAX1, /**< address_DATAX1 */
	address_DATAY0, /**< address_DATAY0 */
	address_DATAY1, /**< address_DATAY1 */
	address_DATAZ0, /**< address_DATAZ0 */
	address_DATAZ1, /**< address_DATAZ1 */
	address_FIFO_CTL, /**< address_FIFO_CTL */
	address_FIFO_STATUS, /**< address_FIFO_STATUS */
} adxl345_reg;

/**
 * @enum adxl345_rates
 * @brief Numbered 4 bits values from ADXL345 data rate
 * sample
 *
 */
typedef enum {
	Data_Rate_0000_10_Hz,/**< Data_Rate_0000_10_Hz */
	Data_Rate_0000_20_Hz,/**< Data_Rate_0000_20_Hz */
	Data_Rate_0000_39_Hz,/**< Data_Rate_0000_39_Hz */
	Data_Rate_0000_78_Hz,/**< Data_Rate_0000_78_Hz */
	Data_Rate_0001_56_Hz,/**< Data_Rate_0001_56_Hz */
	Data_Rate_0003_13_Hz,/**< Data_Rate_0003_13_Hz */
	Data_Rate_0006_25_Hz,/**< Data_Rate_0006_25_Hz */
	Data_Rate_0012_50_Hz,/**< Data_Rate_0012_50_Hz */
	Data_Rate_0025_00_Hz,/**< Data_Rate_0025_00_Hz */
	Data_Rate_0050_00_Hz,/**< Data_Rate_0050_00_Hz */
	Data_Rate_0100_00_Hz,/**< Data_Rate_0100_00_Hz */
	Data_Rate_0200_00_Hz,/**< Data_Rate_0200_00_Hz */
	Data_Rate_0400_00_Hz,/**< Data_Rate_0400_00_Hz */
	Data_Rate_0800_00_Hz,/**< Data_Rate_0800_00_Hz */
	Data_Rate_1600_00_Hz,/**< Data_Rate_1600_00_Hz */
	Data_Rate_3200_00_Hz, /**< Data_Rate_3200_00_Hz */
} adxl345_rates;

/**
 * @enum  adxl345_ranges
 * @brief Value ranges 2 bits from ADXL345
 *
 */
typedef enum {
	gRange_2g, /**< gRange_2g */
	gRange_4g, /**< gRange_4g */
	gRange_8g, /**< gRange_8g */
	gRange_16g, /**< gRange_16g */
} adxl345_ranges;

/**
 * @struct adxl345_d
 * @brief Principal values from ADXL345
 *
 *	@devId		Device ID
 *	@acc_On		Accelerometer flag measuring
 *	@g_Range	Range 2g,4g,8g,16g value
 *	@data_Rate	Actual rate
 */
typedef struct {
	uint8_t devId;
	bool_t acc_On;
	uint8_t g_Range;
	uint8_t data_Rate;
	uint16_t val_x;
	uint16_t val_y;
	uint16_t val_z;
/* To implement */
//	uint8_t th_Tap;
//	uint8_t time_Tap;
} adxl345_d;

/**
 * @fn bool_t adxl345_init()
 * @brief 	Initialize accelerometer ADXL345
 * 			checking if the device is found
 * 			and the	identifier is correct
 *
 * @return	True if all is OK, else False
 */
bool_t adxl345_init();

/**
 * @fn uint8_t adxl345_getID()
 * @brief	Return (read) value ID from
 * 			address_DEVID (0x00) register
 *
 * @return	Value address in uint8_t format
 */
uint8_t adxl345_getID();

/**
 * @fn uint8_t adxl345_getRange()
 * @brief 	Get range Gravity value
 * 			from ADXL345 device memory
 *
 * @return	Value from address_DATA_FORMAT register
 */
uint8_t adxl345_getRange();

/**
 * @fn uint8_t adxl345_getRate()
 * @brief 	Get data rate (Hz) in byte
 * 			from ADXL345 device memory
 *
 * @return	Value from address_BW_RATE register
 */
uint8_t adxl345_getRate();

/**
 * @fn void adxl345_Enable(bool_t)
 * @brief	Set measure on/!off using
 * 			WK_UP_BYTE definition byte
 *
 * @param state_pwr	Indicates need ON (True) or OFF (False)
 */
void adxl345_Enable(bool_t state_pwr);

/**
 * @fn void adxl345_setRange(adxl345_ranges)
 * @brief	Update struct variable range and set bits
 * 			on address_BW_RATE
 *
 * @param range	2 Bits from 0-3
 */
void adxl345_setRange(adxl345_ranges range);

/**
 * @fn void adxl345_setRate(adxl345_rates)
 * @brief 	Set data rate (sampling) in normal
 * 			power mode on address address_BW_RATE
 *
 * @param rate	Value in 16 bits, from 0 to 15
 */
void adxl345_setRate(adxl345_rates rate);

/**
 * @fn void adxl345_getVals(int16_t*, int16_t*, int16_t*)
 * @brief 	Read 2 words from address_DATAX0, address_DATAY0
 * 			and address_DATAZ0.
 *
 * @param x	value gravity axis X in 16 signed bits format
 * @param y	value gravity axis Y in 16 signed bits format
 * @param z	value gravity axis Z in 16 signed bits format
 */
void adxl345_getVals(int16_t *x, int16_t *y, int16_t *z);

#endif /* ADXL_345_H_ */
