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
  return ((target.r == r) && (target.g == g) && (target.b == b));
}

colour DispenserController::lookupColour(char target) {

if (maintenanceMode) {
  for(int i = 0; i < max_colours; i++)
  {
    if (colourList[i].name == target) {return colourList[i];}
  }
    colour null;
    return null;
  }
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
  if (!maintenanceMode) {
    Serial.println("Changing to: maintenance mode");
    maintenanceMode = true;
    digitalWrite(MAINTENANCE_TOGGLE, HIGH);
  }
  else if (maintenanceMode) {
    Serial.println("Changing to: user mode");
    maintenanceMode = false;
    digitalWrite(MAINTENANCE_TOGGLE, LOW);
  }

}

void DispenserController::maintenanceServoTest(int position) {

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
