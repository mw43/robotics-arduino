#include <Arduino.h>
#include "DispenserController.h"

DispenserController controller = DispenserController(12, 13, 10, 9, 8, 20);

void setup() {
  Serial.begin(9600);
   controller.maintenanceToggle();
   controller.maintenanceToggle();

//  pinMode(8, OUTPUT);
//  digitalWrite(8, HIGH);

}

void loop() {

//  bool validCommand = false;
  //char command;

// Read serial port commands.
//while(!validCommand) {
  //command = (char)Serial.read();

//

  controller.reset();
  delay(1000);
  for (int i = 0; i < 5; i++) {
    controller.next();
    delay(1000);
  }


}
