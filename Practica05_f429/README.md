Resolución del Practico 05 - Carlos Herrera



PUNTO 01.

Se crea un API_UART mediante los archivos: "API_uart.c" y "API_uart.h".

Funciones públicas:

	-bool_t uartinit();
	-void uartsendString(uint8_t * pstring);
	-void uartSendStringSize(uint8_t * pstring, uint16_t size);
	-void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

uartinit: Inicializa de acuerdo a los parámetros configurados y devuelve HAL_OK o HAL_ERROR

uartSendString: Envía una cadena de caracteres hasta el caracter especial \0 incluido

uartSendStringsize: Envía una cadena de bytes de acuerdo al valor de size.

PUNTO 02.

Utilizando el API_DEBOUNCE se implementan las funciones:

- "readKey()" verifica el flanco de bajada.
- "readKey_rise()" a fin de verificar el flanco de subida.

Se utilizan las siguientes variables para el envio de mensajes respectivos por el puerto serial:

	char *msg_asc = "Flanco Ascendente\n\r";
	char *msg_des = "Flanco Descendente\n\r";
