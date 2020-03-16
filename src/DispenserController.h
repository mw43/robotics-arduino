#ifndef DISPENSERCONTROLLER_H
#define DISPENSERCONTROLLER_H

#include <Arduino.h>
#include "Adafruit_TCS34725.h"

// STRUCT - Defines a colour with RGB values and a name.
struct colour {
  char name;
  float r, g, b;
  colour(){};
  colour(char name, float r, float g, float b): name(name), r(r), g(g), b(b){};
};

// Control class for the dispenser.
class DispenserController {

public:

  // Construstor takes pin assignments.
  DispenserController(int n, int r, int hs_s, int hs_r, int m, int c):
  NEXTSTATE(n), RESETSTATE(r), HANDSHAKE_SENT(hs_s), HANDSHAKE_RECEIVED(hs_r), MAINTENANCE_TOGGLE(m), max_colours(c)
  {
    pinMode(NEXTSTATE, OUTPUT);
    pinMode(RESETSTATE, OUTPUT);
    pinMode(HANDSHAKE_SENT, OUTPUT);
    pinMode(HANDSHAKE_RECEIVED, INPUT);
    pinMode(MAINTENANCE_TOGGLE, OUTPUT);
    colourList = new colour[max_colours]();
    stored_colours = 0;

  };

  // Public functions for this dispenser class.
  void next();
  void reset();
  void dispense();
  void maintenanceToggle();
  void beginCharacterization();
  bool compareColour(colour target);
  colour lookupColour(char target);


  // Private member variables and functions.
private:

  // Pin Assignments
  int NEXTSTATE;
  int RESETSTATE;
  int HANDSHAKE_SENT;
  int HANDSHAKE_RECEIVED;
  int SERVO_MAINTENANCE[3];
  int MAINTENANCE_TOGGLE;
  int PISTON_CONTROL;

  // Colour sensor used by the dispenser
  Adafruit_TCS34725 colourSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

  // Toggles for various modes of operations.
  bool maintenanceMode = true;
  bool colourMode;

  // Private functions for data transfer.
  void beginHandshake();
  void confirmHandshake();
  void pulsePin(int p);

  // Stores a list of colours that have been characterized.
  int max_colours;
  int stored_colours;
  colour *colourList;

  // Default colours
  int default_colours


};

#endif
