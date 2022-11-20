 #include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() 
{
  myservo.attach(11);  // attaches the servo on pin 6 to the servo object

  delay(10000);
}

void loop()
{
//  myservo.attach(11); 
//  myservo.write(100);
//  delay(1000);
//  myservo.write(200);
//  delay(1000);
  for (pos = 0; pos <= 180; pos += 1)
  { 
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                          // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) 
  { 
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
