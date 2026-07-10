#define RELAY_POMPA 25

class Pompa {
  public: 
    Pompa() {
  }

  void setup() {
    pinMode(RELAY_POMPA, OUTPUT);
    digitalWrite(RELAY_POMPA, 1); // 1 = kondisi off, 0 = kondisi on
  }

  void nyalaMatiVakum() {
      digitalWrite(RELAY_POMPA, LOW);  
      delay(5000);             
      digitalWrite(RELAY_POMPA, HIGH); 
      delay(2000);             
    }
};
