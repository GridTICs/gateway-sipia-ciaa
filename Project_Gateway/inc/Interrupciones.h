bool_t esp01ConnectToServer( char*, uint32_t);
void showDateAndTimeLCD( rtc_t *);


//************************   Esta función es la interrupción de recepción que viene por GPIO (MOTE)  ***************************//
//Esta variables es para mostrar los estados en el LCD con interrupcion por tiempo.
uint8_t lcdStatus = EST_OK;


enum ESTADOS_INT_MOTE {
  MOTE_ESTADO_INICIAL = 0,
  MOTE_RECIBIENDO_DATO,
  MOTE_BUSCANDO_LONG,
  MOTE_ENVIANDO_TRAMA  
}; 


// MOTE Rx Buffer
uint8_t gpioRxBuffer[ UART_MOTE_RX_BUFF_SIZE ];
//Puntero al buffer
uint8_t *punt_rx_gpio;

uint8_t estadoInt = 0;
uint16_t cantDatos;
uint16_t cuentaDatos;

bool_t bandera_mandar_datos = 0;

void ResetGpioBuff()
{
    memset( gpioRxBuffer, '\0', sizeof(gpioRxBuffer));
    punt_rx_gpio = gpioRxBuffer;
    cantDatos = 0;
    cuentaDatos = 1;
    bandera_mandar_datos = false;
    estadoInt = MOTE_ESTADO_INICIAL;
}


//Funcion de Interrupción del MOTE, cada vez que llega un dato Ingresa Aquí.
void INT_GPIO_RX()
{
    *punt_rx_gpio = uartRxRead(UART_GPIO);
    uartWriteByte(UART_USB, *punt_rx_gpio);

    switch(estadoInt)
    {
        case MOTE_ESTADO_INICIAL:
            if(*punt_rx_gpio == 0x7E)estadoInt = MOTE_BUSCANDO_LONG;
            else   ResetGpioBuff();  
        break;
    
        case MOTE_BUSCANDO_LONG:
            cantDatos = *punt_rx_gpio;
            estadoInt = MOTE_RECIBIENDO_DATO;
        break; 
        
        case MOTE_RECIBIENDO_DATO:
            cuentaDatos++;
            if(cuentaDatos == (cantDatos))estadoInt = MOTE_ENVIANDO_TRAMA;
        break;
        
        case MOTE_ENVIANDO_TRAMA:
            bandera_mandar_datos = true;
        break;
     
    }   
    
    //Solo aumentamos el puntero si no estoy en ESTADO_INICIAL
    if(estadoInt != MOTE_ESTADO_INICIAL)punt_rx_gpio++;
    
}

//**************************************************************************************************************************//
/* La forma del paquete recibido del ESP8266 es:    */
/* +IPD,<len>:<data>                                */

//Buffer y puntero al Buffer de la int del ESP8266
uint8_t espRxIntBuffer[UART_MOTE_RX_BUFF_SIZE];
uint8_t *punt_rx_esp;

//Variables para la máquina de estados del CAMINO UART(MOTE) -> SERVER
enum ESTADOS_INT_ESP {
  ESP_RECIBIENDO_DATO_SERVER = 0,
  ESP_MANDAR_DATO_TCP  
}; 

enum ESTADOS_AT_COMM{
    AT_EST_INICIAL = 0,
    AT_MANDAR_COMM,
    AT_WAIT_CONNECT,
    AT_SEND_COMM,
    AT_WAIT_READY_FOR_SEND,
    AT_SEND_DATA,
    AT_WAIT_SEND_OK,
    AT_SEND_OK
};

uint8_t estadoIntEsp = 0;
uint8_t estadoATComm = 0;

//Variables para la máquina de estados del CAMINO SERVER -> UART(MOTE)
enum {
    IPD_INIT = 0,
    IPD_RCV_DATA_LENGH,
    IPD_RCV_DATA,
    IPD_SEND_DATA_OK,
};


uint8_t estadoIntIPD = 0;
uint8_t IPD_Rcv[5]= {0x2B,0x49,0x50,0x44,0x2C};
uint8_t aciertos = 0;
uint8_t length_IPD_Str[4];
uint8_t contIPDStr = 0;
uint16_t cantDataIPD = 0;
uint32_t cantDatosGuard; 


void ResetESPBuff()
{
    memset( espRxIntBuffer, '\0', sizeof(espRxIntBuffer));
    punt_rx_esp = espRxIntBuffer;
}

void ResetIPD()
{
    memset( espRxIntBuffer, '\0', sizeof(espRxIntBuffer));
    punt_rx_esp = espRxIntBuffer;
    memset( length_IPD_Str, '\0', sizeof(length_IPD_Str));
    aciertos = 0;
    contIPDStr = 0;
    cantDataIPD = 0;
    cantDatosGuard = 0;
    estadoIntIPD = IPD_INIT;
}


