//************************************************************************************************************************************************************************************************
//
//Esta funci�n manda los recibido por Uart a la conexi�n TCP/IP del ESP8266, si esto no es posible guarda los datos en una SD.
// - No recibe ning�n valor
//
//************************************************************************************************************************************************************************************************

void Mandar_Uart_TCP()
{
    
    if(bandera_dato_gpio == true && (tickRead() - time_rx_gpio_set) > timeout_rx_gpio)
    {   
        //uartInterrupt(UART_232, false);
        
        char buffer_fp[UART_MOTE_RX_BUFF_SIZE];
        memset( buffer_fp, '\0', sizeof(buffer_fp) );
        char buffer_aux[UART_MOTE_RX_BUFF_SIZE];
        memset( buffer_aux, '\0', sizeof(buffer_aux) );
        unsigned int tam_archivo;
        //Bandera para indicar que estoy mandando el gpioRxBuffer, para que en el 
        //caso de que lleguen mas datos se guarden en el buffer secundario.

    
        if(fatFs_Open_and_GetSize("BUFF.TXT", buffer_fp) > 0 ) 
        {
            strcpy(buffer_aux,gpioRxBuffer);
            memset( gpioRxBuffer, '\0', sizeof(gpioRxBuffer) );
            strcpy(gpioRxBuffer,buffer_fp);
            strcat(gpioRxBuffer,buffer_aux);
            if(Erase_Arch("BUFF.TXT")==true)uartWriteString(UART_USB, "\r\nEl archivo ha sido borrado con �xito.\r\n");
        }
        else
        {
            uartWriteString(UART_USB,"\r\nNo hay datos que leer.\r\n");
        }  
    
        if(esp01SendTPCIPDataToServer(servidor_tcpip, atoi(puerto_tcpip), gpioRxBuffer, gpioBuff_cant)==true)
        {
            uartWriteString(UART_USB,"\r\nPaquete enviado con �xito...\r\n");
            ResetGpioBuff();
        }
        else
        {
            uartWriteString(UART_USB,"\r\nPaquete NO enviado con �xito...\r\n");
            uartWriteString(UART_USB,"...Se guarda en memoria SD...\r\n");
        
            //Guardo el contenido de gpioRxBuffer en "BUFF.TXT de la tarjeta SD"
            if(fatFs_Add_Buff(gpioRxBuffer))
            {
                ResetGpioBuff();
                fatFs_Add_Log(sdcardDriveName(), "No hay conexi�n TCP con el servidor, se guarda el paquete en la SD.");
            }
            else
            {
                uartWriteString(UART_USB,"\r\nPaquete no se ha guardado correctamente en la SD...\r\n...SE PIERDEN DATOS...\r\n"); 
                fatFs_Add_Log(sdcardDriveName(), "No hay conexi�n TCP con el servidor, NO se guarda el contenido del buffer en la SD ERROR."); 
                LCD_Estado(ERROR_SD);
                stopProgramError();  
            }
        
        }
        
        bandera_dato_gpio = false;
                
        //uartInterrupt(UART_232, true);
    }
}

//************************************************************************************************************************************************************************************************
//
//Esta funci�n manda los recibido por TCP/IP al Uart del Gpio
// - No recibe ning�n valor
// - Utiliza todas variables globales:
//        1 - bandera_dato_esp  es la bandera que nos indica que ha llegado un dato por TCP/IP
//        2 - time_rx_esp_set   cada vez que llega un nuevo dato se lee el tickRead() y se guarda en esta variable
//        3 - timeout_rx_esp    es un tiempo fijo, si el tiempo entre el �ltimo dato recibido (time_rx_esp_set) y el actual es mayor a timeout_rx_esp es condici�n para mandar el paquete
//        4 - espRxIntBuffer    es el buffer de recepci�n del ESP8266
//        5 - punt_rx_esp       es la cantidad de datos que han llegado, cada vez que llega un dato se incrementa esta variable
//
//************************************************************************************************************************************************************************************************

void Mandar_Uart_Gpio()
{
 
        if(bandera_dato_esp == true && tickRead() - time_rx_esp_set > timeout_rx_esp) //&& bandera_dato_gpio == false)
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
            //Reinicializamos nuevamente el puntero del buffer para que apunte a la primer direcci�n del mismo
            punt_rx_esp=espRxIntBuffer; 
        }  
    
}
