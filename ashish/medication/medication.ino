#include <Keypad.h>
#include <DS1307RTC.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 13, A0, A1, A2, A3);

const byte ROWS = 4; // Four rows
const byte COLS = 3; // three columns
char keys[ROWS][COLS] =
{ {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = { 5, 6, 7, 8 };
byte colPins[COLS] = { 9, 10, 11 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned int user_time[5];
tmElements_t tm;

bool key_press = false;
unsigned int hours;
unsigned int mins;

unsigned int dose;
String dose_time[2];
//String medicine_name[4] = {"Paracetamol", "Azithromycin", "Pantoprazole", "Amoxicillin"};
String user_dosage1[3];
String user_dosage2[3];
String user_dosage3[3];
unsigned int total_medicine1;
unsigned int total_medicine2;
unsigned int total_medicine3;
int key_med1 = 0; 
int key_med2 = 0;
int key_med3 = 0; 
int key_med4 = 0;
int key_med5 = 0;
int key_med6 = 0; 
int key_med7 = 0;

int buzz = 2;
int led = 3;

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(buzz, LOW);
  digitalWrite(led, HIGH);
  lcd.clear();
  lcd.print(F("    Programmable"));
  lcd.setCursor(0, 1);
  lcd.print(F(" Medication Reminder"));
  lcd.setCursor(0, 2);
  lcd.print(F("       System "));
  delay(2000);
  get_time();
  set_time(hours, mins);
  lcd.clear();
  lcd.print(F("1. Start"));
  lcd.setCursor(0, 1);
  lcd.print(F("2. Set Reminder"));
}


void loop()
{
  int key = get_key();
  if (key == 1) 
  {
    key_press = false;
    if (dose == 1)
    {
      alarm(dose_time[0], total_medicine1, 1);
      dose = 0;
      total_medicine1 = 0;
      total_medicine2 = 0;
      total_medicine3 = 0;
      //      String user_dosage[2];
    }
    else if (dose == 2)
    {
      alarm( dose_time[0], total_medicine1, 1);
      delay(500);
      alarm( dose_time[1], total_medicine2, 2);
      dose = 0;
      total_medicine1 = 0;
      total_medicine2 = 0;
      total_medicine3 = 0;
    }
    else if (dose == 3)
    {
      alarm( dose_time[0], total_medicine1, 1);
      delay(500);
      alarm( dose_time[1], total_medicine2, 2);
      delay(500);
      alarm( dose_time[2], total_medicine3, 3);
      dose = 0;
      total_medicine1 = 0;
      total_medicine2 = 0;
      total_medicine3 = 0;
    }
    else 
    {
      lcd.clear();
      lcd.print(F("Please Set Reminder"));
      delay(2000);
    }
  }
  if (key == 2) 
  {
    key_press = false;
    get_dosage();
    if (dose == 1)
    {
      lcd.clear();
      lcd.print(F("Set Time for Dosage1"));
      lcd.setCursor(2, 1);
      lcd.print(F(":"));
      lcd.setCursor(0, 3);
      lcd.print(F("* = Remove # = Enter"));
      lcd.setCursor(0, 1);
      dose_time[0] = get_dose_time();
      delay(1000);
      lcd.clear();
      lcd.print(F("Choose Medicine &"));
      lcd.setCursor(0, 1);
      lcd.print(F("Press # to Select"));
      key_med1 = 0;
      delay(1000);
      key_press = false;
      medicine_display();
      while(key_press == false)
      {
         key_med1 =  get_key2();
      }
     delay(1000);
     key_press = false;
     if (key_med1 == 1) 
     {
        lcd.clear();
        lcd.print(F("You Choose:"));
        lcd.setCursor(0, 1);
        lcd.print(F("Paracetamol"));
        delay(1000);
        user_dosage1[total_medicine1] = "Paracetamol";
        total_medicine1++;
      }
      if (key_med1 == 2) 
      {
        lcd.clear();
        lcd.print(F("You Choose:"));
        lcd.setCursor(0, 1);
        lcd.print(F("Azithromycin"));
        delay(1000);
        user_dosage1[total_medicine1] = "Azithromycin";
        total_medicine1++;
      }
      if (key_med1 == 3)
      {
         lcd.clear();
         lcd.print(F("You Choose:"));
         lcd.setCursor(0, 1);
         lcd.print(F("Pantoprazole"));
         delay(1000);
         user_dosage1[total_medicine1] = "Pantoprazole";
         total_medicine1++;
       }
       if (key_med1 == 4)
       {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Amoxicillin"));
          delay(1000);
          user_dosage1[total_medicine1] = "Amoxicillin";
          total_medicine1++;
        }
        delay(1000);
        key_med1 = 0;
    }
    else if (dose == 2)
    {
      lcd.clear();
      lcd.print(F("Set Time for Dosage1"));
      lcd.setCursor(2, 1);
      lcd.print(F(":"));
      lcd.setCursor(0, 3);
      lcd.print(F("* = Remove # = Enter"));
      lcd.setCursor(0, 1);
      dose_time[0] = get_dose_time();
      lcd.clear();
      lcd.print(F("Choose Medicine &"));
      lcd.setCursor(0, 1);
      lcd.print(F("Press # to Select"));
      delay(1000);
      key_press = false;
      medicine_display();
      while(key_press == false)
      {
         key_med1 =  get_key2();
      }
     delay(1000);
     key_press = false;
        if (key_med1 == 1) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Paracetamol"));
          delay(1000);
          user_dosage1[total_medicine1] = "Paracetamol";
          total_medicine1++;
        }
        if (key_med1 == 2) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Azithromycin"));
          delay(1000);
          user_dosage1[total_medicine1] = "Azithromycin";
          total_medicine1++;
        }
        if (key_med1 == 3) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Pantoprazole"));
          delay(1000);
          user_dosage1[total_medicine1] = "Pantoprazole";
          total_medicine1++;
        }
        if (key_med1 == 4) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Amoxicillin"));
          delay(1000);
          user_dosage1[total_medicine1] = "Amoxicillin";
          total_medicine1++;
        }
      delay(1000);
      key_med1 = 0;
      lcd.clear();
      lcd.print(F("Set Time for Dosage2"));
      lcd.setCursor(2, 1);
      lcd.print(F(":"));
      lcd.setCursor(0, 3);
      lcd.print(F("* = Remove # = Enter"));
      lcd.setCursor(0, 1);
      dose_time[1] = get_dose_time();
      lcd.clear();
      lcd.print(F("Choose Medicine &"));
      lcd.setCursor(0, 1);
      lcd.print(F("Press # to Select"));
       delay(1000);
      key_press = false;
      medicine_display();
      while(key_press == false)
      {
         key_med2 =  get_key2();
      }
     delay(1000);
      key_press = false;
        if (key_med2 == 1) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Paracetamol"));
          delay(1000);
          user_dosage2[total_medicine2] = "Paracetamol";
          total_medicine2++;
        }
        if (key_med2 == 2) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Azithromycin"));
          delay(1000);
          user_dosage2[total_medicine2] = "Azithromycin";
          total_medicine2++;
        }
        if (key_med2 == 3) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Pantoprazole"));
          delay(1000);
          user_dosage2[total_medicine2] = "Pantoprazole";
          total_medicine2++;
        }
        if (key_med2 == 4) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Amoxicillin"));
          delay(1000);
          user_dosage2[total_medicine2] = "Amoxicillin";
          total_medicine2++;
        }
        delay(1000);
        key_med2 = 0;
        
    }
    else if (dose == 3) {
      lcd.clear();
      lcd.print(F("Set Time for Dosage1"));
      lcd.setCursor(2, 1);
      lcd.print(F(":"));
      lcd.setCursor(0, 3);
      lcd.print(F("* = Remove # = Enter"));
      lcd.setCursor(0, 1);
      dose_time[0] = get_dose_time();
      lcd.clear();
      lcd.print(F("Choose Medicine &"));
      lcd.setCursor(0, 1);
      lcd.print(F("Press # to Select"));
      delay(1000);
      key_press = false;
      medicine_display();
      while(key_press == false)
      {
         key_med1 =  get_key2();
      }
     delay(1000);
     key_press = false;
        if (key_med1 == 1) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Paracetamol"));
          delay(1000);
          user_dosage1[total_medicine1] = "Paracetamol";
          total_medicine1++;
        }
        if (key_med1 == 2) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Azithromycin"));
          delay(1000);
          user_dosage1[total_medicine1] = "Azithromycin";
          total_medicine1++;
        }
        if (key_med1 == 3) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Pantoprazole"));
          delay(1000);
          user_dosage1[total_medicine1] = "Pantoprazole";
          total_medicine1++;
        }
        if (key_med1 == 4) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Amoxicillin"));
          delay(1000);
          user_dosage1[total_medicine1] = "Amoxicillin";
          total_medicine1++;
        }
      delay(1000);
      key_med1 = 0;
      lcd.clear();
      lcd.print(F("Set Time for Dosage2"));
      lcd.setCursor(2, 1);
      lcd.print(F(":"));
      lcd.setCursor(0, 3);
      lcd.print(F("* = Remove # = Enter"));
      lcd.setCursor(0, 1);
      dose_time[1] = get_dose_time();
      lcd.clear();
      lcd.print(F("Choose Medicine &"));
      lcd.setCursor(0, 1);
      lcd.print(F("Press # to Select"));
       delay(1000);
      key_press = false;
      medicine_display();
      while(key_press == false)
      {
         key_med2 =  get_key2();
      }
     delay(1000);
      key_press = false;
        if (key_med2 == 1) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Paracetamol"));
          delay(1000);
          user_dosage2[total_medicine2] = "Paracetamol";
          total_medicine2++;
        }
        if (key_med2 == 2) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Azithromycin"));
          delay(1000);
          user_dosage2[total_medicine2] = "Azithromycin";
          total_medicine2++;
        }
        if (key_med2 == 3) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Pantoprazole"));
          delay(1000);
          user_dosage2[total_medicine2] = "Pantoprazole";
          total_medicine2++;
        }
        if (key_med2 == 4) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Amoxicillin"));
          delay(1000);
          user_dosage2[total_medicine2] = "Amoxicillin";
          total_medicine2++;
        }
        delay(1000);
        key_med2 = 0;
      lcd.clear();
      lcd.print(F("Set Time for Dosage3"));
      lcd.setCursor(2, 1);
      lcd.print(F(":"));
      lcd.setCursor(0, 3);
      lcd.print(F("* = Remove # = Enter"));
      lcd.setCursor(0, 1);
      dose_time[2] = get_dose_time();
      lcd.clear();
      lcd.print(F("Choose Medicine &"));
      lcd.setCursor(0, 1);
      lcd.print(F("Press # to Select"));
      delay(1000);
      key_press = false;
      medicine_display();
      while(key_press == false)
      {
         key_med3 =  get_key2();
      }
      delay(1000);
      key_press = false;
          if (key_med3 == 1) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Paracetamol"));
          delay(1000);
          user_dosage3[total_medicine3] = "Paracetamol";
          total_medicine3++;
          medicine_display();
        }
        if (key_med3 == 2) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Azithromycin"));
          delay(1000);
          user_dosage3[total_medicine3] = "Azithromycin";
          total_medicine3++;
          medicine_display();
        }
        if (key_med3 == 3) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Pantoprazole"));
          delay(1000);
          user_dosage3[total_medicine3] = "Pantoprazole";
          total_medicine3++;
          medicine_display();
        }
        if (key_med3 == 4) {
          lcd.clear();
          lcd.print(F("You Choose:"));
          lcd.setCursor(0, 1);
          lcd.print(F("Amoxicillin"));
          delay(1000);
          user_dosage3[total_medicine3] = "Amoxicillin";
          total_medicine3++;
          medicine_display();
        }
        delay(1000);
        key_med3 = 0;
      }
    }
    lcd.clear();
    lcd.print(F("1. Start"));
    lcd.setCursor(0, 1);
    lcd.print(F("2. Set Reminder"));
}

