int acc_x;
int acc_y;
int acc_z;

int x, y, z, x_val, y_val, z_val,last_val, val, stability;

void setup()
{
  Serial.begin(250000);
//  x_val = checkstabiliy(A0);
//  y_val = checkstabiliy(A1);
//  z_val = checkstabiliy(A2);
}
void loop()
{
  acc_x = analogRead(A0);
  x = acc_x - 336;
  acc_y = analogRead(A1);
  y = acc_y - 386;
  acc_z= analogRead(A2);
  y = acc_z - 256;
  Serial.print( "x=");
  Serial.println(x);
  Serial.print( "y=");
  Serial.println(y);
  Serial.print( "Z=");
  Serial.println(z);
  delay(0.001);
}

int checkstabiliy(int pinNo)
{
  last_val = 0, stability = 0;
  val = analogRead(pinNo);
  last_val = val;
  while (stability < 4)
  {
    val = analogRead(pinNo);
    Serial.println(val);
    delay(100);
    stability++;
    if (((val - last_val) < -5) || ((val - last_val) > 5))
    {
      stability = 0;
      last_val = val;
    }
  }
  Serial.print(pinNo);
  Serial.print(" stability=");
  Serial.println(val);

  stability = 0;
  return val;
}
