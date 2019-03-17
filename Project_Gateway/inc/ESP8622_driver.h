/*==================[definiciones y macros]==================================*/

// UART list:
//  - UART_GPIO or UART_485
//  - UART_USB or UART_ENET
//  - UART_232

#define UART_DEBUG                 UART_USB
#define UART_ESP01                 UART_232
#define UARTS_BAUD_RATE            115200

#define UART_MOTE_RX_BUFF_SIZE         1024     //Buffer de recepción de datos de los motes por el UART_GPIO
 
#define ESP8266_RX_BUFFER_SIZE         1024     //Buffer para la recepción del ESP8266

#define SERVER_URL      "192.168.0.106"
#define SERVER_PORT     2222

#define WIFI_SSID       "Chupala" 
#define WIFI_PASSWORD   "Reina650Woody?"

/*==================[definiciones de datos internos]=========================*/

CONSOLE_PRINT_ENABLE
DEBUG_PRINT_ENABLE

/*==================[definiciones de datos externos]=========================*/

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

// ESP01 Rx Buffer
char espResponseBuffer[ ESP8266_RX_BUFFER_SIZE ];
uint32_t espResponseBufferSize = ESP8266_RX_BUFFER_SIZE;

// UARTs
uartMap_t uartEsp01 = UART_232;
uartMap_t uartDebug = UART_USB;

char tcpIpDataToSend[100];
int64_t sensorValue = 0;


bool_t esp01Init( uartMap_t uartForEsp, uartMap_t uartForDebug, uint32_t baudRate );

void esp01CleanRxBuffer( void );

bool_t esp01ShowWiFiNetworks( void );

bool_t esp01ConnectToWifiAP( char* wiFiSSID, char* wiFiPassword );

bool_t esp01ConnectToServer( char* url, uint32_t port );

bool_t esp01SendTCPIPData( char* strData, uint32_t strDataLen );

bool_t esp01SendTPCIPDataToServer( char* url, uint32_t port, char* strData, uint32_t strDataLen );

bool_t espCleanReceivedData(char* buffer);

bool_t esp01ConnectToServer_UDP(char* addr, uint32_t port);

bool_t esp01DisconnectToServer_UDP(void);

bool_t esp01SendNTPData( char* strData, uint32_t strDataLen );

void esp8266_mode();

void esp8266_mux();


void esp01CleanRxBuffer( void ){
   espResponseBufferSize = ESP8266_RX_BUFFER_SIZE;
   memset( espResponseBuffer, 0, espResponseBufferSize );
}


// AT+CIPSTART="TCP","api.thingspeak.com",80
bool_t esp01SendTPCIPDataToServer( char* url, uint32_t port, char* strData, uint32_t strDataLen ){

   // Enviar dato "data" al servidor "url", puerto "port".
   uartWriteString( UART_DEBUG, ">>>> ===========================================================\r\n" );
   uartWriteString( UART_DEBUG,  ">>>> Enviar dato: \"" );
   uartWriteString( UART_DEBUG,  strData );
   uartWriteString( UART_DEBUG, "\"\r\n>>>> al servidor \"" );
   uartWriteString( UART_DEBUG, url );
   uartWriteString( UART_DEBUG, "\", puerto \"" );
   uartWriteString( UART_DEBUG, intToString(port) );
   uartWriteString( UART_DEBUG, "\"...\r\n" );
   uartWriteString( UART_DEBUG,"\r\n");

   // AT+CIPSTART="TCP","url",port ---------------------------
   if( !esp01ConnectToServer( url, port ) )
      return FALSE;

   // Ejemplo:
   // AT+CIPSEND=47 ------------------------------------------
   // GET /update?api_key=7E7IOJ276BSDLOBA&field1=66 ---------
   if( !esp01SendTCPIPData( strData, strDataLen ) )
      return FALSE;

   return TRUE;
}



