#ifndef DISPENSERCONTROLLER_H
#define DISPENSERCONTROLLER_H

#include <Arduino.h>

class DispenserController {
public:

  DispenserController(int n, int r, int hs_s, int hs_r):
  NEXTSTATE(n), RESETSTATE(r), HANDSHAKE_SENT(hs_s), HANDSHAKE_RECEIVED(hs_r)
  {
    pinMode(NEXTSTATE, OUTPUT);
    pinMode(RESETSTATE, OUTPUT);
    pinMode(HANDSHAKE_SENT, OUTPUT);
    pinMode(HANDSHAKE_RECEIVED, INPUT);
  };

  void next();
  void reset();

private:
  int NEXTSTATE;
  int RESETSTATE;
  int HANDSHAKE_SENT;
  int HANDSHAKE_RECEIVED;
  int SERVO_MAINTENANCE[3];
  int MAINTENANCE_TOGGLE;
  int PISTON_CONTROL;
  
  void beginHandshake();
  void confirmHandshake();
};

#endif
