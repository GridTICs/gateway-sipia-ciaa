/*

PROYECTO FINAL DE INGENIERÍA ELECTRÓNICA
UNIVERSIDAD TECNOLÓGICA NACIONAL
FACULTAD REGIONAL MENDOZA
Autor: Lucas Escribano - Rodrigo Gonzalez
Año: 2014

*/
//#define PRUEBA
//#define PRUEBA_INT_UART

// ************************** INCLUDES *************************************** //
#include "sapi.h"
#include <string.h>

#define UART_DEBUG                 UART_USB
#define UART_ESP01                 UART_232
#define UARTS_BAUD_RATE            115200
#define UART_MOTE_RX_BUFF_SIZE         1024     //Buffer de recepción de datos de los motes por el UART_GPIO
#define ESP8266_RX_BUFFER_SIZE         1024     //Buffer para la recepción del ESP8266

bool_t espSendDataServer(void);

//Inclusiones propias
#include "Estados.h"                //Estados que se muestran en el LCD.
#include "FAT_SD.h"                 //Funciones de la SD
#include "Interrupciones.h"         //Funciones de las interrupciones de todos los UART's
#include "ESP8622_driver.h"         //Driver de la placa de WiFi
#include "RTC_Config.h"             //Funciones de el Real Time Counter
#include "NTP_Config.h"             //Funciones de las conexiones con el Server NTP
#include "Menues_Config.h"


// ************************ DECLARACIONES ************************************ //
#define TIEMPO_INT_TIMER 500000
callBackFuncPtr_t ptrFunction = *myIntTick;

// *********************** VARIABLES GLOBALES ******************************** //
//Paso los prototipos para que no me de ningun Warning el compilador
uint32_t Timer_microsecondsToTicks(uint32_t);
void Timer_Init( uint8_t, uint32_t,callBackFuncPtr_t);

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
    uartConfig(UART_GPIO, 9600);
    
    gpioWrite( LEDB, ON );
 
 #ifndef PRUEBA_INT_UART
    
    uartWriteString(UART_USB, "\r\nLa EDU-CIAA ha sido iniciada correctamente,\r\ny los UART han sido configurados correctamente.\r\n");
 
    // Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x2 pixeles
    lcdInit( 16, 2, 5, 8 );
    lcdClear(); // Borrar la pantalla
    lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1
    lcdSendStringRaw( "Proyecto Final");
    lcdGoToXY( 1, 2 ); // Poner cursor en 1, 2
    lcdSendStringRaw( "UTN FRM");
 
    delay(3000);    
    
    LCD_Estado(EST_OK);
    
    uartWriteString(UART_USB, "\r\n...Ahora se configurará el Real Time Counter (RTC)...\r\n");
     
    LCD_Estado(CONF_RTC); 
 
#ifndef PRUEBA 
    //Esta función inicia el RTC, y le pone una fecha y hora establecidos
    //RTC_Init();
