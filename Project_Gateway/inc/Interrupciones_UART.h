//************************   Esta función es la interrupción de recepción que viene por GPIO   ***************************//
enum ESTADOS_INT {
  ESTADO_INICIAL = 0,
  RECIBIENDO_DATO,
  BUSCANDO_LONG,
  ENVIANDO_TRAMA  
}; 


// MOTE Rx Buffer
uint8_t gpioRxBuffer[ UART_MOTE_RX_BUFF_SIZE ];
//Puntero al buffer
uint8_t *punt_rx_gpio;

//Variables para la máquina de estados
uint8_t estadoInt = 0;
uint16_t cantDatos;
uint16_t cuentaDatos;

void ResetGpioBuff()
{
    memset( gpioRxBuffer, '\0', sizeof(gpioRxBuffer));
    punt_rx_gpio = gpioRxBuffer;
    cantDatos = 0;
    cuentaDatos = 1;
    estadoInt = ESTADO_INICIAL;
}


//Funcion de Interrupción del MOTE, cada vez que llega un dato Ingresa Aquí.
void INT_GPIO_RX()
{
    *punt_rx_gpio = uartRxRead(UART_GPIO);
    uartWriteByte(UART_USB, *punt_rx_gpio);

    switch(estadoInt)
    {
        case ESTADO_INICIAL:
            if(*punt_rx_gpio == 0x7E)estadoInt = BUSCANDO_LONG;
            else   ResetGpioBuff();  
        break;
    
        case BUSCANDO_LONG:
            cantDatos = *punt_rx_gpio;
            estadoInt = RECIBIENDO_DATO;
        break; 
        
        case RECIBIENDO_DATO:
            cuentaDatos++;
            if(cuentaDatos == (cantDatos))estadoInt = ENVIANDO_TRAMA;
        break;
        
        case ENVIANDO_TRAMA:
            uartWriteByteArray(UART_USB, gpioRxBuffer , cantDatos+2);
            ResetGpioBuff();
        break;
     
    }   
    
    //Solo aumentamos el puntero si no estoy en ESTADO_INICIAL
    if(estadoInt != ESTADO_INICIAL)punt_rx_gpio++;
    
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

//Interrupcion TIMER

void myIntTick()
{
     uartWriteString(UART_USB, "\r\nEstoy en la interrupcion de TICK.\r\n");   
}