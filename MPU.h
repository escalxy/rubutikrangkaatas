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
    Serial.println("Mengkalibrasi MPU...");
    delay(1000);
    mpu.calcOffsets(); 
    Serial.println("Kalibrasi selesai!");
    }

  void loop() {
    mpu.update();

    if (millis() - lastPrint > 1000) { //biar ngga spam
      
      String dataMPU = "MPU," + Serial.print(F("ACCELERO  X: ")) + 
          Serial.print(mpu.getAccX()) + "," + 
          Serial.print(mpu.getAccY()) + "," + 
          Serial.println(mpu.getAccZ()); //accelerometer
          Serial.print(F("GYRO      X: ")) + 
          Serial.print(mpu.getGyroX()) + "," + 
          Serial.print(mpu.getGyroY()) + "," + 
          Serial.println(mpu.getGyroZ()); //gyro
          
      Serial2.println(dataMPU); // Send data to Serial2
      lastPrint = millis(); // Reset timer
    }
  }
};