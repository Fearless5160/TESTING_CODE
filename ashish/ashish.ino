  const int in1 = PB0;
  const int in2 = PA7;
  const int in3 = PB7;
  const int in4 = PB8;
  const int in11 = PA0;
  const int in21 = PA1;
  const int in31 = PC15;
  const int in41 = PC14;
  const int EN1 = PB6;
  const int EN2 = PA6;
int pwmw = 85;
int percent[5] = {0, 50, 50, 50, 50};
char data;
//
//int motor = 1;
//long HIGH[5] = {0, 32767, 32767, 32767, 32767};

void setup()
{
  // put your setup code here, to run once:

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in11, OUTPUT);
  pinMode(in21, OUTPUT);
  pinMode(in31, OUTPUT);
  pinMode(in41, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial1.println("hello");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in11, LOW);
  digitalWrite(in21, LOW);
  digitalWrite(in31, LOW);
  digitalWrite(in41, LOW);
  analogWrite(EN1, pwmw);
  analogWrite(EN2, pwmw);

}

void loop()
{
   if(Serial2.available() > 0)
   {   
       while(Serial2.available() > 0)
       { 
          data = Serial2.read();  
       }
       Serial1.print("data ");
       Serial1.println(String(data));
 
    switch (data)
    {
      case 'U':

        digitalWrite(in3, HIGH);
        digitalWrite(in4, 0);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, 0);
        digitalWrite(in31, HIGH);
        digitalWrite(in41, 0);
        digitalWrite(in11, HIGH);
        digitalWrite(in21, 0);
        Serial1.print('u');
        // data_check='U';
        break;

      case 'D':
        Serial1.print('d');
        digitalWrite(in3, 0);
        digitalWrite(in4, HIGH);
        digitalWrite(in1, 0);
        digitalWrite(in2, HIGH);
        digitalWrite(in31, 0);
        digitalWrite(in41, HIGH);
        digitalWrite(in11, 0);
        digitalWrite(in21, HIGH);
        //data_check='D';
        break;

      case 'C':
        Serial1.print('C');
        digitalWrite(in3, 0);
        digitalWrite(in4, 0);
        digitalWrite(in1, 0);
        digitalWrite(in2, 0);
        digitalWrite(in31, 0);
        digitalWrite(in41, 0);
        digitalWrite(in11, 0);
        digitalWrite(in21, 0);
        //data_check='C';
        break;

      case 'L':
        Serial1.print('L');
        digitalWrite(in3, HIGH);
        digitalWrite(in4, 0);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, 0);
        digitalWrite(in31, 0);
        digitalWrite(in41, HIGH);
        digitalWrite(in11, 0);
        digitalWrite(in21, HIGH);
        // data_check='L';
        break;

      case 'R':
        Serial1.print('R');
        digitalWrite(in3, 0);
        digitalWrite(in4, HIGH);
        digitalWrite(in1, 0);
        digitalWrite(in2, HIGH);
        digitalWrite(in31, HIGH);
        digitalWrite(in41, 0);
        digitalWrite(in11, HIGH);
        digitalWrite(in21, 0);
        //data_check='R';
        break;
      case 'a':
        if ((pwmw >= 0) && (pwmw <= 254))
        {
          pwmw = pwmw + 85;
          Serial1.print(pwmw);
          analogWrite(EN1, pwmw);
          analogWrite(EN2, pwmw);
        }
        else {
          pwmw == 255;
        }
        break;

      case 'b':
        if ((pwmw >= 1) && (pwmw <= 255)) {
          pwmw = pwmw - 85;
          Serial1.print(pwmw);
          analogWrite(EN1, pwmw);
          analogWrite(EN2, pwmw);
        }
        else {
          pwmw == 0;
        }
      default: break;
    }
    delay(500);

  }
}
