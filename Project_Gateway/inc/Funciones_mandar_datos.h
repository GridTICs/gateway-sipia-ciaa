//************************************************************************************************************************************************************************************************
//
//Esta función manda los recibido por Uart a la conexión TCP/IP del ESP8266, si esto no es posible guarda los datos en una SD.
// - No recibe ningún valor
//
//************************************************************************************************************************************************************************************************

void Mandar_Uart_TCP()
{
    
    if(bandera_dato_gpio == true && tickRead() - time_rx_gpio_set > timeout_rx_gpio && bandera_dato_esp == false)
    {   
        uartInterrupt(UART_232, false);
        char buffer_fp[1024];
        memset( buffer_fp, '\0', sizeof(buffer_fp) );
        char buffer_aux[1024];
        memset( buffer_aux, '\0', sizeof(buffer_aux) );
        unsigned int tam_archivo;
        //Bandera para indicar que estoy mandando el gpioRxBuffer, para que en el 
        //caso de que lleguen mas datos se guarden en el buffer secundario.
        mandar_paquete = true;
    
        if(fatFs_Open_and_GetSize("BUFF.TXT", buffer_fp) > 0 ) 
        {
            strcpy(buffer_aux,gpioRxBuffer);
            memset( gpioRxBuffer, '\0', sizeof(gpioRxBuffer) );
            strcpy(gpioRxBuffer,buffer_fp);
            strcat(gpioRxBuffer,buffer_aux);
            if(Erase_Arch("BUFF.TXT")==true)uartWriteString(UART_USB, "\r\nEl archivo ha sido borrado con éxito.\r\n");
        }
        else
        {
            uartWriteString(UART_USB,"\r\nNo se leyeron correctamente los datos, o no hay datos que leer.\r\n");
        }  
    
        if(esp01SendTPCIPDataToServer(SERVER_URL, SERVER_PORT, gpioRxBuffer, strlen(gpioRxBuffer))==true)
        {
            uartWriteString(UART_USB,"\r\nPaquete enviado con éxito...\r\n");
            memset( gpioRxBuffer, '\0', sizeof(gpioRxBuffer) );
            punt_rx_gpio = 0;
        }
        else
        {
            uartWriteString(UART_USB,"\r\nPaquete NO enviado con éxito...\r\n");
            uartWriteString(UART_USB,"...Se guarda en memoria SD...\r\n");
        
            //Guardo el contenido de gpioRxBuffer en "BUFF.TXT de la tarjeta SD"
            if(fatFs_Add_Buff(gpioRxBuffer))
            {
                memset( gpioRxBuffer, '\0', sizeof(gpioRxBuffer) );
                punt_rx_gpio = 0;
                fatFs_Add_Log(sdcardDriveName(), "No hay conexión TCP con el servidor, se guarda el paquete en la SD.");
            }
            else
            {
                uartWriteString(UART_USB,"\r\nPaquete no se ha guardado correctamente en la SD...\r\n"); 
                fatFs_Add_Log(sdcardDriveName(), "No hay conexión TCP con el servidor, NO se guarda el contenido del buffer en la SD ERROR.");   
            }
        
        }
    
        mandar_paquete = false;
        bandera_dato_gpio = false;
        uartInterrupt(UART_232, true);
    }
}

//************************************************************************************************************************************************************************************************
//
//Esta función manda los recibido por TCP/IP al Uart del Gpio
// - No recibe ningún valor
// - Utiliza todas variables globales:
//        1 - bandera_dato_esp  es la bandera que nos indica que ha llegado un dato por TCP/IP
//        2 - time_rx_esp_set   cada vez que llega un nuevo dato se lee el tickRead() y se guarda en esta variable
//        3 - timeout_rx_esp    es un tiempo fijo, si el tiempo entre el último dato recibido (time_rx_esp_set) y el actual es mayor a timeout_rx_esp es condición para mandar el paquete
//        4 - espRxIntBuffer    es el buffer de recepción del ESP8266
//        5 - punt_rx_esp       es la cantidad de datos que han llegado, cada vez que llega un dato se incrementa esta variable
//
//************************************************************************************************************************************************************************************************

void Mandar_Uart_Gpio()
{
 
        if(bandera_dato_esp == true && tickRead() - time_rx_esp_set > timeout_rx_esp )
        {
            uartWriteString(UART_USB, "\r\nLa cantidad de datos en Buffer es: ");
            uartWriteString(UART_USB,intToString(strlen(espRxIntBuffer)));
            
            if(espCleanReceivedData(espRxIntBuffer))
            {
                uartWriteString(UART_USB, "\r\nEl buffer ha sido limpiado correctamente.\r\n");
            }    
            else
            {
                uartWriteString(UART_USB, "\r\nEl buffer NO ha sido limpiado correctamente.\r\n");
            }    
            uartWriteString(UART_USB, "\r\nEl dato que he recibido es: ");
            uartWriteString(UART_USB, espRxIntBuffer);
            uartWriteString(UART_GPIO, espRxIntBuffer);
            memset( espRxIntBuffer, '\0', sizeof(espRxIntBuffer) );
            bandera_dato_esp = false;
            punt_rx_esp=0; 
        }  
    
}
