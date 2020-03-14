#include <Arduino.h>
#include "MimasV2Controller.h"
#include "Adafruit_TCS34725.h"

MimasV2Controller fpga = MimasV2Controller(12, 13, 10, 9);
Adafruit_TCS34725 colourSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup() {
  Serial.begin(9600);
}

void loop() {
  fpga.next();

}

// Test commit between Desktop and Laptop.
