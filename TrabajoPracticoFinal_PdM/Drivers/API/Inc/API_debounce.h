#include <stdbool.h>
#include <stdint.h>




typedef bool bool_t;

void debounceFSM_init();		// debe cargar el estado inicial
void debounceFSM_update();	// debe leer las entradas, resolver la lógica de
bool_t readKey();
bool_t readKey_rise();


