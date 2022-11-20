
//-1
String data  = "";
//String blue_data  = "";
//
//String select_load = "";
////String brightness = "";
//char brightness[10];
//String start_time;
//String end_time;
//int index1;
//int index2;
//
void setup() 
{
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial1.println("ATcommand");  //ATcommand Start
}

void loop()
{
   if(Serial2.available() > 0)
   {   
       while(Serial2.available() > 0)
       { 
         data = Serial2.readString();  
       }
       Serial1.print("data ");
       Serial1.println(String(data));
//       blue_data = data;
//       data = "";
//       select_load = blue_data.substring(1,2);
////       Serial.print("select_load  ");
////       Serial.println(select_load);
//       if (select_load == "1")
//       {
//         Serial.println("LOAD");
//         char data_arr[25];
//         blue_data.toCharArray(data_arr, blue_data.length() + 1);
//         Serial.println("data_char: " + String(data_arr));
//         sscanf(data_arr, "$1*%[^#]#", &brightness);
//         Serial.println("brightness: " + String(brightness));
//         String temp = String(brightness);
//         Serial.println("temp: " + temp);
//         if (temp.indexOf('*') >= 0)
//         {
////             Serial.println("here");
//             sscanf(data_arr, "$1*%[^*],%[^*],%[^#]#", &brightness);
//             String checky = blue_data.substring(5,6);
////             Serial.println("checky : " + String(checky));
//             if(checky == "*")
//             {
//                 start_time = blue_data.substring(6,11);
//                 end_time = blue_data.substring(12,17);
//                 Serial.println("brightness 2: " + String(brightness));
//                 Serial.println("start_time : " + start_time);
//                 Serial.println("end_time : " + end_time);
//             }
//             else
//             {
//                 start_time = blue_data.substring(7,12);
//                 end_time = blue_data.substring(13,18);
//                 Serial.println("brightness 3 : " + String(brightness));
//                 Serial.println("start_time : " + start_time);
//                 Serial.println("end_time : " + end_time);
//             }
//         }
//         else
//         {
//            Serial.println("brightness main: " + String(brightness));
//         }
//      }
//      if (select_load == "2")
//      {
//         Serial.println("fan");
//         char data_arr[25];
//         blue_data.toCharArray(data_arr, blue_data.length() + 1);
//         Serial.println("data_char: " + String(data_arr));
//         sscanf(data_arr, "$2*%[^#]#", &brightness);
//         Serial.println("brightness: " + String(brightness));
//      }
////      if(blue_data.indexOf('*') >= 0)
////      {
////         index1 = blue_data.indexOf('*');
////         
////         brightness = blue_data.substring(3,5);
////         Serial.print("select_load  ");
////         Serial.println(select_load);
////         Serial.print("brightness  ");
////         Serial.println(brightness);
////      }
//       
   }
}
/*
USB(mega2560)-to-BLE sketch

Apploader project
http://www.apploader.info

Anton Smirnov
2015

Note:
  HM-10 applies baud rate set in 'AT+BAUD' after switch off and on
*/

//int led = 13;
//int ledHIGH = 0;
//
//long bauds[] =
//{
//    // major 
//    9600, 57600, 115200,
//    
//    // others
//    19200, 38400, 4800, 2400, 1200, 230400
//  };
//
//bool detectBleBaudRate() {
//  Serial.println("Detecting BLE baud rate:");
//  for (int i=0; i<(sizeof(bauds)/sizeof(long)); i++) {
//    Serial.write("Checking ");
//    long cur_baud = bauds[i];
//    Serial.println(cur_baud, DEC);
//    
//    Serial2.begin(cur_baud);
//    Serial2.write("AT");
//    Serial2.flush();
//    delay(50);
//    String response = Serial2.readString();
//    if (response == "OK")
//    {
//      Serial.println("Detected");
//      return true;
//    } else
//    {
//      Serial2.end();
//    }
//  }
//  return false;
//}
//
//void setup() 
//{
//  // init
//  Serial.begin(115200);  // USB (choose 115200 in terminal)
//  
//  if (detectBleBaudRate())
//    Serial.write("Ready, type AT commands\n\n");
//  else
//    Serial.write("Not ready. Halt");
//  
//  pinMode(led, OUTPUT);
//}
//
//void loop() {
//  // read from BLE (HM-10)
//  if (Serial2.available()) {
//    Serial.write("ble: ");
//    String str = Serial1.readString();
//    Serial.print(str);
//    Serial.write('\n');
//  }
//
//  // read from USB (Arduino Terminal)
//  if (Serial.available()) {
//    Serial.write("usb: ");
//    String str = Serial.readString();
//    Serial2.print(str);
//    Serial.print(str);
//    Serial.write('\n');
//  }
//}
//////  Mega analogWrite() test
//////
//////  This sketch fades LEDs up and down one at a time on digital pins 2 through 13.
//////
//////  This sketch was written for the Arduino Mega, and will not work on other boards.
//////
//////  The circuit:
//////
//////  - LEDs attached from pins 2 through 13 to ground.
//////
//////  created 8 Feb 2009
//////
//////  by Tom Igoe
//////
//////  This example code is in the public domain.
//////
//////  http://www.arduino.cc/en/Tutorial/AnalogWriteMega
//////
//////*/
////
////// These constants won't change. They're used to give names to the pins used:
////
////const int lowestPin = 9;
//////
//////const int highestPin = 8;
////
////void setup() {
////
////  // set pins 2 through 13 as outputs:
////    pinMode(lowestPin, OUTPUT);
//////    pinMode(highestPin, OUTPUT);
////}
////
////void loop() 
////{
////
////  // iterate over the pins:
////
//////  for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++)
//////{
////
////    // fade the LED on thisPin from off to brightest:
//////      analogWrite(lowestPin, 255);
////    for (int brightness = 0; brightness < 255; brightness++)
////    {
////
////      analogWrite(lowestPin, brightness);
////
////      delay(1000);
////
////    }
//////
//////    // fade the LED on thisPin from brightest to off:
//////
//////    for (int brightness = 255; brightness >= 0; brightness--) 
//////    {
//////
//////      analogWrite(lowestPin, brightness);
//////
//////      delay(1000);
//////
//////    }
////
////    // pause between LEDs:
////
////    delay(100);
////
//////    }
////}
