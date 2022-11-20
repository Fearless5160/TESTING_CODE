// Arduino with PCF8574T I2C LCD example
 
#include <Wire.h>                  // Include Wire library (required for I2C devices)
#include <LiquidCrystal_I2C.h>     // Include LiquidCrystal_I2C library 
 
//LiquidCrystal_I2C lcd(0x20,20,4);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
 LiquidCrystal_I2C lcd(0x20,16,2);  // Configure LiquidCrystal_I2C library with 0x27 address, 16 columns and 2 rows
void setup() {
 
  lcd.init();                        // Initialize I2C LCD module
 
  lcd.backlight();                   // Turn backlight ON
 
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(2,1);
  lcd.print("Ywrobot Arduino!");
   lcd.setCursor(0,2);
  lcd.print("Arduino LCM IIC 2004");
   lcd.setCursor(2,3);
  lcd.print("Power By Ec-yuan!");
 
}
 
void loop() {
 
}
