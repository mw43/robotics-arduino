#include <Arduino.h>
#include <vector>
#include "DispenserController.h"
#include "Adafruit_TCS34725.h"

MimasV2Controller fpga = MimasV2Controller(12, 13, 10, 9);
Adafruit_TCS34725 colourSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

bool maintenanceMode;
bool colourMode;

float colourCharacterization[3];

void setup() {
  Serial.begin(9600);
  maintenanceMode = false;
  colourMode = false;
}

void loop() {

  if (maintenanceMode)
  {

  }

  else
  {
    if (colourMode)
    {

    }

    else
    {

    }
  }

}
