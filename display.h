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
  // Show initial display buffer contents on the screen the library initializes this with an Adafruit splash screen.
  display.display();
  display.cp437(true);
}

int loopIdx = 0;

void displayTemp(float temp) {
  char sTmp[20];
  sprintf(sTmp, "Temp: %2.1f", temp);
  display.setCursor(2,5);
  display.print(sTmp);
}

void displayCO2(int co2) {
  char sCO2[20];
  sprintf(sCO2, "co2: %5i", co2);
  display.setCursor(2,25);
  display.print(sCO2);
}

void displayPrintWarning() {
  display.setCursor(10,45);
  display.print("Windows !");
}

void displayData(float temp, int co2) {
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  displayTemp(temp);
  displayCO2(co2);

  if (co2 > CO2_THRESHOLD) {
    display.invertDisplay(true);
    displayPrintWarning();
  } else {
    display.invertDisplay(false);
  }
  display.display();
}
