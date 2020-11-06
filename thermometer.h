// Inspired by https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 14
DHT dht(DHTPIN, DHT11);

float temperature = 0.0;
float humidity = 0.0;

void setupThermometer() {
  dht.begin();
}

float getTemperature() {
  float newTemperature = dht.readTemperature(false);
  if(!isnan(newTemperature)) temperature = newTemperature;
  return temperature;
}

float getHumidity() {
  float newHumidity = dht.readHumidity();
  if(!isnan(newHumidity)) humidity = newHumidity;
  return humidity;
}