void medicine_display() {
  lcd.clear();
  lcd.print(F("1. Paracetamol"));
  lcd.setCursor(0, 1);
  lcd.print(F("2. Azithromycin"));
  lcd.setCursor(0, 2);
  lcd.print(F("3. Pantoprazole"));
  lcd.setCursor(0, 3);
  lcd.print(F("4. Amoxicillin"));
}

void get_dosage() {
  key_press = false;
  int key;
  lcd.clear();
  lcd.print(F("Enter No. of Dosage"));
  lcd.setCursor(0, 1);
  lcd.print(F("per day: "));
  lcd.setCursor(0, 3);
  lcd.print(F("# = Enter"));
  while (1) {
    key = get_key();
    if (key_press) {
      if (key <= 3 && key != 0) {
        key_press = false;
        lcd.setCursor(9, 1);
        lcd.print((key));
        dose = key;
      }
      if (key == 11)
      {
        break;
      }
    }
  }
}


void set_time(int Hours, int Min) {
  tm.Hour = Hours;
  tm.Minute = Min;
  tm.Second = 0;
  RTC.write(tm);
}

String get_dose_time()
{
  bool valid_time = false;
  while (valid_time == false) {
    int counter = 0;
    while (1) {
      int key = get_key();
      if (key_press) {
        key_press = false;
        if (counter == 2 && key != 10) {
          user_time[counter] = 0;
          counter++;
        }
        if (key <= 9) {
          lcd.setCursor(counter, 1);
          lcd.print((key));
          if (counter != 2) {
            user_time[counter] = key;
          }
          counter++;
          if (counter >= 5) {
            counter = 5;
          }
        }
        else if (key == 10) {
          key_press = false;
          counter--;
          user_time[counter] = 0;
          lcd.setCursor(counter, 1);
          lcd.print(F(" "));
          lcd.setCursor(2, 1);
          lcd.print(F(":"));
        }
        else if (key == 11) {
          key_press = false;
          break;
        }
      }
    }
    String dose_hour = String(user_time[0]) + String(user_time[1]);
    String dose_min = String(user_time[3]) + String(user_time[4]);
    String dose_time = dose_hour + ":" + dose_min;
    return dose_time;
  }
}
int get_time() {
  lcd.clear();
  bool valid_time = false;
  while (valid_time == false) {
    lcd.setCursor(0, 0);
    lcd.print(F("Please Enter Time:"));
    lcd.setCursor(2, 1);
    lcd.print(F(":"));
    lcd.setCursor(0, 2);
    lcd.print(F("24 Hours Clk Format"));
    lcd.setCursor(0, 3);
    lcd.print(F("* = Remove # = Enter"));
    lcd.setCursor(0, 1);
    int counter = 0;
    while (1) {
      int key = get_key();
      if (key_press) {
        key_press = false;
        if (counter == 2 && key != 10) {
          user_time[counter] = 0;
          counter++;
        }
        if (key <= 9) {
          lcd.setCursor(counter, 1);
          lcd.print((key));
          if (counter != 2) {
            user_time[counter] = key;
          }
          counter++;
          if (counter >= 5) {
            counter = 5;
          }
        }
        else if (key == 10) {
          key_press = false;
          counter--;
          user_time[counter] = 0;
          lcd.setCursor(counter, 1);
          lcd.print(F(" "));
          lcd.setCursor(2, 1);
          lcd.print(F(":"));
        }
        else if (key == 11) {
          key_press = false;
          break;
        }
      }
    }
    String user_hour = String(user_time[0]) + String(user_time[1]);
    String user_min = String(user_time[3]) + String(user_time[4]);
    int HOUR = user_hour.toInt();
    int MIN = user_min.toInt();
    if (MIN == 60) {
      MIN = 00;
    }
    if (HOUR > 24 || MIN > 59) {
      valid_time = false;
      lcd.clear();
      lcd.print(F("Pls Enter Valid Time"));
      delay(1000);
      lcd.clear();
    }
    else {
      hours = HOUR;
      mins = MIN;
      valid_time = true;
    }
  }
}

 int get_key2()
{
  char key = keypad.getKey();
  delay(100);
  switch (key) 
  {
    case '1':
      key_press = true;
      return 1;
      break;
    case '2':
      key_press = true;
      return 2;
      break;
    case '3':
      key_press = true;
      return 3;
      break;
    case '4':
      key_press = true;
      return 4;
      break;
//   default:
//      key_press = false;
//      break;
  }
}

