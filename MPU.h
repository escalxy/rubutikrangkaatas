#include <Wire.h>
#include <MPU6050_light.h>

unsigned long lastPrint = 0;
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
    Serial.println("Mengkalibrasi Gyro, JANGAN GERAKKAN ROBOT...");
    delay(1000);
    mpu.calcOffsets(); 
    Serial.println("Kalibrasi selesai!");
    }

  void loop() {
    mpu.update();

    if (millis() - lastPrint > 1000) { //biar ngga spam
      
      Serial.print(F("ACCELERO  X: "));Serial.print(mpu.getAccX()); //accelerometer
      Serial.print("\tY: ");Serial.print(mpu.getAccY());
      Serial.print("\tZ: ");Serial.println(mpu.getAccZ());

      Serial.print(F("GYRO      X: "));Serial.print(mpu.getGyroX()); //gyroscope
      Serial.print("\tY: ");Serial.print(mpu.getGyroY());
      Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
      
      lastPrint = millis(); // Reset timer
    }
  }
};