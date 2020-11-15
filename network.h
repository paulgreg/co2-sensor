#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

boolean connectToWifi(char* ssid, char* password) {
  if (WiFi.status()!= WL_CONNECTED) {
    Serial.printf("\nconnecting to %s\n", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    unsigned int retries = 100;
    while (WiFi.status() != WL_CONNECTED && (retries-- > 0)) {
      Serial.print(".");
      delay(500);
    }
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("\nWifi connection failed");
      return false;
    }
    Serial.print("\nwifi connected\nIP address: ");
    Serial.println(WiFi.localIP());
  }
  return true;
}

void disconnect() {
  WiFi.disconnect();
}

void sendMetrics(float temperature, float humidity, int co2) {
  if (WiFi.status()== WL_CONNECTED) {
    char data[500];
    sprintf(data, "temperature,location=%s value=%.1f\n" \
    "humidity,location=%s value=%.0f\n" \
    "co2,location=%s value=%i\n", LOCATION, temperature, LOCATION, humidity, LOCATION, co2);
    Serial.println("POST data:");
    Serial.print(data);
    Serial.print("to ");
    Serial.println(INFLUXDB_URL);
    
    HTTPClient http;
    http.begin(INFLUXDB_URL);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST(data);
    String payload = http.getString();
    http.end();
    
    Serial.println(payload);
    Serial.print("Response:");
    Serial.println(httpCode);
 }

}
