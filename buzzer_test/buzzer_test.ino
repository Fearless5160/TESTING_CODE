

#define help_tone buzz, 2000, 200
const int buzz = A4;
void setup() 
{
   pinMode(buzz, OUTPUT);

}

void loop() 
{
   digitalWrite(buzz,LOW);
   delay(2000);
   digitalWrite(buzz,HIGH);
   delay(2000);
}
