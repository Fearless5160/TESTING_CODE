
#include <Wire.h>

#define addr_1 20
#define addr_2 39

int i2c_counter = 0;
byte c;
byte x;

const unsigned int i2c_bulb[15] = {255, 254, 252, 248, 240, 224, 192, 128, 000, 255, 254, 252, 248, 240, 000};

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("start");
}

void loop()
{

  for (int i2c_counter = 0; i2c_counter <= 8; i2c_counter++)
  {
    i2c_led(i2c_counter, addr_1);
    Serial.print("////////////////// i2c_counter = ");
    Serial.println(i2c_counter);
    Serial.print("////////////////// addr_ = ");
    Serial.println(addr_1);

  }

  for (int i2c_counter = 9; i2c_counter <= 14; i2c_counter++)
  {
    i2c_led(i2c_counter, addr_2);
    Serial.print("////////////////// i2c_counter = ");
    Serial.println(i2c_counter);
    Serial.print("////////////////// addr_ = ");
    Serial.println(addr_2);
  }

  for (int i2c_counter = 14; i2c_counter >= 9; i2c_counter--)
  {
    i2c_led(i2c_counter, addr_2);
    Serial.print("////////////////// i2c_counter = ");
    Serial.println(i2c_counter);
    Serial.print("////////////////// addr_ = ");
    Serial.println(addr_2);
  }

  for (int i2c_counter = 8; i2c_counter >= 0; i2c_counter--)
  {
    i2c_led(i2c_counter, addr_1);
    Serial.print("////////////////// i2c_counter = ");
    Serial.println(i2c_counter);
    Serial.print("////////////////// addr_ = ");
    Serial.println(addr_1);
  }
}

void i2c_led(int d, int addr )
{
  x = i2c_bulb[d];
  Wire.beginTransmission(addr); // transmit to device #38
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(2000);
}
