void setup()
{
Serial.begin(9600);
Serial1.begin(115200);
pinMode(5, OUTPUT);
digitalWrite(5, LOW);

for(int i=0;i<=200;i++)
{
delay(50);
Serial1.println("AT+");
}

digitalWrite(5, HIGH);
delay(1000);
digitalWrite(5, LOW);
Serial.println("RESET Complete");
delay(1000);
Serial1.

println("AT");
}

void loop()
{
if(Serial.available() > 0)
{
Serial1.write(Serial.read());
}

if(Serial1.

available() > 0)
{
Serial.write(Serial1.read());
}

}
