#include "sapi_sdcard.h"
//#include "sapi_usbms.h"
#include "sapi.h"

#include "ff.h"
/*
#ifndef LPCUSBLIB_HOST_MASS_STORAGE
    #error No olvidar USE_LPCUSBLIB=y en config.mk!
#endif*/

#define EXAMPLE_TEST_SDCARD_WRAPPER


#if !defined(EXAMPLE_TEST_SDCARD_WRAPPER) && !defined(EXAMPLE_TEST_USBMS_WRAPPER)
    #error Se debe probar al menos un wrapper!
#endif


#define SD_BUFFER_SIZE                 1024     //Buffer para trabajar con la SD   (probablemente necesite mas).

//Buffer SD
char sdBuffer[SD_BUFFER_SIZE];
unsigned int punt_rx_sd;

char ssid_wifi[30];
char clave_wifi[30];
char servidor_tcpip[50];
char puerto_tcpip[10];
char servidor_ntp[30];


// Wrappers para manejar dispositivos USB Mass Storage y tarjeta SD
sdcard_t sdcard;


// Se guarda el ultimo estado para enviar un mensaje solo cuando el estado 
// cambie.
sdcardStatus_t sdcardUltimoEstado = -1;

void diskTickHook ( void *ptr );

static void mostrarEstadoTarjetaSD( void )
{
    // El estado actual es distinto al ultimo mostrado?
    if ( sdcardUltimoEstado == sdcardStatus() )
    {
        // Es igual, no hay nada que hacer aca
        return;
    }
    
    // Es diferente, guardo y envio estado
    sdcardUltimoEstado = sdcardStatus();
    
    switch( sdcardUltimoEstado )
    {
        case SDCARD_Status_Removed:
            uartWriteString( UART_USB, "STATUS: Por favor inserte Tarjeta SD.\r\n" );
            break;
        
        case SDCARD_Status_Inserted:
            uartWriteString( UART_USB, "STATUS: Tarjeta SD insertada.\r\n" );
            break;
    
        case SDCARD_Status_NativeMode:
            uartWriteString( UART_USB, "STATUS: Configurando tarjeta SD.\r\n" );
            break;
            
        case SDCARD_Status_Initializing:
            uartWriteString( UART_USB, "STATUS: Iniciando tarjeta SD.\r\n" );
            break;
        
        case SDCARD_Status_ReadyUnmounted:
            uartWriteString( UART_USB, "STATUS: Tarjeta SD lista pero desmontada.\r\n" );
            break;

        case SDCARD_Status_ReadyMounted:
            uartWriteString( UART_USB, "STATUS: Tarjeta SD lista y montada.\r\n" );
            break;
        
        case SDCARD_Status_Error:
            uartWriteString( UART_USB, "STATUS: Tarjeta SD en estado de Error.\r\n" );
            break;
    }
}

static void fatFsTestOK( void )
{
    uartWriteString( UART_USB, "OK!\r\n" );
}


static void fatFsTestERROR( int error )
{
    char msg[256];
    sprintf( msg, "ERROR %i.\r\n", error );
    uartWriteString( UART_USB, msg );
}


static bool fatFs_Open_or_Create( const char *unidad, const char *nombre_archivo )
{
    char buf[1024];
    char filename[64];    
    FIL file;
    FRESULT fr;
    int r;
    
    sprintf( filename, "%s/", unidad );
    strcat(filename, nombre_archivo);

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
    
    // Ver http://elm-chan.org/fsw/ff/00index_e.html para una referencia de la
    // API de FatFs
    
    // Abre un archivo. Si no existe lo crea, si existe, lo sobreescribe.
    fr = f_open( &file, filename, FA_OPEN_APPEND | FA_WRITE);
    if( fr != FR_OK )
    {
        fatFsTestERROR( fr );
        return false;
    }
    
    // Cierra el archivo y vuelve a abrirlo como LECTURA
    f_close( &file );

    return true;   
}

