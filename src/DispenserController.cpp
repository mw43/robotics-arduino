
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
      beginHandshake();

      digitalWrite(NEXTSTATE, HIGH);

      confirmHandshake();

      digitalWrite(NEXTSTATE, LOW);
    }

void DispenserController::reset() {}
