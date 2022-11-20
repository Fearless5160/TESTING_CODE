//#include <SoftwareSerial.h>

////////////////////////////////////////////////////////////////ultrasonic obstacle detection variables///////////////////////////////////////
#define config_sms  "This number is configured."
#define user_cut_call  "USER cut the call"
#define USER_not_Answering  "USER not Answering call..."
#define call_establish  "call establish.."
#define disconnecting_call  "disconnecting call"
#define cant_make_CALL  "can't make CALL"
#define  ERROR_str "ERROR"

#define RECEIVINGCALL 1
#define IDLE 2
#define BUSY 3
#define NO_ANSWER 4
#define TALKING 5
#define ERROR 6

char date1[10];
char time1[10];
char hr1[3];
char min1[3];

#define Pin "pin"
#define ok "OK"
#define ERROR_str "ERROR"
#define Connected "Connected"
#define Connecting "connecting"
#define CLCC "+CLCC:"
#define atCLCC "AT+CLCC"
#define CMGF "AT+CMGF=1"
#define CMGL "+CMGL:"
#define CMGS "AT+CMGS=\""
#define CMGD "AT+CMGD="
#define UNREAD "AT+CMGL=\"REC UNREAD\""
#define CMGDA "AT+CMGD=0,4"
#define CNMI "AT+CNMI=0,0,0,0"
#define CLIP "+CLIP"

boolean gsm_connect = false;
String numtel;
int no_configured = 0;
String indata = "";
String num = "";
unsigned long current_time ;
String msg = "";
String inputString = "";
String msg_index;
int index1;
int index2;
String call_number;
String sms_num, sms; // = get_sender_number();
String lat = "";
String lon = "";
String site = "\nhttp://maps.google.com/maps?f=q&q=";

float lat_int = 0.0000;
float lon_int = 0.0000;
const int gsm_power = 5;

//SoftwareSerial Serial2(13, 12);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin (9600);
  Serial2.begin(115200);
//  pinMode(gsm_power,OUTPUT);
//  digitalWrite(gsm_power,HIGH);
//  delay(500);
//  digitalWrite(gsm_power,LOW);
//  delay(500);

  Serial.println("connecting");
  exicute_cmd(F("AT"), "OK", 5000);
  delay(1000);  
//  delay(20000);

  if (connect_gsm())
  {
    Serial.println(F("GSM Connected.."));
    delay(1000);
  }
  else
  {
    Serial.println(F("not connected"));
    delay(1000);
//    while (1);
  }
   while (!get_network_status())
  {
    Serial.println("Waiting");
    Serial.println("for Network ");
    delay(100);
  }
  Serial.println(F("network register"));
  int no_configured = 0;
  while (!no_configured)
  {
    switch (call_status())
    {
      case IDLE: // Nothing is happening
        break;

      case RECEIVINGCALL: // Yes! Someone is calling us
        delay(500);
        hangcall();
        delay(10000);
        numtel = get_call_number();
        delay(2000);
        Serial.print(F("Receiving call"));
        Serial.print(numtel);
        delay(500);
        numtel = numtel;
        sendsms(F("This number configured as USER"), numtel);
        Serial.print(F("SMS sent.."));
        no_configured = 1;
    }
  }
  delay(3000);
  gps_track();
}

void loop()
{
  

}

