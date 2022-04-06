/*
 * API_uart.c
 *
 *  Created on: Apr 2, 2022
 *      Author: carlos
 */

#include "API_uart.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_uart.h"

UART_HandleTypeDef UartHandle;

static void Error_Handler();

bool_t uartinit() {
	// Configuramos los parametros del UART
	UartHandle.Instance = USART3;
	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK) {
		Error_Handler();
		return false;
	}
	return true;
}

void uartsendString(uint8_t *pstring) {
	uint16_t pos = 0;
	do {
		HAL_UART_Transmit(&UartHandle, &pstring[pos], 1, 100);
		pos++;
	} while (*(pstring + pos) != '\0');
	HAL_UART_Transmit(&UartHandle, &pstring[pos], 1, 100);
}

void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	HAL_UART_Transmit(&UartHandle, pstring, size, 100);
}

void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {

}

static void Error_Handler() {
//	BSP_LED_Init(LED2);
//	BSP_LED_On(LED2);
	while (1) {

	}
}

