/*

PROYECTO FINAL DE INGENIERÍA ELECTRÓNICA
UNIVERSIDAD TECNOLÓGICA NACIONAL
FACULTAD REGIONAL MENDOZA
Autor: Lucas Escribano - Rodrigo Gonzalez
Año: 2014

*/

// ************************** INCLUDES *************************************** //
#include "sapi.h"
#include <string.h>


//Inclusiones propias
#include "ESP8622_driver.h"         //Driver de la placa de WiFi
#include "RTC_Config.h"             //Funciones de el Real Time Counter
#include "FAT_SD.h"                 //Funciones de la SD
#include "Interrupciones_UART.h"    //Funciones de las interrupciones de todos los UART's
#include "NTP_Config.h"             //Funciones de las conexiones con el Server NTP

// ************************ DECLARACIONES ************************************ //


// *********************** VARIABLES GLOBALES ******************************** //


// *************************** FUNCTIONS ************************************* //

#include "Funciones_mandar_datos.h" //Funciones para Recibir y Transmitir datos

// ***************************** MAIN **************************************** //

int main(void)
{
    /* Inicializar la placa */
    boardConfig();
    /* Inicializar la UART_USB junto con las interrupciones de Tx y Rx */
    uartConfig(UART_USB, 115200);   
    uartConfig(UART_ESP01, 115200);
    uartConfig(UART_GPIO, 115200);
    
 
    uartWriteString(UART_USB, "\r\nLa EDU-CIAA ha sido iniciada correctamente,\r\ny los UART han sido configurados correctamente.\r\n");
    uartWriteString(UART_USB, "\r\n...Ahora se configurará el Real Time Counter (RTC)...\r\n");
    
    //Esta función inicia el RTC, y le pone una fecha y hora establecidos
    //RTC_Init();
    
     uartWriteString(UART_USB, "\r\n...Iniciando puerto SPI..\r\n");
   //Primero iniciamos el SPI
   if(spiConfig( SPI0 ))uartWriteString(UART_USB, "...El puerto SPI ha sido iniciado con éxtio!!!..\r\n");;
   
   
   uartWriteString(UART_USB, "\r\n...Iniciando SD..\r\n");
   
   //Ahora si iniciamos la SD
    if (sdcardInit( &sdcard ) == false)
    {
        uartWriteString( UART_USB, "Inicio de sdcard FALLO.\r\n**FIN**\r\n" );
        while( 1 );
    }
    else {
        uartWriteString( UART_USB, "Inicio de sdcard OK! Unidad FatFs '" );
        uartWriteString( UART_USB, sdcardDriveName());
        uartWriteString( UART_USB, "'.\r\n" );
    }
   
    mostrarEstadoTarjetaSD();
    
    if(fatFs_Open_or_Create(sdcardDriveName(), "BUFF.TXT")) uartWriteString( UART_USB, "Inicio o creación del archivo BUFF.TXT corrrecto.\r\n" );
    if(fatFs_Open_or_Create(sdcardDriveName(), "LOG.TXT"))uartWriteString( UART_USB, "Inicio o creación del archivo LOG.TXT corrrecto.\r\n" );
    if(fatFs_Open_or_Create(sdcardDriveName(), "CONFIG.TXT"))uartWriteString( UART_USB, "Inicio o creación del archivo CONFIG.TXT corrrecto.\r\n" );
    
    
      
    uartWriteString(UART_USB, "\r\nAhora se configurará el ESP8266:\r\n");
    
    if( !esp01Init( UART_ESP01, UART_DEBUG, UARTS_BAUD_RATE ) ){
      stopProgramError(); // Como dio falso (error) me quedo en un bucle infinito
   }

    uartWriteString(UART_USB, "\r\n...ESP8266 iniciado correctamente...\r\n");
   
    esp8266_mode();

    esp8266_mux();
   
   
    uartWriteString(UART_USB, "\r\n\r\nAhora el ESP8266 se conectará a la red preferida:\r\n");

   if( !esp01ConnectToWifiAP( WIFI_SSID, WIFI_PASSWORD ) ){
      stopProgramError(); // Como dio falso (error) me quedo en un bucle infinito
   }
    
    uartWriteString(UART_USB, "\r\n...ESP8266 conectado a red correctamente...\r\n");
   
  
    esp01DisconnectToServer_UDP();
    
    
    fatFs_Add_Log(sdcardDriveName(), "La EDU-CIAA es reiniciada por causas desconocidas."); 
    
    bandera_dato_esp = false;
    
    //uartCallbackSet(UART_232, UART_RECEIVE, Int_esp_Rx, NULL);
    //Debería realizar la conexión con el Servidor NTP y traer la Fecha y Hora
    // ***************   No funciona  *****************//
    //NTP_conection();
    
    
    uartWriteString(UART_USB, "\r\nActivando las interrupciones del GPIO...\r\n");
    //Activo las interrupciones del UART_GPIO para que guarde las variables que llegan...
    uartCallbackSet(UART_GPIO, UART_RECEIVE, UART_GPIO_INT, NULL);
    uartInterrupt(UART_GPIO, true);
    
    uartCallbackSet(UART_232, UART_RECEIVE, Int_esp_Rx, NULL);
    uartInterrupt(UART_232, true);
    
    //mandar_paquete = false;
    uartWriteString(UART_USB, "\r\n...Interrupciones activadas con éxito...\r\n");
    
    // Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x2 pixeles
    lcdInit( 16, 2, 5, 8 );
    lcdClear(); // Borrar la pantalla
    lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1
    lcdSendStringRaw( "Proyecto Final");
    lcdGoToXY( 1, 2 ); // Poner cursor en 1, 1
    lcdSendStringRaw( "UTN FRM");
    
    delay(5000);
    
    //Variables para mostrar el tiempo
    char dateandtime[30];
    unsigned int tiempo_set_lcd = tickRead();
    const unsigned int timeout_lcd = 5000;
    rtc_t rtc_lcd;
    
    while(1)
    {        

        Mandar_Uart_TCP();
        
        Mandar_Uart_Gpio();
        
        if(tickRead() - tiempo_set_lcd > timeout_lcd)
        {    
            showDateAndTimeLCD(&rtc_lcd);
            tiempo_set_lcd = tickRead();
        }
            
       
        sleepUntilNextInterrupt();
   }

   return 0;
}
