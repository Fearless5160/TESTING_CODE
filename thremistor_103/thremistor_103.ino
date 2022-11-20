#include <LiquidCrystal.h>

const int temp_pin = A5;
unsigned int value = 0;
float cel;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
   lcd.begin(16,2);
   Serial.begin(115200);
   pinMode(temp_pin,INPUT);
   delay(2000);
}

void loop()
{
  float next_val = 0.00;
  for (int t  = 0; t < 1000; t++)
  {
    float prev_val = analogRead(temp_pin);
    Serial.println(prev_val);
    next_val = next_val + prev_val ;
  }
  value = (next_val / 10000);     // depend on value of resistor use in ckt
  float mv = (value / 1024.0) * 5000;
  cel = (mv / 2.5);
  Serial.print("temperature: ");
  Serial.print(cel);
  Serial.println("C");
  lcd.print(cel);
  delay(2000);  
}
//#include <math.h>
//
//unsigned int Rs = 150000;
//double Vcc = 3.3;
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(115200);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//
//  Serial.println(Thermister(AnalogRead()));
//  delay(1000);
//
//}
//
//int AnalogRead() {
//  int val = 0;
//  for(int i = 0; i < 20; i++) {
//    val += analogRead(A0);
//    delay(1);
//  }
//
//  val = val / 20;
//  return val;
//}
//
//double Thermister(int val) {
//  double V_NTC = (double)val / 1024;
//  double R_NTC = (Rs * V_NTC) / (Vcc - V_NTC);
//  R_NTC = log(R_NTC);
//  double Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * R_NTC * R_NTC ))* R_NTC );
//  Temp = Temp - 273.15;         
//  return Temp;
//
//}
