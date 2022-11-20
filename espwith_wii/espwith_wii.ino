//Including all the neccessary Libraries
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

WiFiClient client;
WiFiServer server(80);

String data;
void setup() 
{
  Serial.begin(9600);
  WiFi.begin("iot", "project1234");
  while ((!(WiFi.status() == WL_CONNECTED)))  
  {
    Serial.println("..."); 
    delay(300);
  }
  Serial.println("Connected!");
  server.begin();
}

void loop() 
{
  if(Serial.available())
  {
    data = Serial.readStringUntil('\n');
    data.trim();
    // wait for WiFi connection
    if ((WiFi.status() == WL_CONNECTED)) 
    {
      String data2 = "http://iotgecko.com/IOTHit.aspx?Id=mihita4madhusmi@gmail.com&Pass=9092&Data=" + data;
      HTTPClient http;    
      if(http.begin(client, data2))
      {
        int httpCode = http.GET(); 
        // httpCode will be negative on error
        if (httpCode > 0) 
          {
          // HTTP header has been send and Server response header has been handled
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
          {
            String payload = http.getString();
            //Serial.println(payload);
            int i = payload.indexOf("Label1"); 
            payload = payload.substring(i+8, i+12);
            Serial.println(payload);
            http.end();
            Serial.flush();
          }       
        } 
      }
    }
    delay(1000);
  }
}
