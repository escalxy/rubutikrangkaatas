#include <ESP32Servo.h>

class gerakServo {
  private:
    int pos;
    Servo motorServo;

  public:
    gerakServo() {
      pos = 90; // posisi awal servo
    }

  void setup(uint8_t servoPin) {
    motorServo.attach(servoPin);
    motorServo.write(pos);
  }

  void gerakKe(int derajat) {
    derajat = constrain(derajat, 0, 180);
    motorServo.write(derajat);
    pos = derajat;
    Serial.println("-> Servo ke posisi " + String(derajat));
  }

  void gerakKanan() {
    if (pos < 180) {
      for (int i = pos; i <= 180; i++) {
        motorServo.write(i);
        delay(10);
      }
      pos = 180;
      Serial.println("-> Servo bergerak ke kanan (180)");
    } else {
      Serial.println("! Posisi servo sudah di kanan.");
    }
  }

  void gerakKiri() {
    if (pos > 0) {
      for (int i = pos; i >= 0; i--) {
        motorServo.write(i);
        delay(10);
      }
      pos = 0;
      Serial.println("-> Servo bergerak ke kiri (0)");
    } else {
      Serial.println("! Posisi servo sudah di kiri.");
    }
  }
};