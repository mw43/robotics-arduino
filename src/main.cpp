#include <Arduino.h>
#include "DispenserController.h"

DispenserController controller = DispenserController(12, 13, 11, 10, 9, 8, 20);

void setup() {
  Serial.begin(9600);
  
}

void loop() {

  controller.reset();
  char c;

  while(!controller.colourExists(c)) {c = Serial.read();}

  colour target = controller.lookupDefaultColour(c);

  for(int i = 0; i < 5; i++)
  {
    if (controller.compareColour(target)) {
      controller.dispense();

    }
    else{

      controller.next();

    }
  }


}
