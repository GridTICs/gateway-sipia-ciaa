#define CANT_ESTADOS 20


enum ESTADOS {
  
    EST_OK = 0,
    EST_ERROR,
    CONF_RTC,
    CONFIG_SD,
    CONFIG_ESP,
    CONECT_RED,
    CONFIG_INT,
    CONFIG_NTP,
    ENV_PAQUETE_TCP,
    REC_PAQUETE_TCP,
    CONFIG_FAT,
    ERROR_SD
    
    
};   

char* estados_maq[CANT_ESTADOS] = {
    "OK",
    "ERROR REINIC.",
    "CONFIG. RTC",
    "CONFIG. SD",
    "CONFIG. ESP",
    "CONECTANDO RED",
    "CONFIG. INTERR.",
    "CONFIG. NTP",
    "ENVIANDO TCP",
    "RECIBIENDO TCP",
    "",
    "SD ERROR"
    
};


void LCD_Estado(int est)
{
  
        lcdClear(); // Borrar la pantalla
        lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1
        lcdSendStringRaw(estados_maq[est]);

}