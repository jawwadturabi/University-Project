#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;
#define BLYNK_PRINT Serial
char auth[] = "AUTH_TOKEN";

char ssid[] = "SSID";
char pass[] = "PASS";

#define switchone 18

void sendSensor()
{

  Blynk.virtualWrite(V5, "t");

}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  digitalWrite(switchone, pinValue);
}

void setup()
{
  // Debug console
  Serial.begin(1152000  );
  pinMode(switchone, OUTPUT);
  digitalWrite(switchone, LOW);
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);

}

void loop()
{
  Blynk.run();
  timer.run();

}
