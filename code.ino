#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>

Adafruit_FeatherOLED oled = Adafruit_FeatherOLED();

#define DHTPIN            2
#define DHTTYPE           DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  oled.init();
  oled.setBatteryVisible(true);

  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  Serial.println("");
  Serial.println("Temp and Humidity code, by Daniel Mruczynski 02/11/2018");
  Serial.println("Pastebin link (if that still exists): pastebin.com/LCxzJyEZ");

}

void loop() {
  Serial.println("");
  oled.clearDisplay();
  oled.setTextSize(1);
  float battery = analogRead(A0);
// resistors are 220k and 940k
  battery /= .1897;
  battery /= 1024;
  oled.setBattery(battery);
  oled.renderBattery();
  Serial.print(battery);
  Serial.println(" V Battery Voltage");

  oled.setTextSize(2);
  oled.setCursor(0, 0);

  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  Serial.print(event.temperature);
  Serial.println(" Degrees C");
  oled.print(event.temperature, 1);
  oled.setTextSize(1);
  oled.println("C");

  oled.setCursor(0, 17);
  oled.setTextSize(2);
  
  dht.humidity().getEvent(&event);
  Serial.print(event.relative_humidity);
  Serial.println(" % Relative Humidity");

  oled.print(event.relative_humidity, 1);
  oled.setTextSize(1);
  oled.println("%");  

  oled.setCursor(68, 23);
  oled.print("BootyBotV2");
  
  oled.display();

//  ESP.deepSleep(1e6);
  delay(1000);
}
