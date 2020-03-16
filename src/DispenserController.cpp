#include <DispenserController.h>

void DispenserController::beginHandshake() {
  digitalWrite(HANDSHAKE_SENT, HIGH);
}

void DispenserController::confirmHandshake() {
  bool HANDSHAKE_CONFIRMED;

  while(HANDSHAKE_CONFIRMED==false)
  {
    HANDSHAKE_CONFIRMED = (digitalRead(HANDSHAKE_RECEIVED) == HIGH);
  }

  if (HANDSHAKE_CONFIRMED)
  {
    digitalWrite(HANDSHAKE_SENT, LOW);
  }
}

void DispenserController::next() {
      pulsePin(NEXTSTATE);
    }

void DispenserController::reset() {
  pulsePin(RESETSTATE);
}

void DispenserController::beginCharacterization() {
  bool finishCharacterization = false;
  colour temp;

  while(!finishCharacterization)
  {
    temp.name = Serial.readString();
    colourSensor.getRGB(&temp.r, &temp.g, &temp.b);
    finishCharacterization = (Serial.readString() == "finishCharacterization");
  }

}

bool DispenserController::compareColour(colour target) {
  float r,g,b;
  colourSensor.getRGB(&r, &g, &b);
  return ((target.r == r) && (target.g == g) && (target.b == b));
}

colour DispenserController::lookupColour(String target) {

  for(unsigned int i = 0; i < colorList.size(); i++)
  {
    if (colorList[i].name == target) {return colorList[i];}
  }
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
