void error_critico(void);

void error_critico(void)
{
    uartWriteString(UART_USB," _____ ____  ____   ___  ____\r\n");
    uartWriteString(UART_USB,"| ____|  _ \\|  _ \\ / _ \\|  _ \\\r\n");
    uartWriteString(UART_USB,"|  _| | |_) | |_) | | | | |_) |\r\n");
    uartWriteString(UART_USB,"| |___|  _ <|  _ <| |_| |  _ <\r\n");
    uartWriteString(UART_USB,"|_____|_| \\_\\_| \\_\\\\___/|_| \\_\\\r\n");
     
}