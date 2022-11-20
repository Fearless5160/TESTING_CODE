#include <SoftwareSerial.h>

String tag;
byte get_tag[60];
char buff[60];
String rfid_tag = "";
String last_rfid_tag = "";
String serial_receiving_data = "";

SoftwareSerial rfid(6, 7);
SoftwareSerial usb(9, 10);
unsigned long prev_millis = 0;
unsigned char received_flag = 0;

void setup()
{
  Serial.begin(9600);
  rfid.begin(9600);
  Serial.println("Start");
  delay(2000);
  prev_millis = millis();
}

void loop()
{     
    rfid.begin(9600);
    if (rfid.available() > 0)
    {
      Serial.println("here data1");
      rfid_tag =  rfid.readString();
      Serial.print( "rfid_tag = " + String(rfid_tag));
    }
    if(received_flag == 1)
    {
       rfid.print(serial_receiving_data);
       received_flag = 0;
    }
    if (last_rfid_tag != rfid_tag) 
    {
      last_rfid_tag = rfid_tag;
      usb.begin(9600);
      Serial.println("rfid_tag match");
      usb.print(rfid_tag);
      while (usb.available() <= 0)
      {
         Serial.println("waiting");
      };
      if(usb.available() > 0)
      {
         serial_receiving_data = usb.readString();
         Serial.print( "serial_receiving_data = " + String(serial_receiving_data));
         received_flag = 1;
      }
      usb.end();
    }
   delay(1000);
}
