#include <SoftwareSerial.h>
#include <TimerOne.h>

int M21 = A0;   // arm motors
int M22 = A1;
int M23 = A2;
int M24 = A3;

int M11 = 11;   // vehicle motor
int M12 = 10;
int M13 = 9;
int M14 = 8;

SoftwareSerial blue(3, 2);   //bluetooth rx,tx

volatile String data;

void timer_function()
{
    interrupts();
    if(blue.available() > 0)
    {
        data = blue.readString();
    }
}

void setup()
{
  Serial.begin(9600);
  blue.begin(9600);
  
  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M13, OUTPUT);
  pinMode(M14, OUTPUT);

  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);
  pinMode(M23, OUTPUT);
  pinMode(M24, OUTPUT);
  
  digitalWrite(M11, LOW);
  digitalWrite(M12, LOW);
  digitalWrite(M13, LOW);
  digitalWrite(M14, LOW);
  
  digitalWrite(M21, LOW);
  digitalWrite(M22, LOW);
  digitalWrite(M23, LOW);
  digitalWrite(M24, LOW);
  delay(2000);
  Timer1.initialize(100000); // 150ms
  Timer1.attachInterrupt(timer_function);
}

void loop()
{
      while (1) 
      {
        if (data.indexOf("U") >= 0)
        {
           forward();
        }
        if (data.indexOf("L") >= 0)
        {
           left();
        }
        if (data.indexOf("D") >= 0) 
        {
           backward(); 
        }
        if (data.indexOf("R") >= 0)
        {
            right();
        }
        if (data.indexOf("a") >= 0)
        {
           arm_up();
        }
        if (data.indexOf("b") >= 0)
        {
           arm_down();
        }
        if (data.indexOf("c") >= 0) 
        {
           arm_open();
        }
        if (data.indexOf("d") >= 0)
        {
            arm_close();
        }
        if (data.indexOf("C") >= 0)
        {
            all_stop();
        }
      }
}

void forward()
{
  Serial.println("forward");
  digitalWrite(M11, LOW);
  digitalWrite(M12, HIGH);
  digitalWrite(M13, HIGH);
  digitalWrite(M14, LOW);
}

void backward()
{
  Serial.println("backward");
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M13, LOW);
  digitalWrite(M14, HIGH); 
}

void left()
{
  Serial.println("left");
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M13, HIGH);
  digitalWrite(M14, LOW);
}

void right()
{
  Serial.println("right");
  digitalWrite(M11, LOW);
  digitalWrite(M12, HIGH);
  digitalWrite(M13, LOW);
  digitalWrite(M14, HIGH);
}

void all_stop()
{
  Serial.println("stop");
  digitalWrite(M11, LOW);
  digitalWrite(M12, LOW);
  digitalWrite(M13, LOW);
  digitalWrite(M14, LOW);
  
  digitalWrite(M21, LOW);
  digitalWrite(M22, LOW);
  digitalWrite(M23, LOW);
  digitalWrite(M24, LOW);
}

void arm_down()
{
  Serial.println("down");
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  digitalWrite(M23, LOW);
  digitalWrite(M24, LOW);
}

void arm_up()
{
  Serial.println("up");
  digitalWrite(M21, LOW);
  digitalWrite(M22, HIGH);
  digitalWrite(M23, LOW);
  digitalWrite(M24, LOW);
}

void arm_open()
{
  Serial.println("open");
  digitalWrite(M21, LOW);
  digitalWrite(M22, LOW);
  digitalWrite(M23, HIGH);
  digitalWrite(M24, LOW);
}

void arm_close()
{
  Serial.println("close");
  digitalWrite(M21, LOW);
  digitalWrite(M22, LOW);
  digitalWrite(M23, LOW);
  digitalWrite(M24, HIGH);
}
