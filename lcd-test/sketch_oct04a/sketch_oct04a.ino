#include <Wire.h>                      
#include <LiquidCrystal_I2C.h>       

LiquidCrystal_I2C lcd(0x3F,20,4);     

void setup()

{

  lcd.init();                    

  // Print a message to the LCD.

  lcd.backlight();                

  lcd.setCursor(0,0);           

  lcd.print("Hello!");

  lcd.setCursor(0,1);             

  lcd.print("Funny!");

  lcd.setCursor(3,2);            

  lcd.print("Enjoy!");

  lcd.setCursor(8,3);             

  lcd.print("Arduino!");



}

void loop()
{

}
