#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial myserial(13, 12);  // RX,TX
LiquidCrystal lcd(6, 7, 8, 11, 10, 9);
String data_pressure;
char  buff[15];

int sensorValue = 0;
int tempVal = 0; 

int sys_l = 50, sys_u = 90, dia_l = 40, dia_u = 80, temp_l = 25, temp_u = 33, pulse_l = 40, pulse_u = 50;
int sys, dia, p,  stay = 1;

void setup() 
{
  Serial.begin(9600);
  myserial.begin(9600);
  pinMode(A4, OUTPUT);
  digitalWrite(A4,HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print(F("  COVID Patient "));
  lcd.setCursor(0, 1);
  lcd.print(F(" Health  Monitor "));
  delay(2000);
  lcd.clear();
}

void loop()
{
   Serial.println("press on");
   lcd.clear();
   lcd.print(F("    press on    "));
   delay(200);
   myserial.listen();
   
   if (myserial.available())
   {
     while (myserial.available())
     {
       data_pressure = myserial.readString();
     }
     data_pressure.trim();
     data_pressure.toCharArray(buff, data_pressure.length() + 1);
     if (sscanf(buff, "%d,%d,%d", &sys, &dia, &p) == 3)
     {   
         Serial.print("sys :");
         Serial.println(sys);
         Serial.print("dia :");
         Serial.println(dia);
         Serial.print("p :");
         Serial.println(p);   
         lcd.clear();
         lcd.print(F("sys | dia | puls"));
         lcd.setCursor(0, 1);
         lcd.print(sys);
         lcd.setCursor(7, 1);
         lcd.print(dia);
         lcd.setCursor(12, 1);
         lcd.print(p);     
         delay(5000);         
     }
     myserial.end();
   }
   
}
