#include <ArduinoJson.h>   
#include "mpu.h"
#include "katup-pompa.h"   
#include "servo.h"
#include "motor.h"

// Servo
#define SERVO_PIN 15

// Lengan
#define PIN_AIN1 21
#define PIN_AIN2 19
#define PIN_PWMA 18

// Relay
#define RELAY_KATUP 27
#define RELAY_POMPA 26
#define LED 2

Mpu sensorMpu;
katupVakum vakum;              
gerakServo servo;
GerakMotor lengan;

String input = "";

void setup() {
  Serial.begin(9600);   
  pinMode(LED, OUTPUT);
  sensorMpu.setup();
  vakum.setup(RELAY_KATUP, RELAY_POMPA);
  servo.setup(SERVO_PIN);
  lengan.setup(PIN_AIN1, PIN_AIN2, PIN_PWMA);
}

void perintah(String cmd) {
  JsonDocument doc;  
  DeserializationError error = deserializeJson(doc, cmd);

  if (error) {
    Serial.print("Gagal parse JSON (");
    Serial.print(error.c_str());
    Serial.println("): " + cmd);
    return;
  }

  if (!doc["v"].isNull()) {
    int v = doc["v"];
    if (v == 1) {
      Serial.println("-> vakum nyala");
      vakum.nyalabukaVakum();
    } else if (v == 0) {
      Serial.println("-> vakum mati");
      vakum.matitutupVakum();
    } else {
      Serial.println("Nilai v tidak valid (harus 0/1): " + String(v));
    }
  }

  if (!doc["s"].isNull()) {
    float s = doc["s"];
    servo.gerakKe((int)round(s)); // otomatis di-clamp 0-180 di dalam method-nya
  }

  if (!doc["m"].isNull()) {
    int m = doc["m"];
    if (m == 1) {
      Serial.println("-> lengan maju");
      lengan.setArah(1);
      digitalWrite(LED, HIGH);
    } else if (m == -1) {
      Serial.println("-> lengan mundur");
      lengan.setArah(-1);
    } else if (m == 0) {
      Serial.println("-> lengan stop");
      lengan.setArah(0);
      digitalWrite(LED, LOW);
    } else {
      Serial.println("Nilai m tidak valid (harus -1/0/1): " + String(m));
    }
  }
}

void bacaSerial() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();  // Buang \r atau spasi

    if (input.length() > 0) {
      Serial.print("[Input] ");
      Serial.println(input);
      
      perintah(input);
    }
  }
}

void loop() {
  sensorMpu.loop();  // kirim data MPU ke ROS lewat Serial (USB)
  bacaSerial();       // terima command dari ROS lewat Serial (USB)
  lengan.update();    // WAJIB: cek limit switch untuk auto-stop motor DC
}