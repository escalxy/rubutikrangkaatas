#include <Wire.h>
#include <MPU6050_light.h>
#include <ArduinoJson.h>

class Mpu {
  private:
    MPU6050 mpu;
    unsigned long lastSend;

  public:
    Mpu() : mpu(Wire) { lastSend = 0; }

    void setup() {
      Wire.begin();
      byte status = mpu.begin();
      Serial.print("Status MPU6050: "); Serial.println(status);
      delay(1000);
      mpu.calcOffsets();
    }

    void loop() {
      mpu.update();
      if (millis() - lastSend > 100) { // rate sesuain kebutuhan PID yaw
        JsonDocument doc;
        doc["ax"] = mpu.getAccX();
        doc["ay"] = mpu.getAccY();
        doc["az"] = mpu.getAccZ();
        doc["gx"] = mpu.getGyroX();
        doc["gy"] = mpu.getGyroY();
        doc["gz"] = mpu.getGyroZ();
        serializeJson(doc, Serial);
        Serial.println();
        lastSend = millis();
      }
    }
};