int get_key() {
  char key = keypad.getKey();
  delay(100);
  switch (key) {
    case '1':
      key_press = true;
      return 1;
      break;
    case '2':
      key_press = true;
      return 2;
      break;
    case '3':
      key_press = true;
      return 3;
      break;
    case '4':
      key_press = true;
      return 4;
      break;
    case '5':
      key_press = true;
      return 5;
      break;
    case '6':
      key_press = true;
      return 6;
      break;
    case '7':
      key_press = true;
      return 7;
      break;
    case '8':
      key_press = true;
      return 8;
    case '9':
      key_press = true;
      return 9;
      break;
    case '0':
      key_press = true;
      return 0;
      break;
    case '*':
      key_press = true;
      return 10;
      break;
    case '#':
      key_press = true;
      return 11;
    default:
      key_press = false;
      break;
  }
}

void alarm(String med_time, int total_med, int dose_num) {
  String medicine_time;
  while (1) {
    if (RTC.read(tm)) {
      int  hh = tm.Hour;
      int  mn = tm.Minute;
      int  sec = tm.Second;
      String ho = (hh < 10) ? "0" + String(hh) : String(hh);
      String Min1 = (mn < 10) ? "0" + String(mn) : String(mn);
      lcd.clear();
      lcd.print(F("Clock Time:"));
      lcd.setCursor(0, 1);
      lcd.print((ho));
      lcd.print(F(":"));
      lcd.print((Min1));
      lcd.print(F(":"));
      lcd.print((sec));
            lcd.setCursor(0, 2);
            lcd.print(F("Medicine Time is: "));
            lcd.setCursor(0, 3);
            lcd.print((med_time));
      medicine_time = String(ho) + ":" + String(Min1);
    }
    if (medicine_time ==  med_time) {
      digitalWrite(buzz, HIGH);
      digitalWrite(led, LOW);
      lcd.clear();
      for (int i = 0 ; i < total_med; i++) {
        if (dose_num == 1) {
          lcd.setCursor(0, i);
          lcd.print((user_dosage1[i]));
        }
        else if (dose_num == 2) {
          lcd.setCursor(0, i);
          lcd.print((user_dosage2[i]));
        }
        else if (dose_num == 3) {
          lcd.setCursor(0, i);
          lcd.print((user_dosage3[i]));
        }
      }
      delay(10000);
      digitalWrite(buzz, LOW);
      digitalWrite(led, HIGH);
      break;
    }
    delay(1000);
  }
}
