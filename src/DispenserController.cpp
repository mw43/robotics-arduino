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
    temp.name = Serial.readString();
    colourSensor.getRGB(&temp.r, &temp.g, &temp.b);

    colourList[stored_colours] = temp;

    finishCharacterization = (Serial.readString() == "finishCharacterization");
  }

}

bool DispenserController::compareColour(colour target) {
  float r,g,b;
  colourSensor.getRGB(&r, &g, &b);
  return ((target.r == r) && (target.g == g) && (target.b == b));
}

colour DispenserController::lookupColour(String target) {

  for(int i = 0; i < max_colours; i++)
  {
    if (colourList[i].name == target) {return colourList[i];}
  }

    colour null;
    null.name = "null";
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
