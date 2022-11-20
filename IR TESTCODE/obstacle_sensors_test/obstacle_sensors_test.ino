
//const int IR2 =  2;
const int IR3 =  3;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
//  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT_PULLUP);
  delay(2000);
}

void loop() 
{
  // put your main code here, to run repeatedly:

//  if (digitalRead(IR2) == LOW)
//  {
//    Serial.println("Object detected first module!");
//    delay(1000);
//  }

  if (digitalRead(IR3) == HIGH)
  {
    Serial.println("Object detected second module!");
    delay(1000);
  }
}
