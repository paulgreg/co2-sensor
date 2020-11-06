#include <EEPROM.h>

#define SIZE 20

void setupEEPROM(boolean reset) {
  EEPROM.begin(SIZE); 
  if (reset) {
    Serial.println("RESET EEPROM !");
    for (int i = 0; i < SIZE; i++) EEPROM.write(i, 0);
    EEPROM.commit();
    Serial.println("EEPROM RESETED !");
    delay(500);
  }
}

void writeValue(uint8_t idx, uint16_t value) {
  uint8_t address = idx * 2;
  EEPROM.write(address, lowByte(value));
  EEPROM.write(address + 1, highByte(value));
  EEPROM.commit();
}

uint16_t readValue(uint8_t idx) {
  uint8_t address = idx * 2;
  return word(EEPROM.read(address + 1), EEPROM.read(address));
}
