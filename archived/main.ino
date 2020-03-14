#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Initialize the colour sensor for using the built-in library.
Adafruit_TCS34725 colourSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// FPGA PIN Assignments:
  int NEXTSTATE = 12;
  int RESETSTATE = 13;
  int HANDSHAKE_SENT = 10;
  int HANDSHAKE_RECEIVED = 9;


void setup() {
  Serial.begin(9600);

  if(colourSensor.begin()){Serial.println("cs-ONLINE.");}
  else{Serial.println("cs-OFFLINE");}
}

void loop() {
  Serial.println("Initializing");
  pulseFPGA(RESETSTATE);

  for(int i = 0; i < 4; i++)
  {

    Serial.println(i);
    pulseFPGA(NEXTSTATE);
    delay(1000);
  }

  Serial.println("Completed");
  pulseFPGA(RESETSTATE);
}

void pulseFPGA(int pin) {

  int HANDSHAKE_TIMEOUT = 0;
  bool HANDSHAKE_CONFIRMED = false;

  pinMode(pin, OUTPUT);
  pinMode(HANDSHAKE_SENT, OUTPUT);
  pinMode(HANDSHAKE_RECEIVED, INPUT);

  digitalWrite(HANDSHAKE_SENT, HIGH);

  digitalWrite(pin, HIGH);
  delay(400);
  digitalWrite(pin, LOW);
  delay(400);

  Serial.println("Waiting on handshake confirmation...");
  while((HANDSHAKE_CONFIRMED==false))
   {
      HANDSHAKE_CONFIRMED = (digitalRead(HANDSHAKE_RECEIVED) == HIGH);
   }

  if (HANDSHAKE_CONFIRMED)
  {
    Serial.println("Handshake confirmed");
    digitalWrite(HANDSHAKE_SENT, LOW);

  }

}
