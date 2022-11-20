#include <LiquidCrystal.h>


LiquidCrystal lcd(5, 4, 3, 2, 1, 0);

void setup()
{
   lcd.begin(16, 2);
   Serial.begin(9600);
   lcd.clear();
   lcd.print(" LCD TESTED ");
   lcd.setCursor(0, 1);
   lcd.print("     OK     ");
   
   
   delay(1000);
}

void loop()
{
  lcd.print(" DONE ");
//  lcd.clear();
  delay(1000);
}
