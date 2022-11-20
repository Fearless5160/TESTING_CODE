
#include "PCF8574.h"
// SDA - Yellow - 4
// CLK - White - 5
//#define trigPin 0

#define SDA_PIN 4
#define CLK_PIN 5
#define PCF8574_ADDRESS (0x20)

PCF8574 myPCF8574(PCF8574_ADDRESS);
int counter = 0;
int dir = 1;

long duration;
int distance;

void setup()
{
  Serial.begin(115200);
  myPCF8574.begin(SDA_PIN,CLK_PIN,PCF8574_ADDRESS);
}

// The loop function is called in an endless loop
void loop()
{
  myPCF8574.write(2, LOW); 
  delayMicroseconds(2);
 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  myPCF8574.write(2, HIGH);
   delayMicroseconds(10);
  myPCF8574.write(2, LOW) ;
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(myPCF8574.read(1), HIGH);
  distance = duration/58;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
//  
  delay(1500);
//   myPCF8574.write(2, HIGH); 
//   delay(1000);
//   myPCF8574.write(2, LOW); 
//   delay(1000);
//  counter = myPCF8574.read(2);
//  Serial.print("counter : ");
//  Serial.println(counter);
//  delay(1000);
 
}