#endif
    
    LCD_Estado(CONFIG_SD);
    
     uartWriteString(UART_USB, "\r\n...Iniciando puerto SPI..\r\n");
   //Primero iniciamos el SPI
   if(spiConfig( SPI0 ))uartWriteString(UART_USB, "...El puerto SPI ha sido iniciado con éxtio!!!..\r\n");
   else 
   {
        stopProgramError();        
   }    
   
        uartWriteString(UART_USB, "\r\n...Iniciando SD..\r\n");
   
   //Ahora si iniciamos la SD
    if (sdcardInit( &sdcard ) == false)
    {
        stopProgramError(); 
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
    
    uartWriteString( UART_USB, "\r\nSe procede a leer las configuraciones en el archivo CONFIG.TXT...\r\n" );
    
    Tomar_Config_SD();
    
    LCD_Estado(CONFIG_ESP);
         
    uartWriteString(UART_USB, "\r\nAhora se configurará el ESP8266:\r\n");
    
    
    //Para pruebas:
    //esp01_Disconect_AP();
    
    //Primeros dejamos que el ESP8266 se conecte por si mismo
    //Si esto no ocurre se procede a configurar:
    
    
    
    
    if(!esp01_IP())
    {
        esp8266_mode();

        esp8266_mux();
        
        if( !esp01Init( UART_ESP01, UART_DEBUG, UARTS_BAUD_RATE ) ){
            stopProgramError(); // Como dio falso (error) me quedo en un bucle infinito
        }
        
        
        
        uartWriteString(UART_USB, "\r\n...ESP8266 configurado e iniciado correctamente...\r\n");
        
        LCD_Estado(CONECT_RED);
   
        uartWriteString(UART_USB, "\r\n\r\nAhora el ESP8266 se conectará a la red preferida:\r\n");

        if( !esp01ConnectToWifiAP( ssid_wifi, clave_wifi ) ){
            LCD_Estado(EST_ERROR); 
            stopProgramError(); // Como dio falso (error) me quedo en un bucle infinito
        }
    
    
        uartWriteString(UART_USB, "\r\n...ESP8266 conectado a red correctamente...\r\n");


    }
    else
    {    
        uartWriteString(UART_USB, "\r\n...SE TOMA CONFIGURACIÓN DE LA FLASH DEL ESP8266...\r\n");
        uartWriteString(UART_USB, "\r\n...CONFIGURACIÓN AUTOMÁTICA...\r\n");
    }   
    
    esp01DisconnectToServer_UDP();
        
    fatFs_Add_Log(sdcardDriveName(), "La EDU-CIAA es reiniciada por causas desconocidas."); 
    
    LCD_Estado(CONFIG_NTP);
   
    
    //Debería realizar la conexión con el Servidor NTP y traer la Fecha y Hora
    NTP_conection();
    
   
    //Inicializamos los punteros a sus buffer respectivos...
    punt_rx_gpio = gpioRxBuffer;
    punt_rx_esp = espRxIntBuffer;
   
    esp01ConnectToServer(servidor_tcpip, atoi(puerto_tcpip));
 
 #endif
 
    uartWriteString(UART_USB, "\r\nActivando las interrupciones del GPIO...\r\n");
    //Activo las interrupciones del UART_GPIO para que guarde las variables que llegan...
    uartCallbackSet(UART_GPIO, UART_RECEIVE, INT_GPIO_RX, NULL);
    uartInterrupt(UART_GPIO, true);

    uartCallbackSet(UART_232, UART_RECEIVE, INT_ESP_RX, NULL);
    uartInterrupt(UART_232, true);
        
    uartCallbackSet(UART_USB, UART_RECEIVE, USB_INT_RX, NULL);
    uartInterrupt(UART_USB, false);  
    punt_rx_usb = usbRxIntBuffer;  
        
    ResetGpioBuff();
    
    
    //Timer_Init( uint8_t timerNumber, uint32_t timerTicks,callBackFuncPtr_t voidFunctionPointer )
    Timer_Init(3,Timer_microsecondsToTicks(TIEMPO_INT_TIMER), ptrFunction);
    
    
    //mandar_paquete = false;
    uartWriteString(UART_USB, "\r\n...Interrupciones activadas con éxito...\r\n");
    
    LCD_Estado(EST_OK);
    
    //delay(5000);
    
    //Variables para mostrar el tiempo
    char dateandtime[30];
    
    gpioWrite( LEDB, OFF );
    gpioWrite( LEDG, ON );
    
    while(1)
    {     
 
#ifndef PRUEBA_INT_UART
       
        //Si la interrupción me da el "Ejecutar"
         if(botStatus == BOT_EJEC)
        {    
            switch(boton_pulsado)
            {
        
                case 1:
                    showDateAndTimeLCD(&rtc_lcd);
                break;
                        
                case 2:
                    LCD_Estado(lcdStatus);
                break;
             
                case 3:
                    if(usbStatus == UART_USB_CLEAR)
                    {
                        mainMenu();
                        lcdStatus = MENU_CONFIG;
                    }
                break;
            }
        botStatus = BOT_WAIT;
        }
        
#endif
        //Mandar_Uart_Gpio();
        
        if(bandera_mandar_datos == true)Mandar_Uart_TCP();
        
        //Como trabajo todo por interrupciones duermo la EDU-CIAA hasta que la próxima llegue
        sleepUntilNextInterrupt(); 
   }

   return 0;
}
