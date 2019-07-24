//************************   Esta función es la interrupción de recepción que viene por GPIO   ***************************//

// MOTE Rx Buffer
uint8_t gpioRxBuffer[ UART_MOTE_RX_BUFF_SIZE ];
uint8_t *punt_rx_gpio;
uint32_t gpioBuff_cant;

bool_t bandera_dato_gpio = false;
const unsigned int timeout_rx_gpio = 1000;
unsigned int time_rx_gpio_set;


void ResetGpioBuff()
{
    memset( gpioRxBuffer, '\0', sizeof(gpioRxBuffer) );
    punt_rx_gpio = gpioRxBuffer;
    gpioBuff_cant = 0;
    
}

void INT_GPIO_RX()
{
    *punt_rx_gpio = uartRxRead(UART_GPIO);
    punt_rx_gpio++;
    gpioBuff_cant++;
    bandera_dato_gpio = true;
    time_rx_gpio_set = tickRead();
        
}

//**************************************************************************************************************************//
/* La forma del paquete recibido del ESP8266 es:    */
/* +IPD,<len>:<data>                                */

uint8_t espRxIntBuffer[UART_MOTE_RX_BUFF_SIZE];
uint8_t *punt_rx_esp;
bool_t bandera_dato_esp;

const unsigned int timeout_rx_esp = 5000;
unsigned int time_rx_esp_set;


void INT_ESP_RX()
{
        *punt_rx_esp = uartRxRead(UART_232);
        punt_rx_esp++;
        bandera_dato_esp = true;
        time_rx_esp_set = tickRead();

}