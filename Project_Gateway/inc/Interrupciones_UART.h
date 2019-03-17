//************************   Esta función es la interrupción de recepción que viene por GPIO   ***************************//

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

uint8_t espRxIntBuffer[UART_MOTE_RX_BUFF_SIZE];
unsigned int punt_rx_esp;
bool_t bandera_dato_esp;

const unsigned int timeout_rx_esp = 5000;
unsigned int time_rx_esp_set;

void INT_ESP_RX()
{
    uint8_t d = uartRxRead(UART_232);
    espRxIntBuffer[punt_rx_esp]=d;
    punt_rx_esp++;
    if(bandera_dato_gpio != true && strlen(espRxIntBuffer)>1)bandera_dato_esp = true;
    time_rx_esp_set = tickRead();
}