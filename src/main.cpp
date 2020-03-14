#include <Arduino.h>
#include "MimasV2Controller.h"

MimasV2Controller fpga = MimasV2Controller(12, 13, 10, 9);

void setup() {
  Serial.begin(9600);
}

void loop() {
  fpga.next();

}

// Test commit between Desktop and Laptop.
