
#include <SoftwareSerial.h>

SoftwareSerial BT(11,10);

void setup()
{
       Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
       BT.begin(9600);   // opens serial port 1, sets data rate to 9600 bps
       delay(3000);
       BT.print("AT+CONA7CEC7945955E\n\r");    //50:8C:B1:73:B3:84 // AT+CONA7CEC7945E3F9  //7CEC7945955E  //AT+CONA5E954579EC7C
}

void loop() {

  if (BT.available() > 0)
  {
    Serial.write(BT.read());    //read data from Bluetooth and send it to USB
  }
}
