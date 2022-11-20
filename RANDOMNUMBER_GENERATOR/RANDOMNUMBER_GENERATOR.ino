long randNumber;

void setup() 
{
  Serial.begin(9600);
  randomSeed(1000);
}

void loop()
{
  randNumber = random(9999);
  Serial.println(randNumber);
  delay(50);
}