// AT+CIPSEND=39
// GET /update?key=7E7IOJ276BSDLOBA&1=69
bool_t esp01SendTCPIPData( char* strData, uint32_t strDataLen ){

   bool_t retVal = FALSE;

   // "GET /update?key=7E7IOJ276BS\"DL\"OBA&1=69"
   // AT+CIPSEND=strDataLen strData --------------------------

   // Limpiar Buffer (es necesario antes de usar
   // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
   esp01CleanRxBuffer();

   // Envio datos TCP/IP al servidor.
   uartWriteString( UART_DEBUG, ">>>> Envio datos TCP/IP al servidor...\r\n" );

   uartWriteString( UART_DEBUG,">>>> AT+CIPSEND=" );
   uartWriteString( UART_DEBUG, intToString(strDataLen) ); // El mas 2 es del \r\n
   uartWriteString( UART_DEBUG, "\r\n" );

   uartWriteString( UART_ESP01, "AT+CIPSEND=" );
   uartWriteString( UART_ESP01, intToString(strDataLen) ); // El mas 2 es del \r\n
   uartWriteString( UART_ESP01, "\r\n" );

   // No poner funciones entre el envio de comando y la espera de respuesta
   retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "\r\n\r\nOK\r\n>", 9,
               espResponseBuffer, &espResponseBufferSize,
               5000
            );
    
       
   if( retVal ){

      // Imprimo todo lo recibido
      uartWriteString( UART_DEBUG, espResponseBuffer );

      // strData\r\n --------------------------------------------

      // Limpiar Buffer (es necesario antes de usar
      // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
      esp01CleanRxBuffer();

      // Envio los datos TCP/IP ------------------
      uartWriteString( UART_ESP01, strData );
      //uartWriteString( UART_ESP01, "\r\n" );

      // No poner funciones entre el envio de comando y la espera de respuesta
      retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
                  uartEsp01,
                  "SEND OK\r\n", 9,
                  espResponseBuffer, &espResponseBufferSize,
                  5000
               );
      if( retVal ){

         /*// Imprimo todo lo recibido
         uartWriteString( UART_DEBUG, espResponseBuffer );

         // Limpiar Buffer (es necesario antes de usar
         // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
         esp01CleanRxBuffer();

         // Envio los datos TCP/IP ------------------
         uartWriteString( UART_ESP01, strData );

         // No poner funciones entre el envio de comando y la espera de respuesta
         retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
                     uartEsp01,
                     "CLOSED\r\n", 8,
                     espResponseBuffer, &espResponseBufferSize,
                     5000
                  );

         if( retVal ){

            // DATO RECIBIDOOOOOOOOOOO -----------------

            // Imprimo todo lo recibido
            uartWriteString( UART_DEBUG, espResponseBuffer );



         } else{
            uartWriteString( UART_DEBUG, ">>>> Error al enviar los datos TCP/IP, en el envio del string\r\n" );
            uartWriteString( UART_DEBUG, ">>>> \"strData\", cuando el ESP01 pone el prompt > \r\n" );
            uartWriteString( UART_DEBUG, ">>>> y no se recibe la respuesta y \"CLOSED\"!!\r\n" );

            // Imprimo todo lo recibido
            uartWriteString( UART_DEBUG, espResponseBuffer );
         }*/


      } else{
         uartWriteString( UART_DEBUG, ">>>> Error al enviar los datos TCP/IP, en el envio del string\r\n" );
         uartWriteString( UART_DEBUG, ">>>> \"strData\", cuando el ESP01 pone el prompt > \r\n" );
         uartWriteString( UART_DEBUG, ">>>> y no se recibe \"SEND OK\"!!\r\n" );

         // Imprimo todo lo recibido
         uartWriteString( UART_DEBUG, espResponseBuffer );
      }

   } else{
      uartWriteString( UART_DEBUG, ">>>> Error al enviar los datos TCP/IP, en comando\r\n" );
      uartWriteString( UART_DEBUG, ">>>> \"AT+CIPSEND\"!!\r\n" );
      // Imprimo todo lo recibido
      uartWriteString( UART_DEBUG, espResponseBuffer );
   }
   return retVal;
}


//Función que recibe los datos del ESP8266 y limpia la parte del inicio
/* La forma en que llega el dato es:                                                */
/* +IPD,<id>,<len>:<data>   (No es nuestro caso porque solo tenemos 1 conexión)     */
/* +IPD,<len>:<data>                                                                */

bool_t espCleanReceivedData(char* buffer)
{
    char *dos_puntos;
    char buffer_aux[1024];
 
    if(strstr(buffer, "+IPD,")>0)
    {
                dos_puntos = strstr(buffer, ":");
                strcpy(buffer_aux, (dos_puntos+1));
                memset( buffer, '\0', sizeof(buffer) );
                strcpy(buffer, buffer_aux);
                return true;
    }
    else
    {
        return false;
    }    
    

    
} 






