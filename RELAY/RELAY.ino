const int relay = 3;

void setup() {
pinMode(relay, OUTPUT);
digitalWrite(relay, LOW);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(relay, HIGH);
  delay(5000);
  digitalWrite(relay, LOW);
  delay(5000);
  // put your main code here, to run repeatedly:

}