void gps_track()
{
  int z = 0;
  Serial.print(F("Tracking..."));
  delay(2000);
  String  msg, sbeat, stemp;
  float flat, flon;
  unsigned long age;
  char x[10];
  char y[10];
  char g[10];
  char h[10];
  char i[10];
  char c_lat[15];
  char c_lon[15];
  String slat = "";
  String slon = "";
  char data[100];
  Serial2.end();//this is important
  delay(1);
//  Serial2.listen();
  Serial2.println(F("AT+CGPSINFO"));
  delay(1000);
  if (Serial2.available() > 0)
  {
    indata = get_data();
    indata.trim();
    Serial.println("data: ");
    Serial.println(indata);
//    if (indata.indexOf(F("+CGPSINFO:")) >= 0)
//    {
//      indata.toCharArray(data, indata.length() + 1);
//      sscanf(data, "+CGPSINFO:%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", c_lat, x, c_lon, y, g, h, i);
//      lat = String(c_lat);
//      lon = String(c_lon);
//      lat_int =  lat.toFloat();
//      lon_int = lon.toFloat();
//
//      float degrees = floor(lat_int / 100);
//      double minutes = lat_int - (100 * degrees);
//      minutes /= 60;
//      degrees += minutes;
//      //      if (c_lat == 'S') degrees *= -1;
//      if ((x == 'S') || (x == 'W'))
//      {
//        degrees = degrees * (-1);
//      }
//      float lat_deg = degrees;
//      slat = String(lat_deg, 7);
//
//      float degrees1 = floor(lon_int / 100);
//      double minutes1 = lon_int - (100 * degrees1);
//      minutes1 /= 60;
//      degrees1 += minutes1;
//      if ((y == 'S') || (y == 'W'))
//      {
//        degrees1 = degrees1 * (-1);
//      }
//      float lon_deg = degrees1;
//      slon = String(lon_deg, 7);
//    }
//  }
//  if (!(lat.length() > 0) && !(lon.length() > 0))
//  {
//    msg =  "Weak signal...\nGPS not working";
//    Serial.print("GPS not Working...");
//    delay(1000);
//    sendsms(msg, numtel);//sends gps not working msg
//  }
//  else
//  {
//    //    lcd.clear();
//    Serial.print("LAT=");
//    Serial.println(slat);
//    //    lcd.setCursor(0, 1);
//    Serial.print("LON=");
//    Serial.println(slon);
//    String sms_text = "Vehicle At\n";
//    msg = sms_text + site + String(slat) + "," + String(slon) + "&z=16";
////    sendsms(msg, numtel);//sends location data msg
//  }
//  lat = "";
//  lon = "";
}
}

bool sms_available(String &sms_number , String &sms)
{
  inputString = "";
  inputString = sendcmd(UNREAD, 1);
  if (inputString.indexOf(CMGL) >= 0)
  {
    //    Serial.println("sms recieved");
    index1 = inputString.indexOf(CMGL);
    inputString = inputString.substring(index1);
    index1 = inputString.indexOf(':');
    index2 = inputString.indexOf(',');
    msg_index = inputString.substring(index1 + 1, index2);
    //    Serial.print("msg index :");
    msg_index.trim();
    //    Serial.println(msg_index);
    sms_number = inputString.substring(index2 + 1);
    index2 = sms_number.indexOf(',');
    sms_number = sms_number.substring(index2 + 2);
    index2 = sms_number.indexOf(',');
    sms_number = sms_number.substring(0, index2 - 1);
    //    Serial.print("sms_number :");
    sms_number.trim();
    //    Serial.println(sms_number);
    index1 = inputString.indexOf('\n');
    index2 = inputString.indexOf(ok);
    sms = inputString.substring(index1 + 1, index2 - 1);
    sms.trim();
    Serial.print("sms :");
    Serial.println(sms);
    String del_sms_cmd = CMGD + msg_index;
    sendcmd(del_sms_cmd, ok, 2000, 1);
    //    Serial.println(F("sms delete..."));
    return true;
  }
  else
  {
    return false;
  }
}

int call_status()
{
  if (Serial2.available() > 0)
  {
    indata = get_data();
    Serial.println("indata" + indata);
//        checkstr(indata);
    if (indata.indexOf(CLIP) >= 0)
    {
      return RECEIVINGCALL;
    }
    else
    {
      return IDLE;
    }
  }
  else
  {
    return IDLE;
  }
}

String get_call_number()
{
  String call_data = sendcmd("AT+CLCC", 1);
  delay(3000);
  if (call_data.indexOf("MISSED_CALL:") >= 0)   //MISSED_CALL: 01:31PM +919561883120
  {
      index1 = call_data.indexOf('+');
      num = call_data.substring(index1,34);
      Serial.println("num" + num);
      return num;
  }
}

void hangcall()
{
  sendcmd(F("ATH"), ok, 1000, 1);
}

bool sendsms(String sms_data, String recivr_num)
{
  Serial.println(F("sending sms "));
  Serial.println(recivr_num);
  Serial.println(sms_data);
  sendcmd("AT+CMGF=1", "OK", 1000, 1);
  delay(1000);
  String sms_cmd = "";
  sms_cmd = "AT+CMGS=\"";
  sms_cmd += recivr_num;
  sms_cmd += "\"";
  Serial.println(sms_cmd);
  sendcmd(sms_cmd, ">", 2000, 1);
  Serial2.print(sms_data);
  delay(2000);
  if (writecmd(26, "OK", 10000, 1))
  {
    //    Serial.println(F("send"));
    return true;
  }
  else
  {
    //    Serial.println(F("failed"));
    return false;
  }
}

