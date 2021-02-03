#include <SPI.h>
//#include <BlynkSimpleEsp8266.h>
//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTPIN 14
#define DHTTYPE DHT11
String my_Local_IP;
DHT dht(DHTPIN, DHTTYPE);

char auth[] = "yBWMjZKxYgL8qQ6YXzwYtBz7k8XxMdBC";


char ssid[] = "Soft-H";
char pass[] = "Hello123!";

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(14, INPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  Serial.print(WiFi.localIP());
  my_Local_IP = WiFi.localIP().toString();
  Serial.println("' to connect");

}

BLYNK_WRITE(V1)
{
  float pinValue = param.asFloat();
  ledcWrite(12, pinValue);
}

void readSensor() {
  float h = dht.readHumidity(); // or dht.readTemperature(true) for Fahrenheit
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp reading is : ");
  Serial.print(t);
  Serial.print("   Humid reading is : ");
  Serial.println(h);
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V2, t);
}

void loop()
{

  Blynk.run();
  readSensor();
  delay(1000);
}