static bool fatFs_Add_Log(const char *unidad , const char *log)
{
    char buf[1024];
    char filename[64];    
    FIL file;
    FRESULT fr;
    int r;
    
    sprintf( filename, "%s/LOG.TXT", unidad );

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
    
    // Ver http://elm-chan.org/fsw/ff/00index_e.html para una referencia de la
    // API de FatFs
    
    // Abre un archivo. Si no existe lo crea, si existe, me manda el puntero al último para escribir debajo.
    fr = f_open( &file, filename, FA_OPEN_APPEND | FA_WRITE);
    if( fr != FR_OK )
    {
        fatFsTestERROR( fr );
        return false;
    }
    
    //f_puts
   sprintf (buf, "\r\n"
                  "%s %s ; "
                  "%s",
                  __DATE__, __TIME__,
                  log);
    
    r = f_puts( buf, &file );
    if (r < 1)
    {
       fatFsTestERROR( r );
       f_close( &file );
       return false;
    }
    fatFsTestOK( );
    
    // Cierra el archivo
    f_close( &file );
}

static bool fatFsWriteText(const char *nombre_archivo, const char *text)
{
    char buf[1024];
    char filename[64];    
    FIL file;
    FRESULT fr;
    int r;
    
    sprintf( filename, "%s/%s", sdcardDriveName(),nombre_archivo);

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
    
    // Ver http://elm-chan.org/fsw/ff/00index_e.html para una referencia de la
    // API de FatFs
    
    // Abre un archivo. Si no existe lo crea, si existe, me manda el puntero al último para escribir debajo.
    fr = f_open( &file, filename, FA_OPEN_APPEND | FA_WRITE);
    if( fr != FR_OK )
    {
        uartWriteString( UART_USB, "\r\nERROR AL ABRIR ARCHIVO.\r\n" ); 
        fatFsTestERROR( fr );
        return false;
    }
    
    //f_puts
    sprintf (buf, "%s", text);
    
    r = f_puts( buf, &file );
    if (f_error(&file))
    {
       uartWriteString( UART_USB, "\r\nERROR AL ESCRIBIR ARCHIVO.\r\n" ); 
       fatFsTestERROR( r );
       f_close( &file );
       return false;
    }
    fatFsTestOK( );
    
    // Cierra el archivo
    f_close( &file );
    
    return true;
}


static bool fatFs_Add_Buff(const char *text)
{
    char buf[1024];
    char filename[64];    
    FIL file;
    FRESULT fr;
    int r;
    
    sprintf( filename, "%s/BUFF.TXT", sdcardDriveName() );

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
    
    // Ver http://elm-chan.org/fsw/ff/00index_e.html para una referencia de la
    // API de FatFs
    
    // Abre un archivo. Si no existe lo crea, si existe, me manda el puntero al último para escribir debajo.
    fr = f_open( &file, filename, FA_OPEN_APPEND | FA_WRITE);
    if( fr != FR_OK )
    {
        uartWriteString( UART_USB, "\r\nERROR AL ABRIR ARCHIVO.\r\n" ); 
        fatFsTestERROR( fr );
        return false;
    }
    
    //f_puts
    sprintf (buf, "%s", text);
    
    r = f_puts( buf, &file );
    if (f_error(&file))
    {
       uartWriteString( UART_USB, "\r\nERROR AL ESCRIBIR ARCHIVO.\r\n" ); 
       fatFsTestERROR( r );
       f_close( &file );
       return false;
    }
    fatFsTestOK( );
    
    // Cierra el archivo
    f_close( &file );
    
    return true;
}




unsigned int fatFs_Open_and_GetSize(const char *nombre_archivo, char *buffer)
{
    char buf[1024];
    char filename[64];    
    FIL file;
    FRESULT fr;
    int r;
    unsigned int size_of_file, out_bytes;
    bool result;
    
    sprintf( filename, "%s/%s", sdcardDriveName(), nombre_archivo );

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
    
    // Ver http://elm-chan.org/fsw/ff/00index_e.html para una referencia de la
    // API de FatFs
    
    // Abre un archivo. Si no existe lo crea, si existe, me manda el puntero al último para escribir debajo.
    fr = f_open( &file, filename, FA_READ);
    if( fr != FR_OK )
    {
        fatFsTestERROR( fr );
        return false;
    }
    
    size_of_file = f_size(&file);
    
    if(size_of_file > 0)
    {
        //fr = f_read(&fsrc, buffer, sizeof buffer, &br); 
        if(f_read(&file,buffer,(size_of_file+1), &out_bytes) == FR_OK)uartWriteString(UART_USB, "\r\nEl dato ha sido leído correctamente.\r\n");
    
    }
       
    
    fatFsTestOK( );
    
    // Cierra el archivo
    f_close( &file );
    
    uartWriteString(UART_USB, "\r\nEl archivo se cerró correctamente.\r\n");
    
    return size_of_file;
}

