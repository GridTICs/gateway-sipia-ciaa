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

char byteRcv;
int numero;
unsigned long int tiempo_set;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  tiempo_set = millis();
}

void loop() {

if(millis()-tiempo_set > 30000)
{
      Serial.print("Mande el paquete N° ");
      Serial.print(numero);
      Serial.println(" hacia la EDU-CIAA.");
      
      Serial1.print("Hi, i am Arduino!!! El numero es: ");
      Serial1.print(numero);
      Serial1.print("\r\n");
      
      numero++;

      tiempo_set = millis();
}

if(Serial2.available())
{
  byteRcv = Serial2.read();
  Serial.print(byteRcv);
}

}