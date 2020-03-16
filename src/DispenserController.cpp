#include <DispenserController.h>

void DispenserController::beginHandshake() {
  digitalWrite(HANDSHAKE_SENT, HIGH);
  Serial.println("Begin handshake...");
}

void DispenserController::confirmHandshake() {
  while(digitalRead(HANDSHAKE_RECEIVED) == LOW) {}
}

void DispenserController::next() {

      pulsePin(NEXTSTATE);
      delay(400);

    }

void DispenserController::reset() {
  Serial.println("Reset...");
  pulsePin(RESETSTATE);
}

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

colour DispenserController::lookupColour(char target) {

  for(int i = 0; i < 20; i++)
  {
    if (colourList[i].name == target) {return colourList[i];}
  }
    colour null;
    return null;
}

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

void DispenserController::dispense() {
  pulsePin(PISTON_CONTROL);

}

void DispenserController::pulsePin(int p) {
  beginHandshake();
  digitalWrite(p, HIGH);
  confirmHandshake();
  digitalWrite(p, LOW);
  delay(1000);
}

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

void DispenserController::maintenanceServoTest(int position) {

  beginHandshake();

  switch (position) {
    case 0:
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      break;

    case 1:
      digitalWrite(SERVO_MAINTENANCE[0], HIGH);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      break;

    case 2:
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], HIGH);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      break;

    case 3:
      digitalWrite(SERVO_MAINTENANCE[0], HIGH);
      digitalWrite(SERVO_MAINTENANCE[0], HIGH);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      break;

    case 4:
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], HIGH);
      break;

    default:
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);
      digitalWrite(SERVO_MAINTENANCE[0], LOW);

  }

  confirmHandshake();

  digitalWrite(SERVO_MAINTENANCE[0], LOW);
  digitalWrite(SERVO_MAINTENANCE[0], LOW);
  digitalWrite(SERVO_MAINTENANCE[0], LOW);

  delay(1000);
}

colour DispenserController::getColour() {
  colour current;
  colourSensor.getRGB(&current.r, &current.g, &current.b);
  return current;
}

bool DispenserController::colourExists(char c) {
  for (int i = 0; i < 8; i++)
  {
    if (c == default_colours[i].name)
    {return true;}
  }
  return false;
}
