void startMenu(void);
void mainMenu(void);
void menuConfigWiFi(void);
void menuConfigServer(void);
void menuConfigNTP(void);
void finalizarMenuConfig(void);

void startMenu(void)
{
    uint8_t recvDate;
    
    gpioWrite( LEDB, ON );
    gpioWrite( LEDG, OFF );
    
    while(usbStatus != UART_USB_EXIT)
    {    
    
        switch(usbStatus)
        {
            case UART_USB_CLEAR:
            
                if(usbStatus == UART_USB_CLEAR)
                {
                    mainMenu(); 
                }
            
            break;
        
            case UART_MENU_PPAL:
            
            
                if(uartReadByte(UART_USB, &recvDate) == true)
                {    
            
                    if(recvDate > 48 && recvDate < 52)
                    {
                        //Si elijo opción 1
                        if(recvDate == 49)
                        {
                            menuConfigWiFi();
                        }
                
                        //Si elijo opción 2
                        if(recvDate == 50)
                        {
                            menuConfigServer();
                        }    
                    
                        //Si elijo opción 3
                        if(recvDate == 51)
                        {
                            menuConfigNTP();
                        }    
                    }
                    
                    if(recvDate == 52)
                    {
                        usbStatus = UART_USB_EXIT;
                    }
      
                }  
                
            break;
        }
    }
    
    usbStatus = UART_USB_CLEAR;
    boton_pulsado = 2;
    
    uartWriteString(UART_USB, "\r\nSali del Menu\r\n");
    
}



void mainMenu(void)
{
    
    uartInterrupt(UART_USB, true);
    uartInterrupt(UART_GPIO, false);
    uartInterrupt(UART_232, false);
    uartWriteString(UART_USB, "\r\n¡¡¡ATENCIÓN!!!\r\n");
    uartWriteString(UART_USB, "\r\nTENGA EN CUENTA QUE SE HAN DESACTIVADO LAS INTERRUPCIONES,\r\n");
    uartWriteString(UART_USB, "LOS DATOS RECIBIDOS SE HABRÁN PERDIDO.\r\n\r\n");
    uartWriteString(UART_USB, "---------------------------------------------\r\n");
    uartWriteString(UART_USB, "                MENU PRINCIPAL               \r\n");
    uartWriteString(UART_USB, "---------------------------------------------\r\n");
    uartWriteString(UART_USB, "Seleccione una de las siguientes opciones:   \r\n");
    uartWriteString(UART_USB, "         1- Configurar WiFi                  \r\n");
    uartWriteString(UART_USB, "         2- Configurar Server                \r\n");
    uartWriteString(UART_USB, "         3- Configurar Server NTP            \r\n");
    uartWriteString(UART_USB, "         4- Salir del Menu                   \r\n");
    //Le aviso a la interrupción que estoy en el Menu PPAL.
    usbStatus = UART_MENU_PPAL;
    
}

void menuConfigWiFi(void)
{
    char bufferRxSSID[50];
    char *ptrBuff;
    ptrBuff = bufferRxSSID;
    
    char bufferRxClave[50];
    char *ptrBuffClave;
    ptrBuffClave = bufferRxClave;

    uartWriteString(UART_USB, "\r\n\r\n---------------------------------------------\r\n");
    uartWriteString(UART_USB, "               CONFIGURAR WIFI               \r\n");
    uartWriteString(UART_USB, "---------------------------------------------\r\n");
    uartWriteString(UART_USB, "Por favor ingrese el nombre de la red WiFi (SSID):\r\n");
    while(uartRxReady(UART_USB) == false);

    while(uartReadByte(UART_USB, ptrBuff) == true)
    {   
        //Delay necesario para que el uart se pueda leer como corresponde, sino tira error
        delay(10);
        ptrBuff++;
    }
    *ptrBuff = '\0';
    uartWriteString(UART_USB, bufferRxSSID);
    
    uartWriteString(UART_USB, "\r\nPor favor ingrese el nombre de la Clave WiFi:\r\n");
    while(uartRxReady(UART_USB) == false);

    while(uartReadByte(UART_USB, ptrBuffClave) == true)
    {   
        //Delay necesario para que el uart se pueda leer como corresponde, sino tira error
        delay(10);
        ptrBuffClave++;
    }
    *ptrBuffClave = '\0';
    uartWriteString(UART_USB, bufferRxClave);
    
    //Falta Asignar lo leído a las variables que corresponden y modificarlos en la SD
    
    mainMenu();
    
}

void menuConfigServer(void)
{

    uartWriteString(UART_USB, "\r\n\r\n---------------------------------------------\r\n");
    uartWriteString(UART_USB, "               CONFIGURAR SERVER               \r\n");
    uartWriteString(UART_USB, "---------------------------------------------\r\n");
    while(1);
}

void menuConfigNTP(void)
{

    uartWriteString(UART_USB, "\r\n\r\n---------------------------------------------\r\n");
    uartWriteString(UART_USB, "               CONFIGURAR SERVER NTP               \r\n");
    uartWriteString(UART_USB, "---------------------------------------------\r\n");
    while(1);
}