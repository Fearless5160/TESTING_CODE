#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>  //include
//including libraries

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
SoftwareSerial BT(10,11); // software serial RX, TX

//defining variables
String bluedata;
//String command;
byte value;
byte valueall[15];
char valuechar[15];

void setup()  
{
  pinMode(10, OUTPUT);    //def pin no. 10 as output
  digitalWrite(10, HIGH);// setting it high
  Serial.begin(9600);// init uart at 9600 buadrate
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  Serial.println("START");
  BT.begin(9600);    //software serial begin at 38400 buadrate
  delay(3000);
//  BT.print("AT+CONA00025BB410A7\n\r");    //50:8C:B1:73:B3:84 // AT+CONA7CEC7945E3F9
  BT.print("AT+CONA7CEC7945E3F9\n\r");  
  delay(4000);
  BT.print("AT+CONN\n\r");    //50:8C:B1:73:B3:84 // AT+CONA7CEC7945E3F9  //7CEC7945955E 00025BB410A7  7A014BB52000
  delay(4000);
}
void loop()
{
  if (BT.available())  //check if bluetooth data available
  {
    delay(100);
    while (BT.available())//if data available stay in this loop
    {
      value = (BT.read());// read data
      
      if (value == 43 || value == 45)///here we check whether the value is  positive or negative
      {
        for (int i = 0; i <= 15; i++)
        {
          valueall[i] = value;
          value = (BT.read());
        }
        int a = 0;
        String value = ((char*)valueall);// convert the char array to string
        for (a = 0; a <= 15; a++) {
          valuechar[a] = valueall[a];
        }
        
        if (((valueall[9] == 64) || (valueall[9] == 0)) && (valueall[10] == 128) )//if valueall[10] ==128 , then its voltage measurement 
        {
          Serial.println("Volts");
        }
        else if ( ((valueall[9] == 32) || (valueall[9] == 16) || (valueall[9] == 0)) && (valueall[10] == 32)) //if valueall[10] ==' ', then its Continuity Test
        {
          Serial.println("Continuity Test");
        }
        else if ( ((valueall[9] == 64) || (valueall[9] == 128) || (valueall[9] == 0) ) && (valueall[10] == 64)) {//if valueall[10] =='@', then its current  measurement
          Serial.println("Current");
        }
        else if ((valueall[9] == 0 && ((valueall[10] == 2) ) || (valueall[10] == 1)) ) {//if valueall[10] =='lf'or 'STX' , then its temperature  measurement
          Serial.println("Tempurature");
        }
        else if (((valueall[9] == 32) || (valueall[9] == 16) || (valueall[9] == 0)) && valueall[10] == 8)//if valueall[10] =='BACKSPACE' OR 'BS' , then its frequency  measurement
        { Serial.println("Frequency");
        }
        else if (valueall[10] == 0) {//if valueall[10] =='' , then its duty cycle
          Serial.println("Duty Cycle");
        }
        else {//IF NONE OF ABOVE THE HFE MEASUREMENT 
          Serial.println("hFE");//if valueall[9] ==' ',''or 'del' , then its hfe
        }

        
      
        if (valuechar[0] == 43 && valueall[7] == 49)  {//IF valuechar[0] == +  THEN VALUE IS POSITIVE
          Serial.print("+");
        }
        else if (valuechar[0] == 45 && valueall[7] == 49) {//IF valuechar[0] == - THEN VALUE IS NEGATIVE
          Serial.print("-");
        }
        else if (valuechar[0] == 43 && valueall[7] == 41) {//  THEN ITS POSITIVE  AC VALUE 
          Serial.print("~");
        }
        else if (valuechar[0] == 45 && valueall[7] == 41) {// THEN ITS NEGATIVE  AC VALUE
          Serial.print("~");
        }
        // SIMILARLY THIS FOR CURRENT
        else if (valuechar[0] == 43 && valueall[7] == 17) {
          Serial.print("+");
        }
        else if (valuechar[0] == 45 && valueall[7] == 17) {
          Serial.print("-");
        }
        else if (valuechar[0] == 43 && valueall[7] == 9) {
          Serial.print("~");
        }
        else if (valuechar[0] == 45 && valueall[7] == 9) {
          Serial.print("~");
        }
        // WHERE TO DISPLAY DECIMAL POINT
        Serial.print(valuechar[1]);
        if (valueall[6] == 49) {
          Serial.print(".");
        }
        Serial.print(valuechar[2]);
        if (valueall[6] == 50) {
          Serial.print(".");
        }
        Serial.print(valuechar[3]);
        if (valueall[6] == 52) {
          Serial.print(".");
        }
        Serial.println(valuechar[4]);

        ///  IF valueall[10] == 128 ITS VOLTAGE
        if (valueall[9] == 64 && valueall[10] == 128) {//valueall[9] == 64 ITS IN MILLIS-VOLTS
          Serial.print("mV");
        }
        else if (valueall[9] == 0 && valueall[10] == 128) {//valueall[9] == 0 ITS IN VOLTS
          Serial.print("V");
        }
//        IF  valueall[10] == 32 ITS RESISTOR
        else if (valueall[9] == 0 && valueall[10] == 32) {// ITS IN OHMS
          Serial.print("R");
        }
        else if (valueall[9] == 32 && valueall[10] == 32) {//ITS IN KILO OHMS
          Serial.print("K");
        }
        else if (valueall[9] == 16 && valueall[10] == 32) {// ITS IN MEGA OHMS
         Serial.print("M");
        }
//        IF valueall[10] == 64 ITS CURRENT 
        else if (valueall[9] == 0 && valueall[10] == 64) {// ITS IN AMP
          Serial.print("A");
        }
        else if (valueall[9] == 64 && valueall[10] == 64) {// ITS IN MILLI-AMP
          Serial.print("mA");
        }
        else if (valueall[9] == 128 && valueall[10] == 64) {// ITS IN MICRO-AMP
          Serial.print("uA");
        }
//     IF   valueall[10] == 2  ITS TEMPERATURE IN 
        else if (valueall[9] == 0 && valueall[10] == 2) {// ITS IN DEGREE CELSIUS 
          Serial.print("Grad C");
        }
        else if (valueall[9] == 0 && valueall[10] == 1) {// ITS IN FAHRENHEIT
          Serial.print("Grad F");
        }
   //     IF   valueall[10] == 8  ITS FREQUENCY IN      
        else if (valueall[9] == 32 && valueall[10] == 8) {//ITS IN KHz
          Serial.print("KHz");
        }
        else if (valueall[9] == 16 && valueall[10] == 8) {//ITS IN Mhz
          Serial.print("MHz");
        }
        else if (valueall[9] == 0 && valueall[10] == 8) {//ITS IN Hz
          Serial.print("Hz");
        }
        else if (valueall[10] == 0) {//its duty cycle
          Serial.print("%");
        }
      }
    }
  }
}
