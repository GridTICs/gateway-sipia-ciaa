/* Buffer */
static char uartBuff_rtc[10];


char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}


/* Enviar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS" */
void showDateAndTime( rtc_t * rtc){
   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->mday), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio el dia */
   if( (rtc->mday)<10 )
      uartWriteByte( UART_USB, '0' );
   uartWriteString( UART_USB, uartBuff_rtc );
   uartWriteByte( UART_USB, '/' );

   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->month), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio el mes */
   if( (rtc->month)<10 )
      uartWriteByte( UART_USB, '0' );
   uartWriteString( UART_USB, uartBuff_rtc );
   uartWriteByte( UART_USB, '/' );

   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->year), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio el aÃ±o */
   if( (rtc->year)<10 )
      uartWriteByte( UART_USB, '0' );
   uartWriteString( UART_USB, uartBuff_rtc );


   uartWriteString( UART_USB, ", ");


   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->hour), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio la hora */
   if( (rtc->hour)<10 )
      uartWriteByte( UART_USB, '0' );
   uartWriteString( UART_USB, uartBuff_rtc );
   uartWriteByte( UART_USB, ':' );

   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->min), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio los minutos */
  // uartBuff_rtc[2] = 0;    /* NULL */
   if( (rtc->min)<10 )
      uartWriteByte( UART_USB, '0' );
   uartWriteString( UART_USB, uartBuff_rtc );
   uartWriteByte( UART_USB, ':' );

   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->sec), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio los segundos */
   if( (rtc->sec)<10 )
      uartWriteByte( UART_USB, '0' );
   uartWriteString( UART_USB, uartBuff_rtc );


   /* Envio un 'enter' */
   uartWriteString( UART_USB, "\r\n");
}


/* Enviar fecha y hora en formato "DD/MM/YYYY, HH:MM:SS" */
void showDateAndTimeLCD( rtc_t * rtc){
   
    char hora[10]={0};
    char fecha[10]={0};
    
    rtcRead(rtc);
    
    lcdClear();
    lcdGoToXY( 5, 1 ); // Poner cursor en 1, 1
    /* Conversion de entero a ascii con base decimal */
    itoa( (int) (rtc->mday), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
    /* Envio el dia */
    if( (rtc->mday)<10 )strcat(fecha, "0");
    strcat(fecha, uartBuff_rtc );
    strcat(fecha, "/" );

    /* Conversion de entero a ascii con base decimal */
    itoa( (int) (rtc->month), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
    /* Envio el mes */
    if( (rtc->month)<10 )strcat(fecha, "0" );
    strcat(fecha, uartBuff_rtc );
    strcat(fecha, "/" );

    /* Conversion de entero a ascii con base decimal */
    itoa( (int) (rtc->year), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
    /* Envio el aÃ±o */
    if( (rtc->year)<10 )strcat(fecha, "0" );
    strcat(fecha, uartBuff_rtc );
    
    lcdSendStringRaw(fecha);
    
    lcdGoToXY( 6, 2 ); // Poner cursor en 1, 1

   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->hour), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio la hora */
   if( (rtc->hour)<10 )strcat(hora, "0" );
   strcat(hora, uartBuff_rtc );
   strcat(hora, ":" );

   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->min), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio los minutos */
  // uartBuff_rtc[2] = 0;    /* NULL */
   if( (rtc->min)<10 )strcat(hora, "0" );
   strcat(hora, uartBuff_rtc );
   strcat(hora, ":" );

   /* Conversion de entero a ascii con base decimal */
   itoa( (int) (rtc->sec), (char*)uartBuff_rtc, 10 ); /* 10 significa decimal */
   /* Envio los segundos */
   if( (rtc->sec)<10 )strcat(hora, "0" );
   strcat(hora, uartBuff_rtc );

    lcdSendStringRaw(hora);
}






void RTC_Init()
{
    /* Estructura RTC */
    rtc_t rtc;
    
    
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
                            "Sep", "Oct", "Nov", "Dec"};
    
    unsigned char month_rtc, day_rtc, year_rtc;
    unsigned char hour_rtc, minutes_rtc, seconds_rtc;
    char temp [] = __DATE__;
    char temp_time[] = __TIME__; 
    unsigned char c;

    //Funcion que divide la fecha
    year_rtc = atoi(temp + 9);
    *(temp + 6) = 0;
    day_rtc = atoi(temp + 4);
    *(temp + 3) = 0;
    for (c = 0; c < 12; c++)
    {
        if (!strcmp(temp, months[c]))
        {
            month_rtc = c + 1;
        }
    }   
    
    // Función que divide el Time
    seconds_rtc = atoi(temp_time + 6);
    *(temp_time + 5) = 0;
    minutes_rtc = atoi(temp_time + 3);
    *(temp_time + 2) = 0;
    hour_rtc = atoi(temp_time);
    
   rtc.year = year_rtc;
   rtc.month = month_rtc;
   rtc.mday = day_rtc;
   rtc.wday = 1;
   rtc.hour = hour_rtc;
   rtc.min = minutes_rtc;
   rtc.sec= seconds_rtc;

   bool_t val = 0;
   uint8_t i = 0;

   /* Inicializar RTC */
   val = rtcConfig( &rtc );
    
    
    
   delay(2000); // El RTC tarda en setear la hora, por eso el delay
   
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
}
