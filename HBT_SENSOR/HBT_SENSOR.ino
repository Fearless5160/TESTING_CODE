
#define hbt_sensor A0
int  beats=0;
long time1;
long time2;
int last_rate;

void setup() 
{
  Serial.begin(9600);
  pinMode(hbt_sensor,INPUT);
  Serial.println("START");
  delay(1000);
}

void loop()
{
  int k=0;
  long t_out1 = millis();
  bool zero = false;
  while(k < 10)
  {
    if(digitalRead(hbt_sensor))
    {     
      t_out1 = millis();
      if(k == 0)
      time1 = millis();
      k++;
      while(digitalRead(hbt_sensor));
    }
    if(millis() - t_out1 > 2000)
    {
      zero = true;
      break;
    }
  }
  if(!zero)
  {
    time2 = millis();
    beats = time2-time1;
    beats = beats/10;
    beats = 60000/beats;
    if(beats >= 200)
    {
      beats = last_rate;
    } 
  }
  else
  {
    k=0;
    beats=0;
  }
  Serial.print(F("Beats/minute: "));
  Serial.print(beats);
  Serial.println("   ");
  last_rate = beats;     
  k=0;
}