static bool Erase_Arch(const char *nombre_archivo)
{
    char buf[1024];
    char filename[64];    
    FIL file;
    FRESULT fr;
    int r;
    
    sprintf( filename, "%s/%s", sdcardDriveName(), nombre_archivo );

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
    
    // Ver http://elm-chan.org/fsw/ff/00index_e.html para una referencia de la
    // API de FatFs
    
    // Abre un archivo. Si no existe lo crea, si existe, lo sobreescribe y lo deja en blanco.
    fr = f_open( &file, filename, FA_CREATE_ALWAYS);
    if( fr != FR_OK )
    {
        uartWriteString( UART_USB, "\r\nERROR AL ABRIR ARCHIVO.\r\n" ); 
        fatFsTestERROR( fr );
        return false;
    }
    
    fatFsTestOK( );
    
    // Cierra el archivo
    f_close( &file );
    
    return true;
}

bool_t Tomar_Config_SD()
{
 
    char buf[1024];
    char buf_aux[50]={0};
    char filename[64];    
    FIL file;
    FRESULT fr;
    int r;
    unsigned int size_of_file, out_bytes;
    bool result;
    char *ptr_inicio;
    char *ptr_final;
    char *ptr_aux;
    
    
    sprintf( filename, "%s/CONFIG.TXT", sdcardDriveName());

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
 
    // Abre un archivo. Si no existe lo crea, si existe, me manda el puntero al último para escribir debajo.
    fr = f_open( &file, filename, FA_READ);
    
    if( fr != FR_OK )
    {
        fatFsTestERROR( fr );
        return false;
    }
    
    size_of_file = f_size(&file);
    
    if(size_of_file > 0)
    {
        //fr = f_read(&fsrc, buffer, sizeof buffer, &br); 
        if(f_read(&file,buf,(size_of_file+1), &out_bytes) == FR_OK)uartWriteString(UART_USB, "\r\nEl dato ha sido leído correctamente.\r\n");
    
    }
    
    // Cierra el archivo
    f_close( &file);

    ptr_inicio = strstr(buf, "=");
    ptr_final = strstr(buf, ";");
    
    for(ptr_aux=(ptr_inicio+1);ptr_aux<(ptr_final);ptr_aux++)buf_aux[ptr_aux-(ptr_inicio+1)] = *ptr_aux;
    strcpy(ssid_wifi,buf_aux);
    memset( buf_aux, '\0', sizeof(buf_aux));
    
    ptr_inicio = strstr((ptr_inicio+1), "=");
    ptr_final = strstr((ptr_final+1), ";");
    
    for(ptr_aux=(ptr_inicio+1);ptr_aux<(ptr_final);ptr_aux++)buf_aux[ptr_aux-(ptr_inicio+1)] = *ptr_aux;
    strcpy(clave_wifi,buf_aux);
    memset( buf_aux, '\0', sizeof(buf_aux)); 
    
    ptr_inicio = strstr((ptr_inicio+1), "=");
    ptr_final = strstr((ptr_final+1), ";");
    
    for(ptr_aux=(ptr_inicio+1);ptr_aux<(ptr_final);ptr_aux++)buf_aux[ptr_aux-(ptr_inicio+1)] = *ptr_aux;
    strcpy(servidor_tcpip,buf_aux);
    memset( buf_aux, '\0', sizeof(buf_aux)); 
    
    ptr_inicio = strstr((ptr_inicio+1), "=");
    ptr_final = strstr((ptr_final+1), ";");
    
    for(ptr_aux=(ptr_inicio+1);ptr_aux<(ptr_final);ptr_aux++)buf_aux[ptr_aux-(ptr_inicio+1)] = *ptr_aux;
    strcpy(puerto_tcpip,buf_aux);
    memset( buf_aux, '\0', sizeof(buf_aux)); 
    
    ptr_inicio = strstr((ptr_inicio+1), "=");
    ptr_final = strstr((ptr_final+1), ";");
    
    for(ptr_aux=(ptr_inicio+1);ptr_aux<(ptr_final);ptr_aux++)buf_aux[ptr_aux-(ptr_inicio+1)] = *ptr_aux;
    strcpy(servidor_ntp,buf_aux);
    memset( buf_aux, '\0', sizeof(buf_aux));
    
     uartWriteString( UART_USB, "\r\nLos datos obtenidos son: \r\n" );
    uartWriteString( UART_USB, "SSID WIFI: " );
    uartWriteString( UART_USB, ssid_wifi );
    uartWriteString( UART_USB, "\r\n" );
    
    uartWriteString( UART_USB, "CLAVE WIFI: " );
    uartWriteString( UART_USB, clave_wifi );
    uartWriteString( UART_USB, "\r\n" );
    
    uartWriteString( UART_USB, "SERVER TCP/IP: " );
    uartWriteString( UART_USB, servidor_tcpip );
    uartWriteString( UART_USB, "\r\n" );
    
    uartWriteString( UART_USB, "PUERTO TCP/IP: " );
    uartWriteString( UART_USB, puerto_tcpip );
    uartWriteString( UART_USB, "\r\n" );
    
    uartWriteString( UART_USB, "SERVIDOR NTP: " );
    uartWriteString( UART_USB, servidor_ntp );
    uartWriteString( UART_USB, "\r\n" );
    
    
}

