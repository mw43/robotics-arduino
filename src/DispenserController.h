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
  DispenserController(int n, int r, int p, int hs_s, int hs_r, int m, int c):
  NEXTSTATE(n), RESETSTATE(r), PISTON_CONTROL(p), HANDSHAKE_SENT(hs_s), HANDSHAKE_RECEIVED(hs_r), MAINTENANCE_TOGGLE(m), max_colours(c)
  {
    pinMode(NEXTSTATE, OUTPUT);
    pinMode(RESETSTATE, OUTPUT);
    pinMode(PISTON_CONTROL, OUTPUT);
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
  void maintenanceServoTest(int position);
  bool compareColour(colour target);
  colour lookupColour(char target);
  colour lookupDefaultColour(char target);
  colour getColour();
  bool colourExists(char c);


  // Private member variables and functions.
private:

  // Pin Assignments
  int NEXTSTATE;
  int RESETSTATE;
  int PISTON_CONTROL;
  int HANDSHAKE_SENT;
  int HANDSHAKE_RECEIVED;
  int SERVO_MAINTENANCE[3];
  int MAINTENANCE_TOGGLE;


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
  colour default_colours[8] = {
    colour('R', 174.3, 52.1, 36.78), // RED
    colour('G', 65.9, 125.0, 54.2),
    colour('B', 51.2, 86.1, 112.8),
    colour('L', 91.8, 113.7, 34.1),
    colour('O', 154.0, 65.6, 28.6),
    colour('N', 103.2, 89.1, 57.9),
    colour('Y', 118.2, 94.5, 28.9),
    colour('W', 88.5, 95.9, 57.1)
  };


};

#endif
