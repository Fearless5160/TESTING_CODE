#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop()
{
  VL53L0X_RangingMeasurementData_t measure;
  unsigned int measuring_time = 0;
  unsigned int measuring_time2 = 0;
  unsigned int main_time = 0;
  Serial.print("time measurement... ");
  measuring_time = millis();
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  measuring_time2 = millis();
  main_time = measuring_time2 - measuring_time;
  Serial.println(main_time);
  if (measure.RangeStatus != 4) {  
    // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
  float speeds = measure.RangeMilliMeter/main_time;
  Serial.print(speeds);
    
  delay(100);
}
