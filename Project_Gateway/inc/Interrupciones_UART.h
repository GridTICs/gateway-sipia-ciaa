//************************   Esta función es la interrupción de recepción que viene por GPIO   ***************************//

// MOTE Rx Buffer
char gpioRxBuffer[ UART_MOTE_RX_BUFF_SIZE ];
char gpioRxBuffer_aux[ UART_MOTE_RX_BUFF_SIZE ];
unsigned int punt_rx_gpio;
unsigned int punt_rx_gpio_aux;
bool_t mandar_paquete;
bool_t bandera_dato_gpio = false;
const unsigned int timeout_rx_gpio = 5000;
unsigned int time_rx_gpio_set;

void UART_GPIO_INT()
{
    char c = uartRxRead(UART_GPIO);
    if(mandar_paquete == false)
    {   
        //Incorporamos el Buffer auxiliar al buffer de recepción para que toda la información guardada
        //pase al Buffer general "primario" y así no perder la información que llegó.
        strcat(gpioRxBuffer, gpioRxBuffer_aux);
        memset( gpioRxBuffer_aux, '\0', sizeof(gpioRxBuffer_aux) );
        
        gpioRxBuffer[punt_rx_gpio]=c;
        punt_rx_gpio++;
    }
    else
    {    
        //Este buffer auxiliar sirve para guardar la información cuando estoy enviando el buffer
        //real.
        gpioRxBuffer_aux[punt_rx_gpio_aux]=c;
        punt_rx_gpio_aux++;
    }

    bandera_dato_gpio = true;
    time_rx_gpio_set = tickRead();
        
}

//**************************************************************************************************************************//
/* La forma del paquete recibido del ESP8266 es:    */
/* +IPD,<len>:<data>                                */

uint8_t espRxIntBuffer[UART_MOTE_RX_BUFF_SIZE];
unsigned int punt_rx_esp;
bool_t bandera_dato_esp;

const unsigned int timeout_rx_esp = 5000;
unsigned int time_rx_esp_set;

void Int_esp_Rx()
{
    uint8_t d = uartRxRead(UART_232);
    //uartWriteByte(UART_USB, d);
    espRxIntBuffer[punt_rx_esp]=d;
    punt_rx_esp++;
    if(bandera_dato_gpio != true && strlen(espRxIntBuffer)>1)bandera_dato_esp = true;
    time_rx_esp_set = tickRead();
}