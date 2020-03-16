#ifndef DISPENSERCONTROLLER_H
#define DISPENSERCONTROLLER_H


#include <Arduino.h>
#include "Adafruit_TCS34725.h"
#include "Vector.h"

struct colour {
  String name;
  float r, g, b;
};

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
  void dispense();
  void beginCharacterization();
  bool compareColour(colour target);
  colour lookupColour(String target);



private:
  int NEXTSTATE;
  int RESETSTATE;
  int HANDSHAKE_SENT;
  int HANDSHAKE_RECEIVED;
  int SERVO_MAINTENANCE[3];
  int MAINTENANCE_TOGGLE;
  int PISTON_CONTROL;

  float colourCharacterization[3];

  Adafruit_TCS34725 colourSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

  bool maintenanceMode;
  bool colourMode;

  void beginHandshake();
  void confirmHandshake();

  Vector<colour> colorList;

  void pulsePin(int p);


};

#endif
