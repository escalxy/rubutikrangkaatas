#define RELAY_KATUP 26
#define RELAY_POMPA 25

class katupVakum {
  public: 
    katupVakum() {}

  void setup() {
    pinMode(RELAY_KATUP, OUTPUT);
    pinMode(RELAY_POMPA, OUTPUT);
    digitalWrite(RELAY_POMPA, 0); // 1 = kondisi off, 0 = kondisi on
    digitalWrite(RELAY_KATUP, 0); // 1 = kondisi off, 0 = kondisi on
  }

  void nyalabukaVakum() {    
      digitalWrite(RELAY_POMPA, HIGH);   
      digitalWrite(RELAY_KATUP, LOW);         
    }

  void matitutupVakum() {
      digitalWrite(RELAY_POMPA, LOW);
      digitalWrite(RELAY_KATUP, HIGH);                    
    }

  
};
