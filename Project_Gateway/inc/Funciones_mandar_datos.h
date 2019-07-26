//************************************************************************************************************************************************************************************************
//
//Esta función manda los recibido por Uart a la conexión TCP/IP del ESP8266, si esto no es posible guarda los datos en una SD.
// - No recibe ningún valor
//
//************************************************************************************************************************************************************************************************

void Mandar_Uart_TCP()
{
    if(espSendDataServer())uartWriteString(UART_USB, "SEND_OK");
    else uartWriteString(UART_USB, "NO SEND"); 
    
    ResetGpioBuff();
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
 
    uint32_t cantDataIn = 0;
        /*
    
        if(bandera_dato_esp == true && tickRead() - time_rx_esp_set > timeout_rx_esp) //&& bandera_dato_gpio == false)
        {
            
            cantDataIn = espCleanReceivedData(espRxIntBuffer);
            
            uartWriteString(UART_USB, "\r\nLa cantidad de datos en Buffer es: ");
            uartWriteString(UART_USB,intToString(cantDataIn));
            
            if(cantDataIn > 0)
            {
                uartWriteString(UART_USB, "\r\nEl buffer ha sido limpiado correctamente.\r\n");
            }    
            else
            {
                uartWriteString(UART_USB, "\r\nEl buffer NO ha sido limpiado correctamente.\r\n");
            }    
            uartWriteString(UART_USB, "\r\nEl dato que he recibido es: ");
            uartWriteByteArray(UART_USB, espRxIntBuffer, cantDataIn);
            uartWriteByteArray(UART_GPIO, espRxIntBuffer,cantDataIn);
            memset( espRxIntBuffer, '\0', sizeof(espRxIntBuffer) );
            bandera_dato_esp = false;
            //Reinicializamos nuevamente el puntero del buffer para que apunte a la primer dirección del mismo
            punt_rx_esp=espRxIntBuffer; 
            
        }  */
    
}
