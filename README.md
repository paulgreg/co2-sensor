# esp8266 CO2 sensor

That project goal is to mesure CO2 and if too high, tell user to open their windows. 
It’s a simple way to remind to recycle air and so, reduce risk against COVID-19 in crowded space (like classrooms). 
Inspiration is from [Eole project](http://lafabrique.centralesupelec.fr/projetco2/). Thanks


## Components

 * esp8266 (I’ve used a Wemos D1 for tryout, and then an ESP8266 for definitive project)
 * I2C 128X64 OLED LCD screen
 * Humidity & temperature DHT11 sensor (needed as input to SGP30)
 * SGP30 Air Quality Sensor CO2 sensor

## Connections

### I2C screen

 * GND on GND
 * VCC on 3.3V
 * SCL on esp8266 D1
 * SDA on esp8266 D2

### SGP30 sensor

 * GND on GND
 * VCC on 3.3V
 * SCL on esp8266 D1
 * SDA on esp8266 D2

### DHT11 sensor

 * GND on GND
 * VCC on 3.3V
 * sensor to d5 / GPIO14

## Information

The first time you’ll program the esp8266, you’ll need to set `RESET_EEPROM` to `true` in order to prepare EEPROM. Warning, you’ll need to set it back to `false` after that first programming.

As explained on  [Adafruit SGP30 sensor page](https://learn.adafruit.com/adafruit-sgp30-gas-tvoc-eco2-mox-sensor/arduino-code), the SPG30 sensor needs to be calibrated with a baseline value (given by the sensor). 
That baseline is periodically asked from SPG30 sensor and stored into EEPROM (~1 time per hour). 
When the system boots, it's read from EEPROM and the SPG30 is calibrated with that value. That increase the sensor precision.

If I understood correctly, the best baseline value is get after 12 continuous hours of operation. If you don’t use the sensor for 7 days, you’ll have to let it run again for 12 hours to « reset » the correct baseline.

Also, the DHT11 sensor is used to compute absolute humidity level, also used to increase SGP30 precision.

Please note also the `CO2_THRESHOLD` value which inverts the display.
It’s a simple way to bring attention to users to open windows.

## References

  * [Eole project](http://lafabrique.centralesupelec.fr/projetco2/)
  * [I2C OLED screen](https://randomnerdtutorials.com/esp8266-0-96-inch-oled-display-with-arduino-ide/)
  * [DHT11 sensor tryout](https://hackaday.io/project/175689/log/185783-humidity-temperature-module)
  * [Adafruit SGP30 sensor explanation](https://learn.adafruit.com/adafruit-sgp30-gas-tvoc-eco2-mox-sensor/arduino-code)
  * [esp8266 pinout reference](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
