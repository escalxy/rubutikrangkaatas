#include <Arduino.h>
#include <ArduinoJson.h>   
#include <Wire.h>
#include "mpu.h"
#include "katup-pompa.h"   
#include "servo.h"
#include "motor.h"

// Servo
#define SERVO_PIN 15 //deklarasi pin servo

// Lengan
#define PIN_AIN1 33 //deklarasi pin motor driver
#define PIN_AIN2 23
#define PIN_PMW 32

// Relay
#define RELAY_KATUP 27 //deklarasi pin relay
#define RELAY_POMPA 26

// MPU6050
#define SDA_PIN 21 //deklarasi pin MPU6050
#define SCL_PIN 22  

//deklarasi fungsi untuk mengontrol servo, motor, dan katup vakum
Mpu sensorMpu;
katupVakum vakum;              
gerakServo servo;
GerakMotor lengan;

String input = "";

void setup() {
  Serial.begin(115200); //baud rate untuk komunikasi serial
  mpuRtosInit();
  Wire.begin(SDA_PIN, SCL_PIN); // inisialisasi komunikasi I2C untuk MPU6050
  sensorMpu.setup(); // inisialisasi sensor MPU6050
  vakum.setup(RELAY_KATUP, RELAY_POMPA); // inisialisasi katup vakum dan pompa
  servo.setup(SERVO_PIN); // inisialisasi servo
  lengan.setup(PIN_AIN1, PIN_AIN2, PIN_PMW); // inisialisasi motor lengan
}

void perintah(String cmd) { //fungsi untuk memproses perintah yang diterima dari ROS
  JsonDocument doc;  
  DeserializationError error = deserializeJson(doc, cmd);

  if (error) {
    Serial.print("Gagal parse JSON (");
    Serial.print(error.c_str());
    Serial.println("): " + cmd);
    return;
  }

  if (!doc["v"].isNull()) { //perintah vakum
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

  if (!doc["s"].isNull()) { //perintah servo
    int s = doc["s"];
    if (s == 1) {
      Serial.println("-> servo naik");
      servo.setArah(1);
    } else if (s == -1) {
      Serial.println("-> servo turun");
      servo.setArah(-1);
    } else if (s == 0) {
      Serial.println("-> servo stop");
      servo.setArah(0);
    } else {
      Serial.println("Nilai servo tidak valid (harus -1/0/1): " + String(s));
    }
  }

  if (!doc["st"].isNull() || !doc["m"].isNull()) { //perintah motor lengan
    int m = !doc["st"].isNull() ? doc["st"] : doc["m"];
    if (m == 1) {
      Serial.println("-> lengan maju");
      lengan.setArah(1);
    } else if (m == -1) {
      Serial.println("-> lengan mundur");
      lengan.setArah(-1);
    } else if (m == 0) {
      Serial.println("-> lengan stop");
      lengan.setArah(0);
    } else {
      Serial.println("Nilai motor tidak valid (harus -1/0/1): " + String(m));
    }
  }
}

void bacaSerial() { //fungsi untuk membaca perintah dari ROS lewat komunikasi serial
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
  mpuKirimJson(); // kirim data MPU6050 ke ROS
  bacaSerial(); // terima command dari ROS lewat Serial (USB)
  lengan.update(); 
  servo.update();   
}

