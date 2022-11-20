#include <SoftwareSerial.h>
SoftwareSerial blue(6, 7);   //Rx,Tx

const int bluetooth_state_pin = 15;

String data;
bool got_flag = 0;
void setup() 
{
  Serial.begin(9600);
  blue.begin(9600);
//  blue.print("AT+CONA020000000000\n\r");    //50:8C:B1:73:B3:84 // AT+CONA7CEC7945E3F9  //7CEC7945955E
//  delay(4000);
  blue.listen();
  while (!digitalRead(3))
  {
    Serial.println("  Please Pair your Bluetooth   ");
    delay(1000);
  }
  Serial.print("   Connected to Bluetooth");
  delay(2000);
}

void loop()
{
  blue.listen();
  if (blue.available() > 0)
  {
     while(blue.available() > 0)
     {
        data = (blue.readString());
     }
     Serial.println("received: " + String (data));
     got_flag = 1;
  }
  delay(500);
  blue.begin(9600);
  if(got_flag == 1)
  {
    got_flag = 0; 
    blue.print("Got data \n"); 
//    blue.print(data); 
    data = "";
//    got_flag = 0; 
  }
//  if (data.length() >= 0)
//  {
//    if (data.indexOf("C") >= 0) {
//      data = "";
//      while (1) 
//      {
//        while (blue.available() > 0)
//        {
//          data = blue.readString();
//        }
//        if (data.indexOf("U") >= 0) {
//          Serial.print("enter U  ");
//        }
//        if (data.indexOf("L") >= 0) {
//           Serial.print("enter L ");
//        }
//        if (data.indexOf("D") >= 0) {
//          Serial.print("enter D  ");
//        }
//        if (data.indexOf("R") >= 0) {
//           Serial.print("enter R  ");
//        }
//        if (data.indexOf("C") >= 0)
//        {
//          data = "";
//          break;
//        }
//      }
//    }
//  }
}
