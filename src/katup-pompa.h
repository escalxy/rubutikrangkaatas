class katupVakum {
  private:
    uint8_t pinKatup; // Pin untuk relay katup
    uint8_t pinPompa; // Pin untuk relay pompa

  public:
    katupVakum() {}

    void setup(uint8_t relayKatupPin, uint8_t relayPompaPin) { //fungsi untuk menginisialisasi pin relay katup dan pompa
      pinKatup = relayKatupPin;
      pinPompa = relayPompaPin;

      pinMode(pinKatup, OUTPUT); // Set pin relay katup dan katup sebagai output
      pinMode(pinPompa, OUTPUT);

      digitalWrite(pinPompa, HIGH); // 1 = kondisi off
      digitalWrite(pinKatup, HIGH); // 1 = kondisi off
    }

    void nyalabukaVakum() { //fungsi untuk menyalakan pompa dan membuka katup vakum
      digitalWrite(pinPompa, LOW);
      digitalWrite(pinKatup, HIGH);
    }

    void matitutupVakum() { //fungsi untuk mematikan pompa dan menutup katup vakum
      digitalWrite(pinPompa, HIGH);
      digitalWrite(pinKatup, LOW);
    }
};