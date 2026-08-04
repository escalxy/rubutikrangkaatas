#pragma once
#include <Wire.h>
#include <MPU6050_light.h>
#include <ArduinoJson.h>

struct MpuData {
  float ax, ay, az;
  float gx, gy, gz;
};

class Mpu {
  private:
    MPU6050 mpu;

  public:
    Mpu() : mpu(Wire) {}

    void setup() {
      byte status = mpu.begin();
      Serial.print("Status MPU6050: "); Serial.println(status);
      delay(1000);
      mpu.calcOffsets();
    }

    void update() {
      mpu.update();
    }

    MpuData read() {
      MpuData d;
      d.ax = mpu.getAccX() * 9.81;
      d.ay = mpu.getAccY() * 9.81;
      d.az = mpu.getAccZ() * 9.81;
      d.gx = mpu.getGyroX() * PI / 180.0;
      d.gy = mpu.getGyroY() * PI / 180.0;
      d.gz = mpu.getGyroZ() * PI / 180.0;
      return d;
    }
};

QueueHandle_t mpuQueue;

void mpuTask(void *param) { //task RTOS untuk membaca data MPU6050
  Mpu sensorMpu;
  sensorMpu.setup();

  MpuData data; 
  for (;;) {
    sensorMpu.update(); 
    data = sensorMpu.read();
    xQueueOverwrite(mpuQueue, &data);
    vTaskDelay(pdMS_TO_TICKS(20)); //delay 20ms untuk ~50Hz update rate
  }
}

void mpuRtosInit() {
  mpuQueue = xQueueCreate(1, sizeof(MpuData));
  if (mpuQueue == NULL) {
    Serial.println("Gagal bikin queue MPU!");
    while (1) delay(10);
  }
  xTaskCreatePinnedToCore(mpuTask, "MpuTask", 4096, NULL, 1, NULL, 0); // Buat task RTOS untuk membaca data MPU6050
}

void mpuKirimJson() {
  MpuData latest;
  if (xQueuePeek(mpuQueue, &latest, 0) == pdTRUE) {
    JsonDocument doc;
    doc["ax"] = latest.ax;
    doc["ay"] = latest.ay;
    doc["az"] = latest.az;
    doc["gx"] = latest.gx;
    doc["gy"] = latest.gy;
    doc["gz"] = latest.gz;
    serializeJson(doc, Serial);
    Serial.println();
  }
}