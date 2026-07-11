#define RELAY_KATUP 26
#define RELAY_POMPA 25

class katupVakum {
  public: 
    katupVakum() {}

  void setup() {
    pinMode(RELAY_KATUP, OUTPUT);
    pinMode(RELAY_POMPA, OUTPUT);
    digitalWrite(RELAY_POMPA, 1); // 1 = kondisi off, 0 = kondisi on
    digitalWrite(RELAY_KATUP, 1); // 1 = kondisi off, 0 = kondisi on
  }

  void bukaKatup() {
      digitalWrite(RELAY_KATUP, LOW);                           
    }

  void tutupKatup() {          
      digitalWrite(RELAY_KATUP, HIGH);              
    }

  void matiVakum() {
      digitalWrite(RELAY_POMPA, LOW);                    
    }

  void nyalaVakum() {    
      digitalWrite(RELAY_POMPA, HIGH);            
    }
};
