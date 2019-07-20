//************************   Esta función es la interrupción de recepción que viene por GPIO   ***************************//

// MOTE Rx Buffer
uint8_t gpioRxBuffer[ UART_MOTE_RX_BUFF_SIZE ];
uint8_t *punt_rx_gpio;
uint32_t gpioBuff_cant;

bool_t bandera_dato_gpio = false;
const unsigned int timeout_rx_gpio = 3000;
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

char espRxIntBuffer[UART_MOTE_RX_BUFF_SIZE];
char *punt_rx_esp;
bool_t bandera_dato_esp;

const unsigned int timeout_rx_esp = 5000;
unsigned int time_rx_esp_set;

//Únicamente utilizado para las funciones del Server NTP
//Se realiza en un buffer aparte para no tener errores en lo anterior
// ------- EN UN FUTURO SE PUEDE LLEGAR A OPTIMIZAR SIN NECESIDAD DE VARIABLES NUEVAS ----- //

bool_t bandera_NTP = false;

void INT_ESP_RX()
{
    //Solo cuando se hace una petición al Server NTP se activa esta bandera
    /*if(bandera_NTP)
    {    
        *punt_ntp = uartRxRead(UART_232);
        punt_ntp++;
    }
    else
    { */
        *punt_rx_esp = uartRxRead(UART_232);
        punt_rx_esp++;
        //Solo activamos la bandera si NO se está mandando ningún dato por TCP/IP
        //y si el buffer tiene más de un dato 
        // ---- TENER CUIDADO, ESTO ÚLTIMO PUEDE SER UN PROBLEMA ----
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
    //}
}