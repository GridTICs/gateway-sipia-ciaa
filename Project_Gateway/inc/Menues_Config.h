void mainMenu(void);
void menuConfigWiFi(void);
void menuConfigServer(void);
void menuConfigNTP(void);


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