const int freq = 20000;
const int resolution = 8;
int motorSpeed = 255;

class GerakMotor {
  private:
    uint8_t pinAin1, pinAin2, pinPwmA;
    int arah = 0;

  public:
    GerakMotor() {}

    void setup(uint8_t ain1, uint8_t ain2, uint8_t pwmA) {
      pinAin1 = ain1;
      pinAin2 = ain2;
      pinPwmA = pwmA;

      pinMode(pinAin1, OUTPUT);
      pinMode(pinAin2, OUTPUT);

      ledcAttach(pinPwmA, freq, resolution);

      stop();
    }

    void setArah(int arahBaru) {
      arah = arahBaru;
      if (arah == 1) {
        digitalWrite(pinAin1, HIGH);
        digitalWrite(pinAin2, LOW);
        ledcWrite(pinPwmA, motorSpeed);
      } else if (arah == -1) {
        digitalWrite(pinAin1, LOW);
        digitalWrite(pinAin2, HIGH);
        ledcWrite(pinPwmA, motorSpeed);
      } else {
        stop();
      }
    }

    void update() {}

  private:
    void stop() {
      digitalWrite(pinAin1, LOW);
      digitalWrite(pinAin2, LOW);
      ledcWrite(pinPwmA, 0);
    }
};