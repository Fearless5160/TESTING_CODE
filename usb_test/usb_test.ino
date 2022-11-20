#include <SoftwareSerial.h>

SoftwareSerial usb(8, 7);

void setup()
{
   usb.begin(9600);
   Serial.println("start");
}

void loop()
{
   usb.write("test");
   delay(3000);
}
