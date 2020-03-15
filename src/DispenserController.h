#ifndef _MV2C_H
#define _MV2C_H

class DispenserController {
public:
  DispenserController(int n, int r, int hs_s, int hs_r);
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
