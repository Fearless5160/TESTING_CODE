/*----------------------------------------------------------
    MH-Z19 CO2 sensor  SAMPLE
  ----------------------------------------------------------*/

#include "MHZ19.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

const int rx_pin = 10; //Serial rx pin no
const int tx_pin = 11; //Serial tx pin no

//const int pwmpin = 7;

MHZ19 *mhz19_uart = new MHZ19(rx_pin,tx_pin);
//MHZ19 *mhz19_pwm = new MHZ19(pwmpin);

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup()
{
    Serial.begin(115200);
    mhz19_uart->begin(rx_pin, tx_pin);
    mhz19_uart->setAutoCalibration(false);
    delay(3000);
    Serial.print("MH-Z19 now warming up...  status:");
    Serial.println(mhz19_uart->getStatus());
   
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)  i.e display initiallize
  delay(1000);
  display.clearDisplay();//clear display
  display.setTextSize(1);//setting size of text to 1
  display.setTextColor(WHITE);// text color white
  display.setCursor(0, 0);// set cursor at o location of 
  display.setTextColor(BLACK, WHITE);
  display.println("       START     ");
  display.display();
   delay(1000);
}

/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop()
{
    measurement_t m = mhz19_uart->getMeasurement();

    Serial.print("co21: ");
    Serial.println(m.co2_ppm);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("CO2 value: ");
  display.print(m.co2_ppm);
  display.println("ppm");
  display.display();
  delay(5000);
}
