#include <LiquidCrystal.h> // include the LCD library
 
const int rs = PB12, en = PB13, d4 = PB14, d5 = PB15, d6 = PA8, d7 = PB9; //STM32 Pins to which LCD is connected
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Initialize the LCD
 
void setup() {
lcd.begin(16, 2);//Defining 16*2 LCD
lcd.setCursor(0, 0); //LCD Row 0 and Column 0
lcd.print("Interfacing LCD"); //Print this Line
lcd.setCursor(0, 1); //LCD Row 0 and Column 1
lcd.print("with STM32 Board"); //Print this Line
 
delay(4000); //wait for four secounds
lcd.clear(); //Clear the screen
}
 
void loop() {
 
lcd.setCursor(0, 0); //LCD Row 0 and Column 0
lcd.print(" STM32 with LCD "); //Print This Line
lcd.setCursor(0, 1); //LCD Row 0 and Column 1
lcd.print(millis() / 1000); //Print the value of secounds
}
