#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupScreen() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.cp437(true);
  display.clearDisplay();
}

int loopIdx = 0;

void displayTemperature(float temperature) {
  char s[12];
  sprintf(s, "Temp: %2.1f", temperature);
  display.setCursor(2,5);
  display.print(s);
}

void displayHumidity(float humidity) {
  char s[12];
  sprintf(s, "Humi: %3.0f", humidity);
  display.setCursor(2,25);
  display.print(s);
}

void displayCO2(int co2) {
  char s[12];
  sprintf(s, "co2: %5i", co2);
  display.setCursor(2,45);
  display.print(s);
}

void displayData(float temperature, float humidity, int co2) {
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  displayTemperature(temperature);
  displayHumidity(humidity);
  displayCO2(co2);

  display.invertDisplay(co2 > CO2_THRESHOLD);
  display.display();
}