enum {
    SD_WRITE_WIFI = 0,
    SD_WRITE_SERVER,
    SD_WRITE_SERVER_NTP
    
};

bool_t Escribir_Config_SD(uint8_t sdStateWrite, char* server_ssid, char* puerto_clave)
{
    char buf[1024];
    char filename[64];    
    FIL file;
    FRESULT fr;
    unsigned int size_of_file, out_bytes;

    sprintf( filename, "%s/CONFIG.TXT", sdcardDriveName());

    uartWriteString( UART_USB, "\r\n-------------------------------------------\r\n" );   
    sprintf( buf, "Abriendo archivo: '%s'.\r\n", filename);
    uartWriteString( UART_USB, buf);
    uartWriteString( UART_USB, "-------------------------------------------\r\n" ); 
 
    memset(buf,'\0',sizeof(buf));
    
    // Abre un archivo. Si no existe lo crea, si existe, me manda el puntero al último para escribir debajo.
    fr = f_open( &file, filename, FA_READ);
    if( fr != FR_OK )
    {
        fatFsTestERROR( fr );
        return false;
    }
    
    size_of_file = f_size(&file);
    
    if(size_of_file > 0)
    {
        //fr = f_read(&fsrc, buffer, sizeof buffer, &br); 
        if(f_read(&file,buf,(size_of_file+1), &out_bytes) == FR_OK)uartWriteString(UART_USB, "\r\nEl dato ha sido leído correctamente.\r\n");
    
    }
    
   
    char *ptr_igual = 0;
    char *ptr_punto_coma = 0;
    uint32_t cantEntre = 0;
    
    char buffPrimeraParte[1024];
    char buffSegundaParte[1024];
    
    memset(buffPrimeraParte,'\0',sizeof(buffPrimeraParte));
    memset(buffSegundaParte,'\0',sizeof(buffSegundaParte));
    
    //Lo primero que hago es separar todo lo que hay antes del igual, y todo lo que hay después del punto y coma.  
    //Como las funciones de la biblioteca string.h escapan o retornan con un '\0' (NULL) apreovechamos esto y cambio algunos
    //caracteres por éste para guardar lo que me sirva:
    
    switch(sdStateWrite)
    {
        case   SD_WRITE_WIFI:
            
            //Aislo las dos primeras partes:
            ptr_igual = strstr(buf, "=");
            ptr_punto_coma = strstr(buf, ";");
            ptr_igual++;
            *ptr_igual = '\0';  //Aquí inserto el NULL
            strcpy(buffPrimeraParte,buf);
    
            strcat(buffSegundaParte, ptr_punto_coma);
            
            //Las junto en un buffer mas grande:
            strcat(buffPrimeraParte,server_ssid);
            strcat(buffPrimeraParte,buffSegundaParte);
        
            memset(buf, '\0', sizeof(buf));
        
            strcpy(buf,buffPrimeraParte);
            
            //Ahora buscamos el segundo igual
            ptr_igual = strstr(buf,"clave_wifi =");
            ptr_igual = ptr_igual + 12;
            ptr_punto_coma = strstr(buf,";");
            ptr_punto_coma++;
            ptr_punto_coma = strstr(ptr_punto_coma,";"); //Ya estamos en el segundo punto y coma
            *ptr_igual = '\0';  //Aquí inserto el NULL
            
            memset(buffPrimeraParte,'\0',sizeof(buffPrimeraParte));
            memset(buffSegundaParte,'\0',sizeof(buffSegundaParte));
            
            strcpy(buffPrimeraParte,buf);
            strcpy(buffSegundaParte, ptr_punto_coma);
            
            //Las junto en un buffer mas grande:
            strcat(buffPrimeraParte,puerto_clave);
            strcat(buffPrimeraParte,buffSegundaParte);
           
            if(Erase_Arch("CONFIG.TXT"))uartWriteString(UART_USB, "\r\nArchivo borrado correctamente.\r\n");
            
            if(fatFsWriteText("CONFIG.TXT", buffPrimeraParte))uartWriteString(UART_USB, "\r\nArchivo escrito correctamente.\r\n");
            
                    
        break;  
        
        case   SD_WRITE_SERVER:
                
            //Aislo las dos primeras partes:
            ptr_igual = strstr(buf, "server_tcpip =");
            ptr_punto_coma = strstr(ptr_igual, ";");
            ptr_igual = ptr_igual + 14;
            *ptr_igual = '\0';  //Aquí inserto el NULL
            
            strcpy(buffPrimeraParte,buf);
            strcpy(buffSegundaParte, ptr_punto_coma);
            
            //Las junto en un buffer mas grande:
            strcat(buffPrimeraParte,server_ssid);
            strcat(buffPrimeraParte,buffSegundaParte);
            memset(buf, '\0', sizeof(buf));
            strcpy(buf,buffPrimeraParte);
            
            //Ahora buscamos el segundo igual
            ptr_igual = strstr(buf,"puerto_tcpip =");
            ptr_punto_coma = strstr(ptr_igual,";");
            ptr_igual = ptr_igual + 14;
            *ptr_igual = '\0';  //Aquí inserto el NULL
            
            memset(buffPrimeraParte,'\0',sizeof(buffPrimeraParte));
            memset(buffSegundaParte,'\0',sizeof(buffSegundaParte));
            
            strcpy(buffPrimeraParte,buf);
            strcpy(buffSegundaParte, ptr_punto_coma);
            
            //Las junto en un buffer mas grande:
            strcat(buffPrimeraParte,puerto_clave);
            strcat(buffPrimeraParte,buffSegundaParte);
        
            uartWriteString(UART_USB, "\r\nTodo queda: \r\n");
            uartWriteString(UART_USB, buffPrimeraParte);
     
            if(Erase_Arch("CONFIG.TXT"))uartWriteString(UART_USB, "\r\nArchivo borrado correctamente.\r\n");
            
            if(fatFsWriteText("CONFIG.TXT", buffPrimeraParte))uartWriteString(UART_USB, "\r\nArchivo escrito correctamente.\r\n");
        
        break;
        
        case   SD_WRITE_SERVER_NTP:
                
            //Ahora buscamos el segundo igual
            ptr_igual = strstr(buf,"servidor_ntp =");
            ptr_punto_coma = strstr(ptr_igual,";");
            ptr_igual = ptr_igual + 14;
            *ptr_igual = '\0';  //Aquí inserto el NULL
            
            strcpy(buffPrimeraParte,buf);
            strcpy(buffSegundaParte, ptr_punto_coma);
            
            //Las junto en un buffer mas grande:
            strcat(buffPrimeraParte,server_ssid);
            strcat(buffPrimeraParte,buffSegundaParte);
        
            uartWriteString(UART_USB, "\r\nTodo queda: \r\n");
            uartWriteString(UART_USB, buffPrimeraParte);
     
            if(Erase_Arch("CONFIG.TXT"))uartWriteString(UART_USB, "\r\nArchivo borrado correctamente.\r\n");
            
            if(fatFsWriteText("CONFIG.TXT", buffPrimeraParte))uartWriteString(UART_USB, "\r\nArchivo escrito correctamente.\r\n");
        
        break;
        
    }
    
    // Cierra el archivo
    f_close( &file );
    
}