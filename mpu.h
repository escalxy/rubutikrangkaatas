#include <Wire.h>
#include <MPU6050_light.h>

class Mpu {
  private:
    MPU6050 mpu;
    unsigned long lastPrint;   

  public:
    Mpu() : mpu(Wire) {
      lastPrint = 0;
    }

  void setup() {
    Wire.begin();
    byte status = mpu.begin();
    Serial.print("Status MPU6050: ");
    Serial.println(status);

    // Kalibrasi sensor
    Serial.println("Mengkalibrasi MPU...");
    delay(1000);
    mpu.calcOffsets();
    Serial.println("Kalibrasi selesai!");
  }

  void loop() {
    mpu.update();

    if (millis() - lastPrint > 1000) { // biar ngga spam
      float ax = mpu.getAccX();
      float ay = mpu.getAccY();
      float az = mpu.getAccZ();
      float gx = mpu.getGyroX();
      float gy = mpu.getGyroY();
      float gz = mpu.getGyroZ();

      Serial.print(F("ACCEL X: ")); Serial.print(ax);
      Serial.print(F(" Y: "));      Serial.print(ay);
      Serial.print(F(" Z: "));      Serial.println(az);
      Serial.print(F("GYRO  X: ")); Serial.print(gx);
      Serial.print(F(" Y: "));      Serial.print(gy);
      Serial.print(F(" Z: "));      Serial.println(gz);

      String dataMPU = "MPU," + String(ax) + "," + String(ay) + "," + String(az) + "," +
                        String(gx) + "," + String(gy) + "," + String(gz);
      Serial.println(dataMPU);

      lastPrint = millis();
    }
  }
};