//La diferencia con las funciones comunes de envío de datos es que este tipo de datos
//es del tipo uint8_t, no del tipo char
bool_t esp01SendNTPData( char* strData, uint32_t strDataLen ){

    bool_t retVal = FALSE;
    uint8_t i = 0;
    uint8_t buffer_ntp[2]={0};
   // "GET /update?key=7E7IOJ276BS\"DL\"OBA&1=69"
   // AT+CIPSEND=strDataLen strData --------------------------

   // Limpiar Buffer (es necesario antes de usar
   // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
   esp01CleanRxBuffer();

   // Envio datos TCP/IP al servidor.
   uartWriteString( UART_DEBUG, ">>>> Envio datos UDP al servidor...\r\n" );

   uartWriteString( UART_DEBUG,">>>> AT+CIPSEND=" );
   uartWriteString( UART_DEBUG, intToString(strDataLen) ); // El mas 2 es del \r\n
   uartWriteString( UART_DEBUG, "\r\n" );

   uartWriteString( UART_ESP01, "AT+CIPSEND=" );
   uartWriteString( UART_ESP01, intToString(strDataLen) ); // El mas 2 es del \r\n
   uartWriteString( UART_ESP01, "\r\n" );

   // No poner funciones entre el envio de comando y la espera de respuesta
   retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "\r\n\r\nOK\r\n>", 9,
               espResponseBuffer, &espResponseBufferSize,
               5000
            );
   if( retVal ){

      // Imprimo todo lo recibido
      uartWriteString( UART_DEBUG, espResponseBuffer );

      // strData\r\n --------------------------------------------

      // Limpiar Buffer (es necesario antes de usar
      // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
      esp01CleanRxBuffer();

      // Envio los datos TCP/IP ------------------
      for(i=0;i<strDataLen;i++)
      {    
        uartWriteByte( UART_ESP01, strData[i] );
        //uartWriteByte( UART_DEBUG, strData[i] );
        //uartWriteString( UART_DEBUG, "\r\n" );
      
      }    
      //uartWriteString( UART_ESP01, "\r\n" );

      // No poner funciones entre el envio de comando y la espera de respuesta
      retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
                  uartEsp01,
                  "SEND OK", 7,
                  espResponseBuffer, &espResponseBufferSize,
                  3000
               ); 
      if( retVal ){
            
            //esp01CleanRxBuffer();
            // Habilito todas las interrupciones de UART_USB
            uartInterrupt(UART_232, true);              
          
      } else{
         uartWriteString( UART_DEBUG, ">>>> Error al enviar los datos UDP, en el envio del string\r\n" );
         uartWriteString( UART_DEBUG, ">>>> \"strData\", cuando el ESP01 pone el prompt > \r\n" );
         uartWriteString( UART_DEBUG, ">>>> y no se recibe \"SEND OK\"!!\r\n" );

         // Imprimo todo lo recibido
         uartWriteString( UART_DEBUG, espResponseBuffer );
      }

   } else{
      uartWriteString( UART_DEBUG, ">>>> Error al enviar los datos UDP, en comando\r\n" );
      uartWriteString( UART_DEBUG, ">>>> \"AT+CIPSEND\"!!\r\n" );
      // Imprimo todo lo recibido
      uartWriteString( UART_DEBUG, espResponseBuffer );
   }
   return retVal;
}




// AT+CIPSTART="TCP","api.thingspeak.com",80
bool_t esp01ConnectToServer( char* url, uint32_t port ){

   bool_t retVal = FALSE;

   // AT+CIPSTART="TCP","url",port ---------------------------

   // Limpiar Buffer (es necesario antes de usar
   // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
   esp01CleanRxBuffer();

   uartWriteString( UART_DEBUG, ">>>> Conectando al servidor \"" );
   uartWriteString( UART_DEBUG, url );
   uartWriteString( UART_DEBUG, "\", puerto \"" );
   uartWriteString( UART_DEBUG, intToString(port) );
   uartWriteString( UART_DEBUG, "\"...\r\n" );

   uartWriteString( UART_DEBUG, ">>>> AT+CIPSTART=\"TCP\",\"" );
   uartWriteString( UART_DEBUG, url );
   uartWriteString( UART_DEBUG, "\"," );
   uartWriteString( UART_DEBUG, intToString(port) );
   uartWriteString( UART_DEBUG, "\r\n" );

   uartWriteString( UART_ESP01, "AT+CIPSTART=\"TCP\",\"" );
   uartWriteString( UART_ESP01,url );
   uartWriteString( UART_ESP01, "\"," );
   uartWriteString( UART_ESP01, intToString(port) );
   uartWriteString( UART_ESP01, "\r\n" );

   // No poner funciones entre el envio de comando y la espera de respuesta
   retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "CONNECT\r\n\r\nOK\r\n", 15,
               espResponseBuffer, &espResponseBufferSize,
               3000
            );
    
    if(strstr(espResponseBuffer, "ALREADY CONNECTED") !=NULL ) retVal = true;
    
   if( !retVal ){
      uartWriteString( UART_DEBUG, ">>>>    Error: No se puede conectar al servidor: \"" );
      uartWriteString( UART_DEBUG, url );
      uartWriteString( UART_DEBUG,"\"," );
      uartWriteString( UART_DEBUG, intToString(port) );
      uartWriteString( UART_DEBUG, "\"!!\r\n" );
   }
   // Imprimo todo lo recibido
   uartWriteString( UART_DEBUG, espResponseBuffer );
   return retVal;
}


