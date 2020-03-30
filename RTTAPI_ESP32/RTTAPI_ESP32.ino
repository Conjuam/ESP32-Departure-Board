#include <LiquidCrystal.h>
#include <HTTPClient.h>
#include "time.h"
#include <WiFi.h>
#include <ArduinoJson.h>
// Uses ArduinoJson v.6.15.0

//Also uses https://arduinojson.org/v6/assistant/
//https://en.cppreference.com/w/cpp/chrono/c/strftime

const char* ssid = "SSID";
const char* pass = "PASSWORD";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

LiquidCrystal lcd(14, 27, 26, 25, 33, 32);

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    //Serial.println("Failed to obtain time");
    lcd.print("Failed to obtain time");
    return;
  }
  //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  lcd.print(&timeinfo, " %d/%m %H:%M:%S");
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  lcd.begin(16,2);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    //Serial.println("Establishing a connection with WiFi network");
    lcd.print("Connecting...");
    
  }
  lcd.clear();
  //Serial.println("Connection established");
  //lcd.print("Connected!");
  //delay(5000);
  lcd.clear();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

}

void loop() {
  // put your main code here, to run repeatedly:

  
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin("https://rttapi_username:rttapi_password@api.rtt.io/api/v1/json/search/BMH");
    int httpCode = http.GET();

    //if (httpCode > 0) {
      String payload = http.getString();
      //Serial.println(httpCode);
      //Serial.println(payload);
      const size_t capacity = 18*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(9) + 2*JSON_OBJECT_SIZE(3) + 18*JSON_OBJECT_SIZE(4) + 9*JSON_OBJECT_SIZE(9) + 9*JSON_OBJECT_SIZE(15);
      DynamicJsonDocument doc(capacity);
      deserializeJson(doc, payload);
      //Serial.println();
      //Serial.println();
      //Serial.println();
      //Serial.print("Next Service is for: ");
      //Serial.print(doc["services"][0]["locationDetail"]["destination"][0]["description"].as<char*>());
      //Serial.println();
      //Serial.print("Due to arrive at: ");
      //Serial.print(doc["services"][0]["locationDetail"]["realtimeArrival"].as<char*>());
      //Serial.println();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(doc["services"][0]["locationDetail"]["realtimeArrival"].as<char*>());
      lcd.setCursor(4,0);
      lcd.print(": ");
      lcd.setCursor(6,0);
      lcd.print(doc["services"][0]["locationDetail"]["destination"][0]["description"].as<char*>());
      lcd.setCursor(0,1);
      printLocalTime();
    //}
    //else {
      //Serial.println("HTTP Request Error");
      //lcd.setCursor(0,0);
      //lcd.print("HTTP ERROR");
    //}

    http.end();
  }
  //delay(1000);
}
