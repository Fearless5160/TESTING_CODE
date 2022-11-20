
int ldr = A0;
int aval = 0;
void setup() 
{
  // put your setup code here, to run once:
    Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  int val = analogRead(ldr);
  Serial.println(val);
  aval = map(val, 0, 1023, 150, 0);
  Serial.println(aval);
  delay(1000);
}
