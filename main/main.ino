#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Initialize the colour sensor for using the built-in library.
Adafruit_TCS34725 colourSensor = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

// FPGA PIN Assignments:
int NEXTSTATE = 12;
int RESESTATE = 13;
int HANDSHAKE_SENT = 10;
int HANDSHAKE_RECEIVED = 9;
  

void setup() {
  Serial.begin(9600);

  if(colourSensor.begin()){Serial.println("cs-ONLINE.");}
  else{Serial.println("cs-OFFLINE");}
}

void loop() {
  pulseFPGA(NEXTSATE);
  delay(1000);
}

void pulseFPGA(int pin) {
  
  int HANDSHAKE_TIMEOUT = 0;
  bool HANDSHAKE_CONFIRMED = false;

  pinMode(pin, OUTPUT);
  pinMode(HANDSHAKE_SENT, OUTPUT);
  pinMode(HANDSHAKE_RECEIVED, INPUT);

  digitalWrite(HANDSHAKE_SENT, HIGH);
  
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
  delay(200);.

  Serial.println("Waiting on handshake confirmation...");
  while((HANDSHAKE_CONFIRMED==false)||(HANDSHAKE_TIMEOUT <= 5))
  {
    
    HANDSHAKE_CONFIRMED = (digitalRead(HANDSHAKE_RECEIVED) == LOW);
    delay(1000);
    HANDSHAKE_TIMEOUT++;
  }
 
  if (HANDSHAKE_TIMEOUT >= 5)
  {
    Serial.println("Handshake timed-out. Did the FPGA get the data?");
  }
  digitalWrite(HANDSHAKE_SENT, LOW);
  
}
