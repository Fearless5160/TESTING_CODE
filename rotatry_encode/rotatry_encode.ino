
#define SW PB15
#define DT PA8
#define CLK  PA9

byte counter = 0;
byte currentStateCLK;
byte lastStateCLK;
bool CountChange;
byte icount;
byte dcount;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("START");
  /************* Setting INPUT/OUTPUT *************/
  pinMode(SW, INPUT_PULLUP);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);
  lastStateCLK = digitalRead(CLK);
}

void loop()
{
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK)
  {
    bool DTVal = digitalRead(DT);
    if (DTVal != currentStateCLK)
    {
      // Encoder is rotating CCW
      icount ++;
    }
    else
    {
      // Encoder is rotating CW
      icount--;
    }
    Serial.print("Position: ");
    Serial.println(icount);
  }
//    if(icount >= 3)
//    {
//      icount = 0;
//      counter ++;
//      CountChange = true;
//    }
//    else if(dcount >= 3)
//    {
//      dcount = 0;
//      if(counter <= 0 && counter == 255) 
//      { 
//        counter = 0; 
//      }
//      else  
//      {
//        counter --;
//      }
//      CountChange = true;
//    }
//    else 
//    {
//      CountChange = false; 
//    }   
//  }
//  else 
//  {
//    CountChange = false; 
//  }
   lastStateCLK = currentStateCLK;
  
}



//#define outputA 6
//#define outputB 7
//
//
//int counter = 0; 
//int aState;
//int aLastState;  
// 
// 
//void setup() 
//{ 
//   pinMode (outputA,INPUT);
//   pinMode (outputB,INPUT);
//   
//   Serial.begin (9600);
//   aLastState = digitalRead(outputA);   
//} 
// 
//void loop()
//{ 
//   aState = digitalRead(outputA); // Reads the "current" state of the outputA
//   // If the previous and the current state of the outputA are different, that means a Pulse has occured
//   if (aState != aLastState)
//   {     
//     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
//     if (digitalRead(outputB) != aState) 
//     { 
//       counter ++;
//     } 
//     else 
//     {
//       counter --;
//     }
//     Serial.print("Position: ");
//     Serial.println(counter);
//   } 
//   aLastState = aState; // Updates the previous state of the outputA with the current state
//}
