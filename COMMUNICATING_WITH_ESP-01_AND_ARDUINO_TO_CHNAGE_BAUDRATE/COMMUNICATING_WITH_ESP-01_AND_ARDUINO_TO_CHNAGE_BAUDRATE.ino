#include <SoftwareSerial.h>

SoftwareSerial esp8266(7, 8);     // rx,tx for esp8266


void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200);
  esp8266.listen();
}

void loop() 
{
  esp8266.print("AT");
  get_data();
  delay(3000);
  esp8266.print("AT+UART_DEF=9600,8,1,0,0");
  get_data();
  delay(2000);
  while(1);
}

void get_data()
{
  char c;
  String indata = "";
  //  Serial.println(F("data available"));
  while (esp8266.available() > 0)
  {
    c = (char)esp8266.read();
    indata += c;
    Serial.print(c);
    delay(1);
  }
  indata.trim();
    Serial.print("d = ");
    Serial.println(indata);
  return indata;
}
