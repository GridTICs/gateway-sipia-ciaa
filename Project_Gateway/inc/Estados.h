#define CANT_ESTADOS 5

enum ESTADOS {
  
    EST_OK = 0,
    EST_ERROR,
    ENV_PAQUETE_TCP,
    REC_PAQUETE_TCP,
    CONECT_NTP_SERVER,
    CONFIG_RTC,
    CONFIG_FAT
    
    
};   

char* estados_maq[CANT_ESTADOS] = {
    "OK",
    "ERROR",
    "ENVIANDO TCP",
    "RECIBIENDO TCP",
    "CONFIG. NTP"
    
    
};


void LCD_Estado(int est)
{
    lcdClear(); // Borrar la pantalla
    lcdGoToXY( 1, 1 ); // Poner cursor en 1, 1
    lcdSendStringRaw(estados_maq[est]);
    
}