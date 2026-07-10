#define RELAY_KATUP 26

class Katup {
  public: 
    Katup() {
  }

  void setup() {
    pinMode(RELAY_KATUP, OUTPUT);
    digitalWrite(RELAY_KATUP, 1); // 1 = kondisi off, 0 = kondisi on
  }

  void bukaTutupKatup() {
      digitalWrite(RELAY_KATUP, LOW);  
      delay(5000);             
      digitalWrite(RELAY_KATUP, HIGH); 
      delay(2000);             
    }
};
