#include <SoftwareSerial.h>
SoftwareSerial XBee(A5, A4);

void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  { 
    XBee.write(Serial.read());
  }
  if (XBee.available())
  { 
    Serial.write(XBee.read());
  }
}
