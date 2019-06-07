/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/SerialEvent
*/

int byteRcv;
int numero;
unsigned long int tiempo_set;

unsigned long int baudrate[7]={
          9600,
          19200,
          38400, 
          57600,
          74880,
          115200,
          230400,
};
int baud_rate_ch=0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  baud_rate_ch = 0;
  Serial1.begin(baudrate[baud_rate_ch]);
  Serial.print("Se inicia correctamente el ARDUINO... \n");
  Serial.print("El baud rate es: ");
  Serial.print(baudrate[baud_rate_ch]);
  Serial.print(" \n");
  
}

void loop() {

if(millis()-tiempo_set > 30000)
{
  baud_rate_ch++;
  Serial1.begin(baudrate[baud_rate_ch]);
  Serial.print("El baud rate es: ");
  Serial.print(baudrate[baud_rate_ch]);
  Serial.print(" \n");
  tiempo_set = millis();
}


if(Serial1.available())
{
  byteRcv = Serial1.read();
  Serial.print(byteRcv);
  Serial.print(" \n");
}

}
