//************************   Esta funci�n es la interrupci�n de recepci�n que viene por GPIO   ***************************//

// MOTE Rx Buffer
char gpioRxBuffer[ UART_MOTE_RX_BUFF_SIZE ];
char gpioRxBuffer_aux[ UART_MOTE_RX_BUFF_SIZE ];
char *punt_rx_gpio;

unsigned int punt_rx_gpio_aux;
bool_t mandar_paquete;
bool_t bandera_dato_gpio = false;
const unsigned int timeout_rx_gpio = 5000;
unsigned int time_rx_gpio_set;

void INT_GPIO_RX()
{
    *punt_rx_gpio = uartRxRead(UART_GPIO);
    punt_rx_gpio++;

    bandera_dato_gpio = true;
    time_rx_gpio_set = tickRead();
        
}

//**************************************************************************************************************************//
/* La forma del paquete recibido del ESP8266 es:    */
/* +IPD,<len>:<data>                                */

char espRxIntBuffer[UART_MOTE_RX_BUFF_SIZE];
char *punt_rx_esp;
bool_t bandera_dato_esp;

const unsigned int timeout_rx_esp = 5000;
unsigned int time_rx_esp_set;

void INT_ESP_RX()
{
    
        *punt_rx_esp = uartRxRead(UART_232);
        punt_rx_esp++;
        uartWriteByte(UART_USB, *punt_rx_esp);
        //Solo activamos la bandera si NO se est� mandando ning�n dato por TCP/IP
        //y si el buffer tiene m�s de un dato 
        // ---- TENER CUIDADO, ESTO �LTIMO PUEDE SER UN PROBLEMA ----
        if(espRxIntBuffer[0]=='+')
        {
            bandera_dato_esp = true;
            time_rx_esp_set = tickRead();
        }
        else
        {
            memset( espRxIntBuffer, '\0', sizeof(espRxIntBuffer) );
            punt_rx_esp = espRxIntBuffer;
        }    
}