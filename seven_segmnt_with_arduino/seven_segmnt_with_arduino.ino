//
//const int dsp1 = 9;
//const int dsp2 = A0;
//
//int limit = 0;
//int ds1 = 0;
//int ds2 = 0;
//
//int num_array[10][7] = {  { 0,0,0,0,0,1,0 },    // 0  (a,b,c,d,e,f,g) f is middle horizontal line
//                          { 1,0,0,1,1,1,1 },    // 1
//                          { 0,0,1,0,0,0,1 },    // 2
//                          { 0,0,0,0,1,0,1 },    // 3
//                          { 1,0,0,1,1,0,0 },    // 4
//                          { 0,1,0,0,1,0,0 },    // 5
//                          { 0,1,0,0,0,0,0 },    // 6
//                          { 0,0,0,1,1,1,1 },    // 7
//                          { 0,0,0,0,0,0,0 },    // 8
//                          { 0,0,0,0,1,0,0 }};   // 9
//                                       
//void Num_Write(int);
//
//void setup()
//{
//  Serial.begin(9600);
//  Serial.println("test");
//  pinMode(dsp1,OUTPUT);
//  pinMode(dsp2,OUTPUT);
//  pinMode(2,OUTPUT);
//  pinMode(3,OUTPUT);
//  pinMode(4,OUTPUT);
//  pinMode(5,OUTPUT);
//  pinMode(6,OUTPUT);
//  pinMode(7,OUTPUT);
//  pinMode(8,OUTPUT);
//
//  digitalWrite(dsp1,HIGH);
//  digitalWrite(dsp2,HIGH);
//  Num_Write(ds1);
//}
//
//void loop() 
//{
//    up_counter();
//    delay(1000);
////    down_counter();
////    delay(5000);
//   
//}
//
//void up_counter()
//{
//  Num_Write(ds1);
//  ds2++;
//  Num_Write1(ds2);
//  if(ds2 >= 9)
//  {
//     ds2 = 0;
//     ds1 = 1;
//     
//  }
//}
//
//void down_counter()
//{
//
//}
//
//
//void Num_Write(int number) 
//{ 
////  digitalWrite(dsp2,LOW);
//  digitalWrite(dsp1,HIGH);
//  int pin= 2;
//  for (int j=0; j < 7; j++)
//  {
//    digitalWrite(pin, num_array[number][j]);
//    pin++;
//  }
//}
//
//void Num_Write1(int number) 
//{
////  digitalWrite(dsp1,LOW);
//  digitalWrite(dsp2,HIGH);
//  
//  int pin= 2;
//  for (int j=0; j < 7; j++)
//  {
//    digitalWrite(pin, num_array[number][j]);
//    pin++;
//  }
//}

int num_array[10][7] = {  { 0,0,0,0,0,1,0 },    // 0  (a,b,c,d,e,f,g) f is middle horizontal line
                          { 1,0,0,1,1,1,1 },    // 1
                          { 0,0,1,0,0,0,1 },    // 2
                          { 0,0,0,0,1,0,1 },    // 3
                          { 1,0,0,1,1,0,0 },    // 4
                          { 0,1,0,0,1,0,0 },    // 5
                          { 0,1,0,0,0,0,0 },    // 6
                          { 0,0,0,1,1,1,1 },    // 7
                          { 0,0,0,0,0,0,0 },    // 8
                          { 0,0,0,0,1,0,0 }};   // 9
                                       
void Num_Write(int);
// common pins of the four digits definitions
#define Dig1    9
#define Dig2   A0

#define SegA   2
#define SegB   3
#define SegC   4
#define SegD   5
#define SegE   6
#define SegF   7
#define SegG   8
// variable declarations
byte current_digit;
int  count = 0;
 
void setup()
{
  pinMode(SegA, OUTPUT);
  pinMode(SegB, OUTPUT);
  pinMode(SegC, OUTPUT);
  pinMode(SegD, OUTPUT);
  pinMode(SegE, OUTPUT);
  pinMode(SegF, OUTPUT);
  pinMode(SegG, OUTPUT);
  pinMode(Dig1, OUTPUT);
  pinMode(Dig2, OUTPUT);
 
  disp_off();  // turn off the display
 
  // Timer1 module overflow interrupt configuration
  TCCR1A = 0;
  TCCR1B = 1;  // enable Timer1 with prescaler = 1 ( 16 ticks each 1 µs)
  TCNT1  = 0;  // set Timer1 preload value to 0 (reset)
  TIMSK1 = 1;  // enable Timer1 overflow interrupt
 
}
 
ISR(TIMER1_OVF_vect)   // Timer1 interrupt service routine (ISR)
{
  disp_off();  // turn off the display
  switch (current_digit)
  {
    case 1:
      disp((count / 10) % 10);   // prepare to display digit 3
      digitalWrite(Dig1, HIGH);    // turn on digit 3
      break;
 
    case 2:
      disp(count % 10);   // prepare to display digit 4 (most right)
      digitalWrite(Dig2, HIGH);  // turn on digit 4
  }
  current_digit = (current_digit % 2) + 1;
}
 
// main loop
void loop()
{
    count++;  // increment 'count' by 1
    if(count >= 99)
      count = 0;
    delay(1000);  // wait 200 milliseconds

}
 
void disp(byte number)
{
  switch (number)
  {
    case 0:  // print 0
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, LOW);
      break;
 
    case 1:  // print 1
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, HIGH);
      break;
      
    case 2:  // print 2
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, HIGH);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, HIGH);
      break;
 
    case 3:  // print 3
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, HIGH);
      break;

    case 4:  // print 4
      digitalWrite(SegA, HIGH);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, LOW);
      break;
 
    case 5:  // print 5
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, LOW);
      break;
      
    case 6:  // print 6
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, HIGH);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, LOW);
      break;
    
    case 7:  // print 7
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, HIGH);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, HIGH);
      digitalWrite(SegG, HIGH);
      break;
 
    case 8:  // print 8
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, LOW);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, LOW);
      break;
 
    case 9:  // print 9
      digitalWrite(SegA, LOW);
      digitalWrite(SegB, LOW);
      digitalWrite(SegC, LOW);
      digitalWrite(SegD, LOW);
      digitalWrite(SegE, HIGH);
      digitalWrite(SegF, LOW);
      digitalWrite(SegG, LOW);
  }
} 

void disp_off()
{
   digitalWrite(Dig1, LOW);
   digitalWrite(Dig2, LOW);
}
 
