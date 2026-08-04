#include <ESP32Servo.h>

class gerakServo {
  private:
    int pos, target;
    unsigned long lastStep;
    uint8_t stepDelay = 10; // ms per derajat, tuning kecepatan
    Servo motorServo;

  public:
    gerakServo() { pos = 90; target = 90; lastStep = 0; } //edit posisi awal servo

    void setup(uint8_t servoPin) {
      motorServo.attach(servoPin);
      motorServo.write(pos);
    }

    void gerakKe(int derajat) {
      target = constrain(derajat, 0, 70); //edit maksimal turunnya
    }

    void gerakKanan() { gerakKe(180); }
    void gerakKiri()  { gerakKe(0); }

    void update() {
      if (pos == target) return;
      if (millis() - lastStep < stepDelay) return;
      lastStep = millis();
      pos += (target > pos) ? 1 : -1;
      motorServo.write(pos);
    }
};