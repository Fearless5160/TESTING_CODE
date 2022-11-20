
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

void setup() {
  Serial.begin(9600);  
}
void loop() {
  // read the sensor on analog A0:
   int s0 = analogRead(A0);
  int s1 = analogRead(A1);
  int s2 = analogRead(A2);
  int s3 = analogRead(A3);
  int s4 = analogRead(A4);
  Serial.print(s0);
  Serial.print("\t");
  Serial.print(s1);
  Serial.print("\t");
  Serial.print(s2);
  Serial.print("\t");
  Serial.print(s3);
  Serial.print("\t");
  Serial.println(s4);

  int direction;
  if ((s0 < 30) && (s1 < 30) && (s2 < 30) && (s3 < 30) && (s4 < 30))
    direction = 0;
//  else if (s2 > 985)
  else if (s2 > 800)
    direction = 6;
  else if ((s0 > s1) && (s0 > s2) && (s0 > s3) && (s0 > s4))
    direction = 1;
  else if ((s1 > s0) && (s1 > s2) && (s1 > s3) && (s1 > s4))
    direction = 2;
  else if ((s2 > s0) && (s2 > s1) && (s2 > s3) && (s2 > s4))
    direction = 3;
  else if ((s3 > s0) && (s3 > s1) && (s3 > s2) && (s3 > s4))
    direction = 4;
  else if ((s4 > s0) && (s4 > s1) && (s4 > s2) && (s4 > s3))
    direction = 5;

  switch (direction) {
    case 0:
      Serial.println("No fire detected");
      delay(200);
      break;

    case 1:
      Serial.println("Right +");
      delay(400);
      break;

    case 2:
      Serial.println("Right");
      delay(200);
      break;

    case 3:
      Serial.println("Forward");
      delay(200);
      break;

    case 4:
      Serial.println("Left");
      delay(200);
      break;

    case 5:
      Serial.println("Left +");
      delay(400);
      break;

    case 6:
      Serial.println("Fire Detected! Launch water cannons!");
      delay(200);

  }
  delay(1000); 
}
