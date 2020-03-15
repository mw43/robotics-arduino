#include <Arduino.h>
#include <DispenserController.h>



DispenserController::DispenserController(int n, int r, int hs_s, int hs_r) {
  this->NEXTSTATE = n;
  this->RESETSTATE = r;
  this->HANDSHAKE_SENT = hs_s;
  this->HANDSHAKE_RECEIVED = hs_r;

  pinMode(this->NEXTSTATE, OUTPUT);
  pinMode(this->RESETSTATE, OUTPUT);
  pinMode(this->HANDSHAKE_SENT, OUTPUT);
  pinMode(this->HANDSHAKE_RECEIVED, INPUT);

}

void DispenserController::beginHandshake() {
  digitalWrite(this->HANDSHAKE_SENT, HIGH);
}

void DispenserController::confirmHandshake() {
  bool HANDSHAKE_CONFIRMED;

  while(HANDSHAKE_CONFIRMED==false)
  {
    HANDSHAKE_CONFIRMED = (digitalRead(this->HANDSHAKE_RECEIVED) == HIGH);
  }

  if (HANDSHAKE_CONFIRMED)
  {
    digitalWrite(this->HANDSHAKE_SENT, LOW);
  }
}


void DispenserController::next() {
      this->beginHandshake();

      digitalWrite(this->NEXTSTATE, HIGH);

      this->confirmHandshake();

      digitalWrite(this->NEXTSTATE, LOW);
    }

void DispenserController::reset(){}
