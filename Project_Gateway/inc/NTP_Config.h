
#define NTP_PACKET_SIZE 48 // NTP time stamp is in the first 48 bytes of the message
uint8_t packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

//PARA PASAR DE SEGUNDOS A FECHA Y HORA
// EPOCH = Jan 1 1970 00:00:00
#define   EPOCH_YR   1970
//(24L * 60L * 60L)
#define   SECS_DAY   86400UL
#define   LEAPYEAR(year)   (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define   YEARSIZE(year)   (LEAPYEAR(year) ? 366 : 365)

#define BUFSIZE (sizeof(long) * 8 + 1)

static const char day_abbrev[21] = "SunMonTueWedThuFriSat";

//Realiza una conexión NTP con el servidor argentino y devuelve la configuración en el RTC de la EDU-CIAA
//Es importante haber iniciado el RTC con rtcConfig(), de no hacer esto el rtc no se configurará correctamente
bool NTP_conection();

//Función necesaria para enviar el paquete que pide la hora al servidor NTP
void sendNTPpacket();

//Funcion que convierte un unsigned long en un string
//value = unsigned long que se quiere pasar a string
//*ptr = puntero al string donde se almacena el resultado
//base = base de conversión, 10 significa decimal
char *ultostr(unsigned long value, char *ptr, int base);

//Función que convierte la cantidad de segundos desde el 1 de enero de 1970 hasta hoy en la fecha de hoy
//time = tiempo en segundos desde el 1 de enero de 1970 hasta hoy
bool gmtime(unsigned long time);

//Función que se utiliza para saber cuantos días tiene el mes actual
//isleapyear = 0 si el año NO es biciesto
//			   1 si el año es biciesto
//month = mes del año que va entre 0-11
uint8_t monthlen(uint8_t isleapyear,uint8_t month);


bool NTP_conection()
{
	bool bandera_break = FALSE;
	int cant=0;
    
    uint16_t cantData;

	uint32_t largo=0;
	uint8_t i=0;
    
    uint8_t buffer_ntp[100];
    uint8_t *punt_ntp;

    char *ptr_dos_puntos;
    int cant_ntp = 0;
    bool_t band_transp = false;
    int pos = 0;
    int j;

    uartWriteString(UART_USB, "\r\nPrimero nos desconectamos de cualquier server...\r\n");
    
    if(esp01DisconnectToServer_UDP())uartWriteString(UART_USB, "\r\nDesconexión correcta...\r\n");
    
    //delay(2000);

    uartWriteString(UART_USB, "\r\nAhora nos conectamos al server UDP...\r\n");

	while(1)
	{
		if(esp01ConnectToServer_UDP(servidor_ntp, 123))
		{
            uartWriteString(UART_USB, "\r\nLa conexion UDP es correcta...\r\n");
            bandera_break = TRUE;
		}
		else
		{
            uartWriteString(UART_USB, "\r\nLa conexion UDP no se ha realizado...\r\n");
            cant++;
		}
	
        delay(2000);
	
        if(cant==5)
		{
            uartWriteString(UART_USB, "\r\nDespues de 5 intentos ERROR.\r\n");
            return FALSE;
		}
        
        if(bandera_break==TRUE)break;
	}

    memset( buffer_ntp, '\0', sizeof(buffer_ntp) );
    
    punt_ntp = buffer_ntp;
    //bandera_NTP = true;
    //Envío el paquete correspondiente para pedir la hora actual al servidor NTP
    sendNTPpacket();
    
    cantData = espCleanReceivedData(espResponseBuffer);
 
 #ifdef PRUEBA   
    uartWriteString(UART_USB, "\r\nLos Datos Ya Trabajados Son: ");
    uartWriteByteArray( UART_DEBUG, espResponseBuffer, cantData );
#endif

    memcpy(buffer_ntp,espResponseBuffer,cantData);
    
    //Cierro la conexión UDP
    esp01DisconnectToServer_UDP();
    

  ///////////////////// FORMA A LA HORA DEL SERVIDOR NTP ////////////////////////////////////////

  //the timestamp starts at byte 40 of the received packet and is four bytes,
  // or two words, long. First, esxtract the two words:

  	  char buff_aux_ntp[50]={0};
      char *ptr_ntp;
      ptr_ntp = &buff_aux_ntp[0];
      
      unsigned long highWord = ((buffer_ntp[40]<<8) & 0xFF00)+buffer_ntp[41];
      unsigned long lowWord = ((buffer_ntp[42]<<8) & 0xFF00)+buffer_ntp[43];
      //unsigned long lowWord = word(buffer_ntp[42], buffer_ntp[43]);
      // combine the four bytes (two words) into a long integer
      // this is NTP time (seconds since Jan 1 1900):
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      ultostr(secsSince1900,ptr_ntp,10);
      uartWriteString(UART_USB,"\r\n\r\nSeconds since Jan 1 1900 = " );
      uartWriteString(UART_USB, ptr_ntp);

      // now convert NTP time into everyday time:
      uartWriteString(UART_USB,"\r\nUnix time = ");
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      // subtract seventy years:
      unsigned long epoch = secsSince1900 - seventyYears - 10800;
      i=0;
      for(i=0;i<50;i++)buff_aux_ntp[i]=0;
      ultostr(epoch,ptr_ntp,10);
      uartWriteString(UART_USB,ptr_ntp);

      if(gmtime(epoch))
      {
    	  return TRUE;
      }
      else
      {
    	  return FALSE;
      }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////


}