void INT_ESP_RX()
{
    *punt_rx_esp = uartRxRead(UART_232);
       
    switch(estadoIntEsp)
    {
        case  ESP_RECIBIENDO_DATO_SERVER:
        
            switch(estadoIntIPD)
            {
                    case IPD_INIT:
                        
                        if(*punt_rx_esp == IPD_Rcv[aciertos])
                        {    
                            aciertos++;
                        }    
                        else aciertos = 0;
                        
                        if(aciertos == 5)estadoIntIPD = IPD_RCV_DATA_LENGH;
                            
                    break;    
                        
                    case IPD_RCV_DATA_LENGH:
                    
                        if(*punt_rx_esp == 0x3A)
                        {
                            cantDataIPD = atoi(length_IPD_Str);
                            estadoIntIPD = IPD_RCV_DATA;
                        }
                        else
                        {
                            length_IPD_Str[contIPDStr] = *punt_rx_esp;
                            contIPDStr++;
                        }    
                        
                    break;
                    
                    case IPD_RCV_DATA:
                        
                        if(cantDatosGuard > cantDataIPD-1)
                        {
                            estadoIntIPD = IPD_SEND_DATA_OK;
                        }    
                        else
                        {
                            //DEBEMOS CAMBIAR UART_USB por UART_GPIO cuando deseemos que el dato llegue al MOTE (SERVER -> MOTE)
                            uartWriteByte(UART_USB,*punt_rx_esp);
                            cantDatosGuard++;
                        }
                    
                    break;
                        
                    case IPD_SEND_DATA_OK:
                        ResetIPD();
                    break;    
            }
        
        break;
        
        case ESP_MANDAR_DATO_TCP:
             
        break;
        
    }
    
    punt_rx_esp++;

}

//INTERRUPCION DE RECEPCIÓN DEL UART DE LA CONSOLA SERIE
enum {
    UART_USB_CLEAR = 0,
    UART_MENU_PPAL,
    UART_USB_EXIT,
    
    
};

//Buffer y puntero al Buffer de la int del ESP8266
uint8_t usbRxIntBuffer[UART_MOTE_RX_BUFF_SIZE];
uint8_t *punt_rx_usb;
uint8_t usbStatus = 0;

void ResetUSB()
{
    memset(usbRxIntBuffer,'\0',sizeof(usbRxIntBuffer));
    punt_rx_usb = usbRxIntBuffer;
}


void USB_INT_RX()
{
    *punt_rx_usb = uartRxRead(UART_USB);
    uartWriteByte(UART_USB,*punt_rx_usb);
    
    switch(usbStatus)
    {
        case UART_MENU_PPAL:
            
            if(*punt_rx_usb > 48 && *punt_rx_usb < 52)
            {    
                switch(*punt_rx_usb)
                {
                    //Quiero configurar el WiFi - Opción 1
                    case 49:
                        uartWriteString(UART_USB,"\r\nEstoy en el menú 1.");
                        while(1);
                    break;
                    //Quiero configurar el Server - Opción 2
                    case 50:
                        uartWriteString(UART_USB,"\r\nEstoy en el menú 2.");
                        while(1);
                    break;
                    //Quiero configurar el Server NTP - Opción 3
                    case 51:
                        uartWriteString(UART_USB,"\r\nEstoy en el menú 3.");
                        while(1);
                    break;
                    
                }
            }
            else
            {    
                if(*punt_rx_usb == 52)
                {    
                    usbStatus = UART_USB_EXIT;    
                }
                else
                {
                    ResetUSB();
                }
            }
            
        break;
            
        case UART_USB_EXIT:
            uartWriteString(UART_USB, "\r\nQuise salir del Menú Ppal.");
        break;
        
    }
    
    punt_rx_usb++;
    
}




//Interrupcion TIMER
enum BOTTON_STATUS{
        BOT_WAIT = 0,
        BOT_EJEC,
};

uint8_t statusServer = 0;
uint8_t boton_pulsado = 2;
uint8_t botStatus = 0;
rtc_t rtc_lcd;

void myIntTick()
{   
    //Esta interrupción se ejecuta cada TIEMPO_INT_TIMER micro segundos
    //Se va a utilizar para:
    //      1- Refrescar los estados en el LCD.
    //      2- Saber que boton de la EDU-CIAA se apretó.
    //      3- Para indicarle al Main la acción a realizar.
    
    
    //Qué botón se apretó?
    if(gpioRead(TEC1)== FALSE)boton_pulsado = 1;
    if(gpioRead(TEC2)== FALSE)boton_pulsado = 2;
    if(gpioRead(TEC3)== FALSE)boton_pulsado = 3;
    botStatus = BOT_EJEC;
    
    
}