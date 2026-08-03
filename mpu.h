#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>

class Mpu {
  private:
    Adafruit_MPU6050 mpu;
    unsigned long lastSend;

    float alpha = 0.2;
    float fAx, fAy, fAz, fGx, fGy, fGz;
    bool inited = false;

    float ema(float newVal, float &state) {
      if (!inited) { state = newVal; return state; }
      state = alpha * newVal + (1 - alpha) * state;
      return state;
    }

  public:
    Mpu() { lastSend = 0; }

    void setup() {
      if (!mpu.begin()) {
        Serial.println("MPU6050 gagal detect, cek wiring!");
        while (1) delay(10);
      }
      Serial.println("MPU6050 OK");

      mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
      mpu.setGyroRange(MPU6050_RANGE_500_DEG);
      mpu.setFilterBandwidth(MPU6050_BAND_21_HZ); // built-in low-pass, bantu redam noise
    }

    void loop() {
      if (millis() - lastSend > 200) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        float ax = ema(a.acceleration.x, fAx);
        float ay = ema(a.acceleration.y, fAy);
        float az = ema(a.acceleration.z, fAz);
        float gx = ema(g.gyro.x, fGx);
        float gy = ema(g.gyro.y, fGy);
        float gz = ema(g.gyro.z, fGz);
        inited = true;

        JsonDocument doc;
        doc["ax"] = ax;
        doc["ay"] = ay;
        doc["az"] = az;
        doc["gx"] = gx;
        doc["gy"] = gy;
        doc["gz"] = gz;
        serializeJson(doc, Serial);
        Serial.println();
        lastSend = millis();
      }
    }
};