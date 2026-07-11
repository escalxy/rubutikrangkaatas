#include "MPU.h"
#include "pompa.h"
#include "servo.h"
#include "stepper.h"

#define TX2_PIN 18       // TX2 (output ke ESP, optional if ESP needs feedback)
#define RX2_PIN 19

Mpu sensorMpu;
katupVakum katupVakum;
gerakServo servo; 
GerakStepper lengan;

String input = "";

void setup() {
  Serial.begin(9600);         // Debugging via USB
  Serial2.begin(9600);        // Komunikasi dengan Rasp
  Serial2.println(">> Koneksi berhasil ke ESP");

  sensorMpu.setup();
  katupVakum.setup();
  servo.setup();
  lengan.setup();

}

void perintah(String perintah) {
  if (perintah == "l1") {
    Serial.println("....");
    servo.gerakKanan();
    } 
  else if (perintah == "r1") {
    Serial.println("...");
    servo.gerakKiri();
    } 
  else if (perintah == "l2") {
    Serial.println("...");
    lengan.gerak(100.0); //maju
    } 
  else if (perintah == "r2") {
    Serial.println("...");
    lengan.gerak(-100.0); //mundur
   } 
  else if (perintah == "circle") {
    Serial.println("....");
    katupVakum.nyalabukaVakum();
  }
  else if (perintah == "circle") {
    Serial.println("....");
    katupVakum.matitutupVakum();
  }
  else {
    Serial.println("Perintah tidak dikenal: " + perintah);
    }
}

void bacaSerial(HardwareSerial& port) {
  if (port.available()) {
    input = port.readStringUntil('\n');
    input.trim();  // Buang \r atau spasi
  }
    else if (input.length() > 0) {
      Serial.print("[Input ");
      Serial.print(&port == &Serial ? "USB" : "ESP");
      Serial.print("] ");
      Serial.println(input);
    }
}

void loop () {
    sensorMpu.loop();
    bacaSerial(Serial);   // dari USB
    bacaSerial(Serial2);  // dari Raspi
}