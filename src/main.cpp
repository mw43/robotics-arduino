#include <Arduino.h>
#include "DispenserController.h"

// Control of the FPGA is done through a custom library: the DispenserController class.
//  - This class defines an functions the dispenser may need such as:
//    > Moving blocks between different positions.
//    > Colour: detection, comparison, and characterization.
//    > Built-in data handshaking between FGPA and Arduino.

DispenserController controller = DispenserController(12, 13, 11, 10, 9, 8, 3, 4, 5, 2);
char c = '#';

// Pin Assignments are as follows:
//   12 > NEXTSTATE
//   13 > RESETSTATE
//   11 > PISTON_CONTROL
//   10 > HANDSHAKE_SENT
//   9  > HANDSHAKE_RECEIVED
//   8  > MAINTENANCE_TOGGLE
//   3  > SERVO_MAINTENANCE_0
//   4  > SERVO_MAINTENANCE_1
//   5  > SERVO_MAINTENANCE_2

void setup() {
  // Open the serial port.
  Serial.begin(9600);
}

void loop() {

  while(!controller.validCommand(c)) {c = Serial.read();}

  // User Mode Operation
  if (controller.userMode)
  {
    // Reset to the initial position of the dispenser.
    controller.reset();


    // Using the colour ID: lookup the characterization of a target colour.
    //  - Returns a structure of type colour.
    //  - Colours have a name, and float RGB values.
    colour target = controller.lookupDefaultColour(c);


    // Begin moving through dispenser positions to search for the target colour.
    int counter = 0;
    bool colourFound = false;
    while(counter < 5 && !colourFound)
    {
      // Check the block currently positioned under the sensor, with the target colour.
      //  - An error margin of +/- 5% is allowed to account for slight changes in colour reading.
      if (controller.compareColour(target))
      {
        // If the target colour is detected: begin dispensing process.
        colourFound = true;
        controller.dispense();
        controller.reset();

      }
      else
      {
        // Target colour is not in the current position, move to the next position.
        controller.next();

      }
      counter++;
    }
  }

  // Maintenance Mode Operation
  else
  {
    controller.maintenanceServoTest(c);
  }

  Serial.println();
  c = '#';
}
