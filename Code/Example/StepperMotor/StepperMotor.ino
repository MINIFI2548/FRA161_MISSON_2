#include <AccelStepper.h>

#define enbPin 2
#define dirPin 3
#define pulPin 4

AccelStepper stepper(AccelStepper::DRIVER, pulPin, dirPin);


void setup() {
  Serial.begin(115200);
  stepper.setMaxSpeed(2000); // ตั้งค่าความเร็วสูงสุด
  stepper.setAcceleration(500); // ตั้งค่าความเร่ง  

  stepper.setSpeed(900);
}

void loop() {
  stepper.runSpeed();
}
