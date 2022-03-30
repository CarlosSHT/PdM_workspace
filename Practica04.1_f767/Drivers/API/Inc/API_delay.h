#include <stdbool.h>
#include <stdint.h>
#include "stm32f7xx_hal.h"
#include "stm32f7xx_nucleo_144.h"

typedef uint32_t tick_t;

typedef bool bool_t;

typedef struct {
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

/* USER CODE BEGIN EFP */
void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);

void Error_Handler_API_delay(void);
