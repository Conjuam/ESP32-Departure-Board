#include <LiquidCrystal.h>
#include <HTTPClient.h>
#include "time.h"
#include <WiFi.h>
#include <ArduinoJson.h>
// Uses ArduinoJson v.6.15.0

const char* ssid = "SSID"; //Substitute SSID with your WiFi SSID
const char* pass = "PASSWORD"; //Substitute PASSWORD with your Wifi Password

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0; //Offset from GMT in seconds
const int   daylightOffset_sec = 3600; //Daylight Saving Time Offset

LiquidCrystal lcd(14, 27, 26, 25, 33, 32); //LCD Pins

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    //Serial.println("Failed to obtain time");
    lcd.print("Failed to obtain time");
    return;
  }
  //Formatting options can be found here: https://en.cppreference.com/w/cpp/chrono/c/strftime
  lcd.print(&timeinfo, " %d/%m %H:%M:%S");
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  lcd.begin(16,2);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    //Serial.println("Establishing a connection with WiFi network");
    lcd.print("Please Wait...");
  }
  lcd.clear();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

}

void loop() {
  // put your main code here, to run repeatedly:

  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    //Substitute username and password for your unique username and password
    //Substitute "BMH" for your station's three-letter code
    http.begin("https://rttapi_username:rttapi_password@api.rtt.io/api/v1/json/search/BMH");
    int httpCode = http.GET();

    String payload = http.getString();
    //The following line is a formula generated here: https://arduinojson.org/v6/assistant/
    //Input a JSON response from a peak service time, to get one tailored to your station
    const size_t capacity = 18*JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(9) + 2*JSON_OBJECT_SIZE(3) + 18*JSON_OBJECT_SIZE(4) + 9*JSON_OBJECT_SIZE(9) + 9*JSON_OBJECT_SIZE(15);
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, payload);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(doc["services"][0]["locationDetail"]["realtimeArrival"].as<char*>());
    lcd.setCursor(4,0);
    lcd.print(": ");
    lcd.setCursor(6,0);
    lcd.print(doc["services"][0]["locationDetail"]["destination"][0]["description"].as<char*>());
    lcd.setCursor(0,1);
    printLocalTime();

    http.end(); //Release resources
  }
  //delay(1000);
}
