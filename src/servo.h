#pragma once
#include <ESP32Servo.h>

class gerakServo {
  private:
    int pos, arah;
    unsigned long lastUpdate;
    Servo motorServo;

  public:
    gerakServo() { pos = 90; arah = 0; lastUpdate = 0; }

    void setup(uint8_t servoPin) {
      // Rentang pulse width 500us - 2500us untuk pergerakan servo
      motorServo.attach(servoPin, 500, 2500);
    }

    void setArah(int arahBaru) {
      arah = arahBaru;
    }

    void update() {
      if (arah == 0) return;
      if (millis() - lastUpdate < 20) return; // ~50Hz update rate
      lastUpdate = millis();

      pos += arah * 3; // step increment 3 derajat per tick
      motorServo.write(pos);
    }
};