String get_data()
{
  char c;
  indata = "";
  //  Serial.println(F("data available"));
  while (Serial2.available() > 0)
  {
    c = (char)Serial2.read();
    indata += c;
    Serial.print(c);
    delay(1);
  }
  indata.trim();
  //  Serial.print("d = ");
  //  Serial.println(indata);
  return indata;
}


bool connect_gsm()
{
  exicute_cmd(F("AT"), "OK", 5000);
  delay(10000);
//  Serial2.begin(9600);
  exicute_cmd(F("AT"), "OK", 5000);
  delay(1000);
  exicute_cmd("ATE0", "OK", 5000);
  delay(1000);
  exicute_cmd(F("AT+CLIP=1"), "OK", 5000);
  delay(1200);
  exicute_cmd(F("AT+CVHU=0"), "OK", 5000);
  delay(1200);
  exicute_cmd(F("AT+CTZU=1"), "OK", 5000);
  delay(1200);
  exicute_cmd(F("AT+CGPS=1,1"), "OK", 5000);
  delay(1000);
  exicute_cmd("AT+CMGF=1", "OK", 5000);
  delay(1200);
  exicute_cmd("AT+CNMI=0,0,0,0", "OK", 5000);
  delay(1200);
  exicute_cmd("AT+CMGD=0,4", "OK", 5000);
  delay(1200);
  return true;
}

bool get_network_status()
{
  String net_stat = sendcmd(F("AT+CREG?"), 1);
  delay(1000);
  if (net_stat.indexOf(F("+CREG:")) >= 0)
  {
    index1 = net_stat.indexOf(',');
    net_stat = net_stat.substring(index1 + 1);
    net_stat.trim();
    int net_stat_int = net_stat.toInt();
    if ((net_stat_int == 1) || (net_stat_int == 5))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  if (net_stat.indexOf("ERROR" >= 0))
  {
    return false;
  }
}

bool sendcmd(String gsmcmd, String response, int timeout, int debug)
{
  //  Serial.println(F(" in sendcmd1"));

  //  long t_start = micros();
    Serial.println(gsmcmd);
  Serial2.println(gsmcmd);
  if (debug == 1)
  {
    return get_gsm_cmd_response(response, timeout);
  }
}

bool writecmd(uint8_t gsmcmd, String response, int timeout, int debug)
{
  //  Serial.println(F(" in writecmd"));
  Serial2.write(gsmcmd);
  //  Serial.println(cmd);
  if (debug == 1)
  {
    return get_gsm_cmd_response(response, timeout);
  }
  return 1;
}

String sendcmd(String gsmcmd, int wait)
{
  //  Serial.println(F(" in sendcmd2"));
  //  Serial.println(gsmcmd);
  Serial2.println(gsmcmd);
  if (wait == 1)
  {
    long z = millis();
    while (!Serial2.available())
    {
      if ((millis() - z) >= 20000)
      {
        return "ERROR";
      }
    }
  }
  else if (wait == 0)
  {
    return "";
  }
  if (Serial2.available() > 0)
  {
    return get_data();
  }
  //  return 1;
}

bool get_gsm_cmd_response(String resp, int tout)
{
  //  Serial.println(F("in get_gsm_cmd_response()"));
  inputString = "";
  bool cmd_exicute = false;
  current_time = millis();
  while (1)
  {
    if (Serial2.available() > 0)
    {
      inputString = "";
      inputString = get_data();
      //        delay(1);
    }
    inputString.trim();
    if (inputString.endsWith("ERROR"))
    {
      break;
    }
    if ((millis() - current_time) > tout)
    {
      break;
    }
    if (inputString.endsWith(resp) == true)
    {
      cmd_exicute = true;
      break;
    }
  }
  if (cmd_exicute)
  {
    //    Serial.print("inputString=");
    //    Serial.println(inputString);
    return 1;
  }
  else
  {
    //    Serial.println("ERROR");
    return 0;
  }
}

bool exicute_cmd(String c , String r, int t)
{
  //  Serial.println(F("in exicute_cmd()"));
  long current_time2 = millis();
  gsm_connect = false;
  while (!gsm_connect)
  {
    if (sendcmd(c, r, t, 1))
    {
      gsm_connect = true;
      break;
    }
    else if ((millis() - current_time2) > t)
    {
      return false;
    }
    delay(1000);
  }
  return true;
}

void substring(char s[], char sub[], int p, int l) {
   int c = 0;
   
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}
