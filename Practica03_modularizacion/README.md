Resolución del Practico 03

Punto 01. 

Se crea una API_DELAY, creando un folder "API" y las subcarpetas "Src" e "Inc".

Se crean los archivos API_delay.c y API_delay.h


Punto 02:

Se utilizaron 2 variables para identificar los indices del vector de leds a fin de que el anterior se encuentre en modo OFF y el presente en modo ON cada 200 milisegundos.

---(led3)---[LED1]---[LED2]---[LED3]---(led1)---
---( OFF)---[ ON ]---[----]---[----]---
         ---[ OFF]---[ ON ]---[----]---
	 ---[----]---[ OFF]---[ ON ]---
	 ---[----]---[----]---[ OFF]---( ON )---

Se muestra la correspondencia entre las variables y los estados

	 ledCurrent_index  <----> ON
	 ledPrevious_index <----> OFF

¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o estos están hardcodeados? ¿Hay números “mágicos”?

Si esta localizado en la linea 33 del archivo main.c del Practico03


¿Qué bibliotecas estándar se debieron agregar a API_delay.h para que el código compile? Si las funcionalidades de una API propia crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.

Se incluyeron las siguientes bibliotecas

Estandar
#include <stdbool.h>
#include <stdint.h>
Bibliotecas del microcontrolador
#include "stm32f4xx_hal.h"		// Señala las funciones HAL a utilizar como el HAL_delay
#include "stm32f4xx_nucleo_144.h"	// Archivo de inclusión del BSP de la tarjeta NUCLEO


¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?

Se realizan control de parametros en :

delayInit  -> Se verifica que la estructura del delay no sea NULL y el tiempo de duración sea diferente a 0 ya que el tipo de variable de "duracion" es entero sin signo.
delayRead  -> Verifica que la estructura delay no sea NULL, y el si la duración configurada es 0 automaticamente devuelve el valor FALSE
delayWrite -> Verifica que la estructura delay no sea NULL

Error_Handler_API_delay --- Se ejecuta esta función en caso exista un error en las funciones anteriores.






