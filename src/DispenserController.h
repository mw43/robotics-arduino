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
  DispenserController(int n, int r, int p, int hs_s, int hs_r, int m, int s0, int s1, int s2):
  NEXTSTATE(n), RESETSTATE(r), PISTON_CONTROL(p), HANDSHAKE_SENT(hs_s), HANDSHAKE_RECEIVED(hs_r), MAINTENANCE_TOGGLE(m),
  SERVO_MAINTENANCE_0(s0), SERVO_MAINTENANCE_1(s1), SERVO_MAINTENANCE_2(s2)
  {
    pinMode(NEXTSTATE, OUTPUT);
    pinMode(RESETSTATE, OUTPUT);
    pinMode(PISTON_CONTROL, OUTPUT);
    pinMode(HANDSHAKE_SENT, OUTPUT);
    pinMode(HANDSHAKE_RECEIVED, INPUT);
    pinMode(SERVO_MAINTENANCE_0, OUTPUT);
    pinMode(SERVO_MAINTENANCE_1, OUTPUT);
    pinMode(SERVO_MAINTENANCE_2, OUTPUT);
    pinMode(MAINTENANCE_TOGGLE, OUTPUT);

    stored_colours = 0;

  };

  bool userMode = true;

  // Public functions for this dispenser class.
  void next();
  void reset();
  void dispense();
  void maintenanceToggle();
  void beginCharacterization();
  void maintenanceServoTest(char position);
  bool compareColour(colour target);
  colour lookupColour(char target);
  colour lookupDefaultColour(char target);
  colour getColour();
  bool colourExists(char c);
  bool validCommand(char c);
  void processCommand(char c);
  bool valiedMaintenanceCommand(char c);

  // Private member variables and functions.
private:

  // Pin Assignments
  int NEXTSTATE;
  int RESETSTATE;
  int PISTON_CONTROL;
  int HANDSHAKE_SENT;
  int HANDSHAKE_RECEIVED;
  int MAINTENANCE_TOGGLE;
  int SERVO_MAINTENANCE_0;
  int SERVO_MAINTENANCE_1;
  int SERVO_MAINTENANCE_2;


  // Colour sensor used by the dispenser
  Adafruit_TCS34725 colourSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);


  // Private functions for data transfer.
  void beginHandshake();
  void confirmHandshake();
  void pulsePin(int p);

  // Stores a list of colours that have been characterized.
  int stored_colours;
  colour colourList[20];

  // Default colours
  colour default_colours[8] = {
    colour('R', 174.3, 52.1, 36.78), /*RED*/
    colour('G', 65.9, 125.0, 54.2),  /*GREEN*/
    colour('B', 51.2, 86.1, 112.8),  /*BLUE*/
    colour('L', 91.8, 113.7, 34.1),  /*LIME*/
    colour('O', 154.0, 65.6, 28.6),  /*ORANGE*/
    colour('N', 103.2, 89.1, 57.9),  /*BLACK*/
    colour('Y', 118.2, 94.5, 28.9),  /*YELLOW*/
    colour('W', 88.5, 95.9, 57.1)    /*WHITE*/
  };

  // Colour error adjustment
  float errorUpper = 1.05;
  float errorLower = 0.95;

  char commands[2] = {'$', '%'};
  char maintenanceCommands[7] = {'0', '1', '2', '3', '4', '6', '7'};
};

#endif
