#include <Arduino.h>

#include "DispenserController.h"


DispenserController controller = DispenserController(12, 13, 10, 9);


void setup() {
  Serial.begin(9600);

}

void loop() {
  controller.next();
  if (controller.compareColour(controller.lookupColour(Serial.readString())))
  {
    controller.dispense();
  }

}