// send an NTP request to the time server at the given address
void sendNTPpacket()
{
  //Serial.println("1");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  //Serial.println("2");
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  //Serial.println("3");

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  //Udp.beginPacket(address, 123); //NTP requests are to port 123
  //Serial.println("4");
  //Udp.write(packetBuffer, NTP_PACKET_SIZE);
  esp01SendNTPData(packetBuffer, 48);
  //Serial.println("5");
  //Udp.endPacket();
  //Serial.println("6");


}



char *ultostr(unsigned long value, char *ptr, int base)
{
  unsigned long t = 0, res = 0;
  unsigned long tmp = value;
  int count = 0;

  if (NULL == ptr)
  {
    return NULL;
  }

  if (tmp == 0)
  {
    count++;
  }

  while(tmp > 0)
  {
    tmp = tmp/base;
    count++;
  }

  ptr += count;

  *ptr = '\0';

  do
  {
    res = value - base * (t = value / base);
    if (res < 10)
    {
      * -- ptr = '0' + res;
    }
    else if ((res >= 10) && (res < 16))
    {
        * --ptr = 'A' - 10 + res;
    }
  } while ((value = t) != 0);

  return(ptr);
}



// isleapyear = 0-1
// month=0-11
// return: how many days a month has
uint8_t monthlen(uint8_t isleapyear,uint8_t month){
   if(month==1){
      return(28+isleapyear);
   }
   if (month>6){
      month--;
   }
   if (month%2==1){
      return(30);
   }
   return(31);
}


bool gmtime(unsigned long time)
{
   char dstr[4]; // week days
   char ampm[3]="pm";

   rtc_t rtc;

   uint8_t i;
   uint32_t dayclock;
   uint16_t dayno;
   uint16_t tm_year = EPOCH_YR;
   uint8_t tm_sec,tm_min,tm_hour,tm_wday,tm_mon;

   dayclock = time % SECS_DAY;
   dayno = time / SECS_DAY;

   tm_sec = dayclock % 60UL;
   tm_min = (dayclock % 3600UL) / 60;
   tm_hour = dayclock / 3600UL;
   tm_wday = (dayno + 4) % 7;   /* day 0 was a thursday */
   while (dayno >= YEARSIZE(tm_year)) {
      dayno -= YEARSIZE(tm_year);
      tm_year++;
   }
   tm_mon = 0;
   while (dayno >= monthlen(LEAPYEAR(tm_year),tm_mon)) {
      dayno -= monthlen(LEAPYEAR(tm_year),tm_mon);
      tm_mon++;
   }
        i=0;
        while (i<3){
                dstr[i]= day_abbrev[tm_wday*3 + i];
                i++;
        }
        dstr[3]='\0';
   //sprintf_P(day,PSTR("%s %u-%02u-%02u"),dstr,tm_year,tm_mon+1,dayno + 1);

        rtc.year = tm_year;
        rtc.month = tm_mon+1;
        rtc.mday = dayno+1;
        rtc.hour = tm_hour;
        rtc.min = tm_min;
        rtc.sec= tm_sec;

        bool_t val = 0;
        /* Inicializar RTC */
        val = rtcWrite( &rtc );
        
        delay(2000);
        
        if(val == 1)
        {
            uartWriteString( UART_USB, "\r\nEl RTC ha sido configurado exitosamente...\r\n");
            
            if(rtcRead(&rtc)==1) 
            {
                uartWriteString( UART_USB, "Se lee la fecha y hora configuradas: ");
                showDateAndTime(&rtc);
            }
            else
            {
                uartWriteString( UART_USB, "\r\nLa hora no ha podido ser leída correctamente.\r\n");
            }
        }
        else uartWriteString( UART_USB, "\r\nEl RTC NO ha sido configurado exitosamente\r\n");
        
        return val;
}


