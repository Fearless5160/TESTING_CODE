int sensorInterrupt = 0;  // interrupt 0
int sensorPin       = 2; //Digital Pin 2
//int solenoidValve = 5; // Digital pin 5
 
/*The hall-effect flow sensor outputs pulses per second per litre/minute of flow.*/
float calibrationFactor = 5; //You can change according to your datasheet
 
volatile byte pulseCount =0;  
 
float flowRate = 0.0;
unsigned int flowMilliLitres =0;
unsigned long totalMilliLitres = 0;
 
unsigned long oldTime = 0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING); //you can use Rising or Falling   
}
 
void loop()
{
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    detachInterrupt(sensorInterrupt);
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
 
    unsigned int frac;
    Serial.print("Flow rate: ");
    Serial.print(flowMilliLitres, DEC);  // Print the integer part of the variable
    Serial.print("mL/Second");
    Serial.print("\t");           
 
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres,DEC);
    Serial.println("mL"); 
    Serial.print("\t");     
        
//    if (totalMilliLitres >= 500)
//    {
//      digitalWrite(13,HIGH);
//      while(1);
//    }
    pulseCount = 0;
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
}
 
void pulseCounter()
{
  pulseCount++;
}
 