bool_t esp01ConnectToWifiAP( char* wiFiSSID, char* wiFiPassword ){

   bool_t retVal = FALSE;
   char* index = 0;

   // AT+CWJAP="wiFiSSID","wiFiPassword" ---------------------

   // Limpiar Buffer (es necesario antes de usar
   // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
   esp01CleanRxBuffer();

   // Conectar a la red Wi-Fi. se envia AT+CWJAP="wiFiSSID","wiFiPassword"
   uartWriteString( UART_DEBUG, ">>>> Conectando a la red Wi-Fi: \"" );
   uartWriteString( UART_DEBUG, wiFiSSID );
   uartWriteString( UART_DEBUG, "\"...\r\n" );

   uartWriteString( UART_ESP01, "AT+CWJAP=\"" );
   uartWriteString( UART_ESP01, wiFiSSID );
   uartWriteString( UART_ESP01, "\",\"" );
   uartWriteString( UART_ESP01, wiFiPassword );
   uartWriteString( UART_ESP01, "\"\r\n" );

   // No poner funciones entre el envio de comando y la espera de respuesta
   retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "WIFI CONNECTED\r\nWIFI GOT IP\r\n\r\nOK\r\n", 35,
               espResponseBuffer, &espResponseBufferSize,
               10000
            );
   if( retVal ){

      // Imprimo todo lo recibido filtrando la parte que muestra el password, llega:

      // AT+CWJAP="wiFiSSID","wiFiPassword"
      //
      // WIFI DISCONNECT ----> Opcional
      // WIFI CONNECTED
      // WIFI GOT IP
      //
      // OK

      // Pero imprimo:

      // WIFI CONNECTED
      // WIFI GOT IP
      //
      // OK

      index = strstr( (const char*)espResponseBuffer, (const char*)"WIFI CONNECTED" );
      if( index != 0 ){
         // Muestro desde " WIFI CONNECTED" en adelante
         uartWriteString( UART_DEBUG, index );
      } else{
         // Muestro todo en caso de error
         uartWriteString( UART_DEBUG,espResponseBuffer );
      }
   } else{
      uartWriteString( UART_DEBUG, ">>>>    Error: No se puede conectar a la red: \"" );
      uartWriteString( UART_DEBUG, wiFiSSID );
      uartWriteString( UART_DEBUG, "\"!!\r\n" );

      // Muestro todo en caso de error
      uartWriteString( UART_DEBUG, espResponseBuffer );
   }
   return retVal;
}


bool_t esp01ShowWiFiNetworks( void ){

   bool_t retVal = FALSE;

   // AT+CWLAP -----------------------------------------------

   // Limpiar Buffer (es necesario antes de usar
   // "receiveBytesUntilReceiveStringOrTimeoutBlocking")
   esp01CleanRxBuffer();

   // Mostrar lista de AP enviando "AT+CWLAP"
   uartWriteString( UART_DEBUG, ">>>> Consultando las redes Wi-Fi disponibles.\r\n>>>>    Enviando \"AT+CWLAP\"..." );
   uartWriteString( UART_ESP01, "AT+CWLAP\r\n" );
   // No poner funciones entre el envio de comando y la espera de respuesta
   retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               ")\r\n\r\nOK\r\n", 9,
               espResponseBuffer, &espResponseBufferSize,
               20000
            );
   if( !retVal ){
      uartWriteString( UART_DEBUG, ">>>>    Error: No se encuentran redes disponibles!!\r\n" );
   }
   // Imprimo todo lo recibido
   uartWriteString( UART_DEBUG, espResponseBuffer );
   return retVal;
}


