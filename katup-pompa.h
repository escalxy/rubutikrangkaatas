class katupVakum {
  private:
    uint8_t pinKatup;
    uint8_t pinPompa;

  public:
    katupVakum() {}

    void setup(uint8_t relayKatupPin, uint8_t relayPompaPin) {
      pinKatup = relayKatupPin;
      pinPompa = relayPompaPin;

      pinMode(pinKatup, OUTPUT);
      pinMode(pinPompa, OUTPUT);

      digitalWrite(pinPompa, HIGH); // 1 = kondisi off
      digitalWrite(pinKatup, HIGH); // 1 = kondisi off
    }

    void nyalabukaVakum() {
      digitalWrite(pinPompa, HIGH);
      digitalWrite(pinKatup, LOW);
    }

    void matitutupVakum() {
      digitalWrite(pinPompa, LOW);
      digitalWrite(pinKatup, HIGH);
    }
};