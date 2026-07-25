#define JGA_PWM_SPEED 200   // duty cycle PWM (0-255) -- silakan tuning

class GerakMotor {
  private:
    uint8_t pinAin1, pinAin2, pinPwmA;
    int arah = 0;  // -1 mundur, 0 stop, 1 maju

  public:
    GerakMotor() {}

    void setup(uint8_t ain1, uint8_t ain2, uint8_t pwmA) {
      pinAin1 = ain1;
      pinAin2 = ain2;
      pinPwmA = pwmA;

      pinMode(pinAin1, OUTPUT);
      pinMode(pinAin2, OUTPUT);
      pinMode(pinPwmA, OUTPUT);

      berhenti();
    }

    void setArah(int arahBaru) {
      arah = arahBaru;
      if (arah == 1) {
        digitalWrite(pinAin1, HIGH);
        digitalWrite(pinAin2, LOW);
        analogWrite(pinPwmA, JGA_PWM_SPEED);
      } else if (arah == -1) {
        digitalWrite(pinAin1, LOW);
        digitalWrite(pinAin2, HIGH);
        analogWrite(pinPwmA, JGA_PWM_SPEED);
      } else {
        berhenti();
      }
    }

    void update() {
    }

  private:
    void berhenti() {
      digitalWrite(pinAin1, LOW);
      digitalWrite(pinAin2, LOW);
      analogWrite(pinPwmA, 0);
    }
};