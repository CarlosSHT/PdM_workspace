# PdM_workspace
STM32CubeIDE workspace para Programación de microcontroladores - CESE - FIUBA

Alumno: Carlos Herrera Trujillo

Se muestran los siguientes proyectos:

-Practica01_01. uso de leds, boton y retardos (HAL_DELAY)

  commit 0a0a246d5b3dd2f0da458f1a5173cc1f1bc2f0ba: Contiene el punto 01 resuelto en clase.
  
  commit 352375b30d70d19c18f17d37d90e07e5a0f7fcf1: Es una solución básica de control de sentido de leds
  

-Practica01_solUBA. Solución realizada por el profesor.


-Practica02_grupal. tema de retardo no bloqueante
  
  commit 05ce25ad8cdf190362792ec5a4be6b1cd4713659: Soluciónrealizada en clase del punto 01, linea 99 error de subida a git no se actualizó el código
                                                   debe verificar si existe un delay en curso para actualizar el retardo.
                                                   
  commit f75d60b3eecbc381535e108402f6e4be9fddf1f6: Solución realizada fuera de clase del punto 02, se añadió la linea 111 a fin de actualizar el tiempo 
                                                   de inicio del contador.
                                                   Se permite la creación de un arreglo de LEDs y retardos de diferentes longitudes, de forma de que no se obligue a
                                                   titilar todos los leds (en caso sea menor cantidad de retardos) o solo se disponga de los necesarios (en caso sea
                                                   mayor la cantidad de retardos con respecto al número de leds).
                                                   Se logró probar la portabilidad del programa en la placa nucleo-f767 utilizando la carpeta BSP respectiva, así mismo,
                                                   se utilizó diferentes valores de retardo.
                                                   
  commit 07aead27a4d11e7a10b9bf3269c7eac61ab75981: Solución con los retardos requeridos (100,500 y 1000ms) por el punto2-practica02 PdM.
