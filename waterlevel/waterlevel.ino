
const int water_level = A3;
unsigned int w_level = 0;

void setup() 
{
  Serial.begin(9600);
  Serial.println("TEST START");
  pinMode(water_level,INPUT);
  
}

void loop()
{
   unsigned int level = analogRead(water_level);
   Serial.print("level  ");
   Serial.println(level);
   w_level = map(level,0,530,0,6);
   Serial.print("w_level  ");
   Serial.println(w_level);
   delay(2000);
}
