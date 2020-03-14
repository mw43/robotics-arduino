#include <Arduino.h>

class MimasV2Controller {

private:
    int NEXTSTATE;
    int RESETSTATE;
    int HANDSHAKE_SENT;
    int HANDSHAKE_RECEIVED;

    int SERVO_MAINTENANCE[3];

    int MAINTENANCE_TOGGLE;

    int PISTON_CONTROL;


    void beginHandshake() {
      digitalWrite(this->HANDSHAKE_SENT, HIGH);
    }

    void confimHandshake() {
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

  public:
    MimasV2Controller(int n, int r, int hs_s, int hs_r) {
      this->NEXTSTATE = n;
      this->RESETSTATE = r;
      this->HANDSHAKE_SENT = hs_s;
      this->HANDSHAKE_RECEIVED = hs_r;

      pinMode(this->NEXTSTATE, OUTPUT);
      pinMode(this->RESETSTATE, OUTPUT);
      pinMode(this->HANDSHAKE_SENT, OUTPUT);
      pinMode(this->HANDSHAKE_RECEIVED, INPUT);
    }

    void next() {
      this->beginHandshake();

      digitalWrite(this->NEXTSTATE, HIGH);

      this->confimHandshake();
      
      digitalWrite(this->NEXTSTATE, LOW);
    }



    void reset();



};
