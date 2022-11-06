/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLf_VEI5xH"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "X5zwImlUNpugTUixUBav5_NeUB345PWx"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <PMS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "E = mc2";
char pass[] = "zxkeq8vo9i931";

PMS pms(Serial);
PMS::DATA data;
LiquidCrystal_I2C lcd(0x27, 16, 2);

BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(BT1, OUTPUT);
  lcd.begin();
  lcd.display();
  lcd.backlight();
  lcd.clear();
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  Blynk.connect();
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
}


BLYNK_WRITE(V2){
  if(param.asInt()==1){
    digitalWrite(14, HIGH);
  }
  else{
    digitalWrite(14, LOW);
  }
}

void loop()
{
  Blynk.run();

  if (pms.read(data)) {
    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);
    lcd.begin();
    lcd.display();
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("Dust : (ug/m3)");
    lcd.setCursor(0,1);
    lcd.println("PM 2.5 : ");
    lcd.println(data.PM_AE_UG_2_5);
    delay(1000);
    Blynk.virtualWrite(V1, data.PM_AE_UG_2_5);

}