/*
 * adxl345_FSM.c
 *
 *  Created on: Apr 23, 2022
 *      Author: carlos
 */
#include "adxl345_FSM.h"
#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"
#include "API_gpio.h"
#include "adxl_345.h"

#define 	SAMPLE_DELAY	100
#define 	ADXL345			0x53<<1
#define 	ADXL345_DEVID	0b11100101

static projectState_t curr_tpState, prev_tpState;

static delay_t accSample_delay;
static uint8_t acc_Range,acc_Rate;
static int16_t val_axisX, val_axisY, val_axisZ = 0;

static const char *rx_Cmds[] = { "Start", "Idle_", "Confg"};

static char serial_bufferTx[1024];
static char serial_bufferRx[1024];
static uint16_t cont_txtBuffer = 0;
static HAL_StatusTypeDef msg_Received;


void adxl345_FSM_init() {
	uartsendString((uint8_t*) "\nInit State\r\n");
	delayInit(&accSample_delay, SAMPLE_DELAY); //!< Send samples each SAMPLE_DELAY
	if (!adxl345_init()) {
		Error_Handler();
	}
	HAL_Delay(1000);
	prev_tpState = FSM_reset;
	curr_tpState = IDLE;
}

void adxl345_FSM_update() {
	//!< Check command received
	msg_Received = uartReceiveStringSize((uint8_t*) serial_bufferRx, 5);

	switch (curr_tpState) {

	/**
	 * Waiting until button is pressed or
	 * serial command is received (SAMPLING, CONFIGURE)
	 */
	case IDLE:
		if (prev_tpState != curr_tpState) {
			uartsendString((uint8_t*) "\nIdle State\r\n");
			adxl345_Enable(false);
			BSP_LEDs_On(false,false,false);
			prev_tpState = curr_tpState;
		}

		BSP_LEDs_On(true,true,true);
		if (msg_Received == HAL_OK) {
			if (strcmp((const char*) serial_bufferRx, rx_Cmds[rx_Start]) == 0)
				curr_tpState = SAMPLING;

			if (strcmp((const char*) serial_bufferRx, rx_Cmds[rx_Config]) == 0)
				curr_tpState = CONFIG;
		}

		if (readKey())
			curr_tpState = CONFIG;
		break;

		/**
		 * Receives commands through the serial port for
		 * set gravity ranges in 2g, 4g, 8g or 16g and
		 * sample rates in normal mode from 0.1Hz (index=0)
		 * to 3.2KHz (index=15)
		 */
	case CONFIG:
		if (prev_tpState != curr_tpState) {
			uartsendString((uint8_t*) "\nConfig State\r\n");
			prev_tpState = curr_tpState;
			BSP_LEDs_On(false,false,false);
		}
		BSP_LEDs_On(true,false,false);
		/**
		 * Commands in ASCII
		 * Range command = ran_0, ran_1, ran_2, or "ran_3
		 * Sample rate command = rt_00, rt_01, rt_02 ... rt_15
		 */
		if (msg_Received == HAL_OK) {
			if (serial_bufferRx[0] == 'r' && serial_bufferRx[1] == 'a'
					&& serial_bufferRx[2] == 'n' && serial_bufferRx[3] == '_'
					&& serial_bufferRx[4] > 47 && serial_bufferRx[4] < 52) {
				adxl345_setRange(serial_bufferRx[4] - 48);
			}

			if (serial_bufferRx[0] == 'r' && serial_bufferRx[1] == 't'
					&& serial_bufferRx[2] == '_' && serial_bufferRx[3] > 47
					&& serial_bufferRx[3] < 58 && serial_bufferRx[4] > 47
					&& serial_bufferRx[4] < 58) {
				adxl345_setRate(
						(serial_bufferRx[3] - 48) * 10
								+ (serial_bufferRx[4] - 48));
				msg_Received = HAL_ERROR;
			}

			if (strcmp((const char*) serial_bufferRx, rx_Cmds[rx_Start]) == 0)
				curr_tpState = SAMPLING;
		}

		/**
		 * Print by actual principal configuration values from ADXL345
		 * before change state
		 */
		if (readKey()) {
			cont_txtBuffer = 0;
			acc_Range=adxl345_getRange();
			acc_Rate=adxl345_getRate();
			if ((acc_Rate>>5)!=0) {
				Error_Handler();
			}
			cont_txtBuffer = sprintf(serial_bufferTx,
					"\n DeviceID ADXL345 = 0x%02X "
							" Range n = %d"
							" Rate  n = %d\n", adxl345_getID(),
							acc_Range,acc_Rate );
			uartSendStringSize((uint8_t*) serial_bufferTx, cont_txtBuffer);
			curr_tpState = SAMPLING;
			HAL_Delay(2500);
		}

		break;

	case SAMPLING:
		if (prev_tpState != curr_tpState) {
			uartsendString((uint8_t*) "\nSampling State\r\n");
			prev_tpState = curr_tpState;
			BSP_LEDs_On(false,false,false);
		}

		/**
		 * Get and visualize values from axis (X,Y,Z)
		 * in decimal base, negative or positive.
		 */
		if (delayRead(&accSample_delay)) {
			delayRead(&accSample_delay);
			adxl345_getVals(&val_axisX, &val_axisY, &val_axisZ);
			cont_txtBuffer = 0;
			cont_txtBuffer = sprintf(serial_bufferTx,
					"\n Valor X = %d\t Valor Y = %d\t Valor Z = %d\t\r\n",
					val_axisX, val_axisY, val_axisZ);
			uartSendStringSize((uint8_t*) serial_bufferTx, cont_txtBuffer);

			BSP_LED_Toggle(LED2);
		}

		if (readKey())
			curr_tpState = IDLE;
		break;

	default:
		curr_tpState = IDLE;
		adxl345_Enable(false);
		break;
	}
}

