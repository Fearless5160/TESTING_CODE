
#include <SoftwareSerial.h>

SoftwareSerial rfid1(4, 0);
String inputString1 = "";
//String bus_ID = "06004DFDC375";
//String local_ID = "060074016516";
//String metro_ID = "0600747FF7FA";
//String universal_ID = "060073F623A0";

String user_1 = "1000D25650C4";
String user_2 = "1000D1F283B0";
String user_3 = "1000D1F5C9FD";
String user_4 = "1000D1EE7D52";
String user_5 = "1000D2079055";

void setup()
{
  Serial.begin(9600);
  rfid1.begin(9600);   
  Serial.println("test");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  rfid1.listen();
  inputString1 = "";
  while (rfid1.available()) 
  {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = rfid1.read();
    inputString1 += c;
    Serial.println("inputString1");
    Serial.println(inputString1);
  }
//  inputString1.trim();
//  if(user_1 == inputString1)
//  {
//     Serial.println("correct id");
//  }
//  else
//  {
//     inputString1 = "";
//  }

}
