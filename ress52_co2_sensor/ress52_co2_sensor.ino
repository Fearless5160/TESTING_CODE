#include "CO2Sensor.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>//include

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
byte value;
byte valueall[15];
char valuechar[15];
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

CO2Sensor co2Sensor(A1, 0.99, 100);

void setup() {
  Serial.begin(9600);
  Serial.println("=== Initialized ===");
  co2Sensor.calibrate();

//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)  i.e display initiallize
//  delay(1000);
//  display.clearDisplay();//clear display
//  display.setTextSize(1);//setting size of text to 1
//  display.setTextColor(WHITE);// text color white
//  display.setCursor(0, 0);// set cursor at o location of 
//  display.setTextColor(BLACK, WHITE);
//  display.println("       START     ");
//  display.display();
}

void loop() {
  int val = co2Sensor.read();
  Serial.print("CO2 value: ");
  Serial.print(val);
  Serial.println("ppm ");
  
//  display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(WHITE);
//  display.setCursor(0, 0);
//  display.print("CO2 value: ");
//  display.print(val);
//  display.println("ppm");
//  display.display();
  delay(500);
}
