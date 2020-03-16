#include <DispenserController.h>

// Begins the data handshaking, this is called any time data is written to the FPGA.
void DispenserController::beginHandshake() {
  digitalWrite(HANDSHAKE_SENT, HIGH);
  Serial.println("Begin handshake...");
}

// Confirmation of data recieved, data confirmation should be sent AFTER the FPGA has changed state.
void DispenserController::confirmHandshake() {
  while(digitalRead(HANDSHAKE_RECEIVED) == LOW) {}
}

// Moves the FPGA to the next state in user mode.
void DispenserController::next() {

      pulsePin(NEXTSTATE);
      delay(400);

    }

// Resets the FPGA to the initial state.
void DispenserController::reset() {
  Serial.println("Reset...");
  pulsePin(RESETSTATE);
}

// Allows for characterization of custom colours - up to 20 can be stored.
void DispenserController::beginCharacterization() {
  bool finishCharacterization = false;
  colour temp;

  while(!finishCharacterization)
  {
    temp.name = Serial.read();
    colourSensor.getRGB(&temp.r, &temp.g, &temp.b);

    colourList[stored_colours] = temp;

    finishCharacterization = (Serial.read() == '5');
  }

}

// Compares two colour characterizations:
//  - Current block under the sensor.
//  - Target colour.
// Allows for adjustable errors (default 5%.)
// Will return true if colours match (within error.)
bool DispenserController::compareColour(colour target) {

  float r,g,b;
  colourSensor.getRGB(&r, &g, &b);

  return
  (
    ((errorLower*target.r) < r) && (r < (errorUpper*target.r)) &&
    ((errorLower*target.g) < g) && (g < (errorUpper*target.g)) &&
    ((errorLower*target.b) < b) && (b < (errorUpper*target.b))
  );
}

// Returns the characterization of a specific colour from the CUSTOM set.
colour DispenserController::lookupColour(char target) {

  for(int i = 0; i < 20; i++)
  {
    if (colourList[i].name == target) {return colourList[i];}
  }
    colour null;
    return null;
}

// Returns the characterization of a specific colour from the DEFAULT set.
colour DispenserController::lookupDefaultColour(char target) {
  for(int i = 0; i < 8; i++)
  {
    if (default_colours[i].name == target)
    {
      return default_colours[i];
    }
  }
    colour null;
    return null;

}

// Dispenses current block.
void DispenserController::dispense() {
  pulsePin(PISTON_CONTROL);

}

// Private method to pulse a specific pin on the FPGA
void DispenserController::pulsePin(int p) {
  beginHandshake();
  digitalWrite(p, HIGH);
  confirmHandshake();
  digitalWrite(p, LOW);
  delay(1000);
}

// Toggles between maintenance mode and user mode (default starts in user mode.)
void DispenserController::maintenanceToggle() {

  if (!userMode) {
    Serial.println("Changing to: maintenance mode");
    userMode = true;
    digitalWrite(MAINTENANCE_TOGGLE, HIGH);
  }

  else if (userMode) {
    Serial.println("Changing to: user mode");
    userMode = false;
    digitalWrite(MAINTENANCE_TOGGLE, LOW);
  }

}

// Maintenance mode function tests servo positions with a 3-bit output.
void DispenserController::maintenanceServoTest(int position) {

  beginHandshake();

  switch (position) {
    case 0:
      digitalWrite(SERVO_MAINTENANCE_0, LOW);
      digitalWrite(SERVO_MAINTENANCE_1, LOW);
      digitalWrite(SERVO_MAINTENANCE_2, LOW);
      break;

    case 1:
      digitalWrite(SERVO_MAINTENANCE_0, HIGH);
      digitalWrite(SERVO_MAINTENANCE_1, LOW);
      digitalWrite(SERVO_MAINTENANCE_2, LOW);
      break;

    case 2:
      digitalWrite(SERVO_MAINTENANCE_0, LOW);
      digitalWrite(SERVO_MAINTENANCE_1, HIGH);
      digitalWrite(SERVO_MAINTENANCE_2, LOW);
      break;

    case 3:
      digitalWrite(SERVO_MAINTENANCE_0, HIGH);
      digitalWrite(SERVO_MAINTENANCE_1, HIGH);
      digitalWrite(SERVO_MAINTENANCE_2, LOW);
      break;

    case 4:
      digitalWrite(SERVO_MAINTENANCE_0, LOW);
      digitalWrite(SERVO_MAINTENANCE_1, LOW);
      digitalWrite(SERVO_MAINTENANCE_2, HIGH);
      break;

    default:
      digitalWrite(SERVO_MAINTENANCE_0, LOW);
      digitalWrite(SERVO_MAINTENANCE_1, LOW);
      digitalWrite(SERVO_MAINTENANCE_2, LOW);

  }

  confirmHandshake();

  digitalWrite(SERVO_MAINTENANCE_0, LOW);
  digitalWrite(SERVO_MAINTENANCE_1, LOW);
  digitalWrite(SERVO_MAINTENANCE_2, LOW);

  delay(1000);
}

// Returns the colour characterization of the current block.
colour DispenserController::getColour() {
  colour current;
  colourSensor.getRGB(&current.r, &current.g, &current.b);
  return current;
}

// Checks to see if a colour ID exists in the DEFAULT set.
bool DispenserController::colourExists(char c) {
  for (int i = 0; i < 8; i++)
  {
    if (c == default_colours[i].name)
    {return true;}
  }
  return false;
}
