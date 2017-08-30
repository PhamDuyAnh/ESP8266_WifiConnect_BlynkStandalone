/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example runs directly on ESP8266 chip.
 *
 * You need to install this for ESP8266 development:
 *   https://github.com/esp8266/Arduino
 *
 * Please be sure to select the right ESP8266 module
 * in the Tools -> Board menu!
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 *
 **************************************************************
 * Pham Duy Anh - CKD - phamduyanh@gmail.com
 * Create: 25-07-2017
 * Update: 30-07-2017
 **************************************************************/
//Blynk.begin(auth, ssid, pass);
//You can also specify server:
//Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
//Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
//BLYNK_READ(virtualPin) function will be called every time App Widget requests data for Virtual Pin
//BLYNK_WRITE(virtualPin) function will be called every time App Widget writes value to Virtual Pin
#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//define LED toggle
WidgetLED led1(V6);
WidgetLED led2(V2);
//define built in LDR, LED, Button
//                         //V0
#define ldr             A0 //V1 - LDR sensor
#define button          4  //V2 - FLASH button
#define ledGreen        12 //V3
#define ledBlue         13 //V4
#define ledRed          15 //V5
#define led             2  //V6 - led built-in
//                         //V7 - Humidity
//                         //V8 - Temperature
#define inLedConnectStatus 2000

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
#define localserver
#ifdef localserver
  char auth[] = "YourAuthToken"; //local
#else 
  char auth[] = "YourAuthToken"; //cloud.blynk.vn
#endif

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid1[] = "ssid1";
char pass1[] = "pass1";

char ssid2[] = "ssid2";
char pass2[] = "pass2";

char ssid3[] = "ssid3";
char pass3[] = "pass3";

char ssid4[] = "ssid4";
char pass4[] = "pass4";

long timeCon = millis();
long timeDht = millis();

bool isFirstConnect = true;

void ledWifiConnectStatus()
{
  for (int i=0; i < 5; i++)
  {
    digitalWrite(led,0);
    delay(20);
    digitalWrite(led,1);
    delay(200);
  }
}
// Led status if Blynk is Connected
void ledConnectStatus()
{
  if (millis()- timeCon > inLedConnectStatus)
  {
    if(Blynk.connected())
    {
      digitalWrite(led, 0);
      delay(20);
      digitalWrite(led, 1);
    }
    else digitalWrite(led, 0);
    
    timeCon = millis();
  }
}
// Led status if Blynk is Connected

void wifiConnect()
{
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  // WIFI_AP, WIFI_STA, WIFI_AP_STA, WIFI_OFF
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // WiFi.scanNetworks will return the number of networks found
  // WiFi.RSSI(i) at long
  // WiFi.SSID(i) at String
  // WiFi.encryptionType(i) -> TKIP (WPA) = 2, WEP = 5, CCMP (WPA) = 4, NONE = 7, AUTO = 8
  long rssi = -100;
  byte numF;
  byte n = WiFi.scanNetworks();
  if (n > 0)
  {
    for (byte i = 0; i < n; i++)
    {
      if (rssi < WiFi.RSSI(i))
      {
        rssi = WiFi.RSSI(i);
        numF = i;
      }
    }
    //Connect to Fifi and Blynk
    if (WiFi.SSID(numF) == String(ssid1))
    {
      Serial.println("");
      Serial.println(ssid1);
      Serial.println(pass1);
      #ifdef localserver
        Blynk.begin(auth, ssid1, pass1, "myblynk.homeip.net");
      #else
        Blynk.begin(auth, ssid1, pass1, "cloud.blynk.vn");
      #endif
      ledWifiConnectStatus();
    }
    else if (WiFi.SSID(numF) == String(ssid2))
    {
      Serial.println("");
      Serial.println(ssid2);
      Serial.println(pass2);
      #ifdef localserver
        Blynk.begin(auth, ssid2, pass2, "myblynk.homeip.net");
      #else
        Blynk.begin(auth, ssid2, pass2, "cloud.blynk.vn");
      #endif
      ledWifiConnectStatus();
    }
    else if (WiFi.SSID(numF) == String(ssid3))
    {
      Serial.println("");
      Serial.println(ssid3);
      Serial.println(pass3);
      #ifdef localserver
        Blynk.begin(auth, ssid3, pass3, "myblynk.homeip.net");
      #else
        Blynk.begin(auth, ssid3, pass3, "cloud.blynk.vn");
      #endif
      ledWifiConnectStatus();
    }
    else if (WiFi.SSID(numF) == String(ssid4))
    {
      Serial.println("");
      Serial.println(ssid4);
      Serial.println(pass4);
      #ifdef localserver
        Blynk.begin(auth, ssid4, pass4, "myblynk.homeip.net");
      #else
        Blynk.begin(auth, ssid4, pass4, "cloud.blynk.vn");
      #endif
      ledWifiConnectStatus();
    }
  }
  else
  {
    Serial.println("no networks found");
  }
}


void setup()
{
  Serial.begin(9600);
  Serial.println("");
  
  pinMode(led,      OUTPUT);
  pinMode(ledRed,   OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue,  OUTPUT);
  pinMode(button,   INPUT);
  pinMode(ldr,      INPUT);
  digitalWrite(led, 1);

  wifiConnect();
}

void loop()
{
  Blynk.run();
  ledConnectStatus();
}

BLYNK_CONNECTED()
{
  if (isFirstConnect)
  {
    for (int i=0; i < 5; i++)
    {
      digitalWrite(ledRed,1);
      delay(20);
      digitalWrite(ledRed,0);
      delay(200);
    }
    Blynk.syncAll();
    isFirstConnect = false;
  }
}

BLYNK_WRITE(3)
{
  int g = param[0].asInt();
  analogWrite(ledGreen, g);
}
BLYNK_WRITE(4)
{
  int b = param[0].asInt();
  analogWrite(ledBlue, b);
}
BLYNK_WRITE(5)
{
  int r = param[0].asInt();
  analogWrite(ledRed, r);
}
BLYNK_READ(0)
{
  // Fifi strength
  int ws = WiFi.RSSI();
  String wsS;
  if ((ws > -100) && (ws < -20))
  {
    ws = 2 * (ws + 100);
    Blynk.virtualWrite(V0,ws);
  }
  else Blynk.virtualWrite(V0,"-");
  
  //Led toggle
  if (!digitalRead(led)) led1.setValue(255);
  else                   led1.setValue(0);
  //Button toggle
  if (!digitalRead(button)) led2.setValue(255);
  else                      led2.setValue(0);
}
BLYNK_READ(1)
{
  Blynk.virtualWrite(V1,analogRead(ldr));
}
BLYNK_READ(7)
{
  Blynk.virtualWrite(V7,dht.readHumidity());
}
BLYNK_READ(8)
{
  Blynk.virtualWrite(V8,dht.readTemperature());
}
