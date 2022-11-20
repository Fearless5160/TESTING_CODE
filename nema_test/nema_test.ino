#include<mwc_stepper.h>

#define EN_PIN 0
#define DIR_PIN 7
#define STEP_PIN 6

#define PULSE 3000
#define ClOCKWISE 0 
#define OTHERWISE 1

int RPM = 90;
int step_angle = 350;

MWCSTEPPER nema23(EN_PIN, DIR_PIN, STEP_PIN);

void setup() 
{
    nema23.init();
}

void loop() 
{
  nema23.set(ClOCKWISE, RPM, PULSE);
  for(int j = 0;j<20;j++)
  {
    for (size_t i = 0; i < step_angle; i++)
    {
      nema23.run();
    }
  }
  delay(250);
  nema23.set(OTHERWISE, RPM, PULSE);
  for(int k = 0;k<20;k++)
  {
    for (size_t i = 0; i < step_angle; i++)
    {
      nema23.run();
    }
  }
  delay(250);
}
