#include <Arduino.h>
#include "DispenserController.h"

DispenserController controller = DispenserController(12, 13, 11, 10, 9, 8, 20);

void setup() {
  Serial.begin(9600);
  controller.maintenanceToggle();
  controller.maintenanceToggle();

}

void loop() {

  controller.reset();

char c = 'e';

while(!controller.colourExists(c)){
  c = Serial.read();
}

colour target = controller.lookupDefaultColour(c);



  for(int i = 0; i < 5; i++)
  {
    colour t = controller.getColour();

    Serial.print(t.r); Serial.print("  ");
    Serial.print(t.g); Serial.print("  ");
    Serial.print(t.b); Serial.println();

    if (controller.compareColour(target)) {
      controller.dispense();

    }
    else{

      controller.next();

    }
  }


}
