#include "sapi.h"

void onRx( void *noUsado )
{
   char c = uartRxRead( UART_232 );
   uartWriteByte(UART_USB, c);
   //uartWriteString(UART_USB," ...OK...\r\n");
}

int main(void)
{
   /* Inicializar la placa */
   boardConfig();

   /* Inicializar la UART_USB junto con las interrupciones de Tx y Rx */
   uartConfig(UART_USB, 115200);   
   uartConfig(UART_232, 115200);   
   // Seteo un callback al evento de recepcion y habilito su interrupcion
   uartCallbackSet(UART_232, UART_RECEIVE, onRx, NULL);
   // Habilito todas las interrupciones de UART_USB
   uartInterrupt(UART_232, true);
    
   while(TRUE) {
      // Una tarea muy bloqueante para demostrar que la interrupcion funcina
      gpioToggle(LEDB);
      delay(5000);
      uartWriteString(UART_USB,"...Keep I Live...\r\n");  
   }
   return 0;
}
