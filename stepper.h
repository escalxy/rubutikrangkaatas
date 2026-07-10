#include <AccelStepper.h>

#define PIN_DIR 8
#define PIN_STEP 9
#define PIN_ENABLE 10

#define STEPS_PER_REV 200
#define MICROSTEPPING 16
#define PITCH (47.14 * 2)  
#define STEPS_PER_MM (STEPS_PER_REV * MICROSTEPPING / PITCH)

class GerakStepper {
  private:
    AccelStepper stepper; 

  public:
    GerakStepper() : stepper(AccelStepper::DRIVER, PIN_STEP, PIN_DIR) {
    }

    void setup() {
      pinMode(PIN_ENABLE, OUTPUT);
      digitalWrite(PIN_ENABLE, HIGH); // Matikan motor saat idle
      
      stepper.setMaxSpeed(500);
      stepper.setAcceleration(3000);
    }

    void gerak(float jarak) {
      int steps = jarak * STEPS_PER_MM;
      digitalWrite(PIN_ENABLE, LOW); 
      
      stepper.moveTo(steps); 

      while (stepper.distanceToGo() != 0) {
          stepper.run(); 
      }

      digitalWrite(PIN_ENABLE, HIGH);  
    }
};