bool_t esp01Init( uartMap_t uartForEsp, uartMap_t uartForDebug, uint32_t baudRate ){

   bool_t retVal = FALSE;

   uartEsp01 = uartForEsp;
   uartDebug = uartForDebug;

   // Initialize HW ------------------------------------------

   // Inicializar UART_USB como salida de debug
   uartWriteString( UART_DEBUG, ">>>> UART_USB configurada como salida de debug.\r\n" );

   // Inicializr otra UART donde se conecta el ESP01 como salida de consola
   uartWriteString( UART_DEBUG, ">>>> UART_ESP (donde se conecta el ESP01), \r\n>>>> configurada como salida de consola.\r\n\r\n" );

   // AT -----------------------------------------------------

   // Chequear si se encuentra el modulo Wi-Fi enviandole "AT"
   uartWriteString( UART_DEBUG, ">>>> Chequear si se encuentra el modulo Wi-Fi.\r\n>>>>    Enviando \"AT\"...\r\n" );
   uartWriteString( UART_ESP01, "AT\r\n" );
   // No poner funciones entre el envio de comando y la espera de respuesta
   retVal = waitForReceiveStringOrTimeoutBlocking( uartEsp01, "AT\r\n", 4, 500 );
   if( retVal ){
      uartWriteString( UART_DEBUG, ">>>>    Modulo ESP01 Wi-Fi detectado.\r\n" );
   } else{
      uartWriteString( UART_DEBUG, ">>>>    Error: Modulo ESP01 Wi-Fi No detectado!!\r\n" );
      return retVal;
   }

   // AT+CWLAP -----------------------------------------------
   return esp01ShowWiFiNetworks();
}


void stopProgramError( void ){
   // Si hay un error grave me quedo en un bucle infinito
   // en modo bajo consumo
   while( TRUE ){
      sleepUntilNextInterrupt();
   }
}

bool_t esp01ConnectToServer_UDP(char* url, uint32_t port)
{
    bool_t retVal = FALSE;

    esp01CleanRxBuffer();

    uartWriteString( UART_ESP01, "AT+CIPSTART=\"UDP\",\"" );
    uartWriteString( UART_ESP01,url );
    uartWriteString( UART_ESP01, "\"," );
    uartWriteString( UART_ESP01, intToString(port) );
    uartWriteString( UART_ESP01, "\r\n" );

       // No poner funciones entre el envio de comando y la espera de respuesta
    retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "CONNECT\r\n\r\nOK\r\n", 15,
               espResponseBuffer, &espResponseBufferSize,
               10000
            );
    if( !retVal ){
      uartWriteString( UART_DEBUG, ">>>>    Error: No se puede conectar al servidor: \"" );
      uartWriteString( UART_DEBUG, url );
      uartWriteString( UART_DEBUG,"\"," );
      uartWriteString( UART_DEBUG, intToString(port) );
      uartWriteString( UART_DEBUG, "\"!!\r\n" );
    }
    // Imprimo todo lo recibido
    uartWriteString( UART_DEBUG, espResponseBuffer );
    return retVal;
}

bool_t esp01DisconnectToServer_UDP(void)
{
    bool_t retVal = FALSE;    
    
    esp01CleanRxBuffer();
    uartWriteString(UART_ESP01,"AT+CIPCLOSE\r\n");
           // No poner funciones entre el envio de comando y la espera de respuesta
    retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "OK\r\n", 4,
               espResponseBuffer, &espResponseBufferSize,
               5000
            );
    
    
    if( !retVal ){
      uartWriteString( UART_DEBUG, ">>>>    Error: No se puede desconectar del servidor: \"" );
    }
    
    // Imprimo todo lo recibido
    uartWriteString( UART_DEBUG, espResponseBuffer );
    
    return retVal;
}

//Con esta función selecciono el modo de operación correspondiente
void esp8266_mode()
{
	bool_t retVal = FALSE; 

	uartWriteString( UART_ESP01,"AT+CWMODE_CUR=3\r\n");
    
       // No poner funciones entre el envio de comando y la espera de respuesta
    retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "OK", 2,
               espResponseBuffer, &espResponseBufferSize,
               5000
            );
    
    if(retVal)uartWriteString( UART_USB,"\r\nModo configurado correctamente...!!!");
        
    if(!retVal)uartWriteString( UART_USB,"\r\nModo NO configurado correctamente...!!!");
	
}

void esp8266_mux()
{
    bool_t retVal = FALSE; 
    
	uartWriteString( UART_ESP01,"AT+CIPMUX=0\r\n");

	    // No poner funciones entre el envio de comando y la espera de respuesta
    retVal = receiveBytesUntilReceiveStringOrTimeoutBlocking(
               uartEsp01,
               "OK\r\n", 4,
               espResponseBuffer, &espResponseBufferSize,
               5000
            );
    
    if(retVal)uartWriteString( UART_USB,"\r\nMultiplexado configurado correctamente...!!!");
        
    if(!retVal)uartWriteString( UART_USB,"\r\nMultiplexado NO configurado correctamente...!!!");

}


