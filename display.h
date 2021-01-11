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
  char s[10];
  sprintf(s, "%2.0fC", temperature);
  display.setTextSize(2);
  display.setCursor(24, 42);
  display.print(s);
}

void displayHumidity(float humidity) {
  char s[10];
  sprintf(s, "%3.0f%%", humidity);
  display.setTextSize(2);
  display.setCursor(64, 42);
  display.print(s);
}


void displayCO2(int co2) {
  char s[10];
  display.setTextSize(3);
  sprintf(s, "%4i", co2);
  display.setCursor(10, 12);
  display.print(s);

  display.setTextSize(2);
  display.setCursor(86, 20);
  display.print("ppm");
}

void displayData(float temperature, float humidity, int co2) {
  display.clearDisplay();
  
  display.setTextColor(WHITE);
  
  displayCO2(co2);
  displayTemperature(temperature);
  displayHumidity(humidity);

  display.invertDisplay(co2 > CO2_THRESHOLD);
  display.display();
}
