#include <SoftwareSerial.h>

char get_tag[60];
SoftwareSerial sens(10,11);

union int_char
{
   unsigned int int_val;
   unsigned char char_val[2];
}O2,flow;

void setup()
{
   Serial.begin(9600);
   sens.begin(9600);
}

void loop()
{
  int i = 0;
  while (sens.available() > 0)
  {
    get_tag[i++] = sens.read();
  }
  O2.char_val[1] = get_tag[3];
  O2.char_val[0] = get_tag[4];
  flow.char_val[1] = get_tag[5];
  flow.char_val[0] = get_tag[6];
  Serial.print("O2: ");
  Serial.println(O2.int_val);
  Serial.print("flow: ");
  Serial.println(flow.int_val);
  delay(2000);
}
