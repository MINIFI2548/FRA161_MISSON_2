/*  
    Note : stepper fomura
    Step Delay= 500 micro seconds (500 micro seconds for LOW and 500 microseconds for HIGH)
    Step Duration= 2 x 500 micro seconds = 1000 micro seconds = 0.001 seconds
    Step Frequency (Hz) = 1/Step Duration = 1/ 0.001 =1000 Hz
    Motor Speed (RPM) = (Step Frequency (Hz) x 60 ) / Driver Resolution */
#include <AccelStepper.h>

#define ENB_PIN 2 
#define DIR_PIN 3
#define PUL_PIN 4 

#define GEAR_RATIO 0.2
#define MAX_SPEED_RPM 300       // RPM
#define MIN_SPEED_RPM 50        // RPM
#define ACCELERATION_RPM 5000   // RPM^2
#define PULSE_PER_REV 200
#define END_STOP_POSITION 0 // step

AccelStepper stepper(AccelStepper::DRIVER, PUL_PIN, DIR_PIN);

const int MAX_SPEED_SPS = MAX_SPEED_RPM / 60 * PULSE_PER_REV;
const int MIN_SPEED_SPS = MIN_SPEED_RPM / 60 * PULSE_PER_REV;
const int ACCELERATION_SPS = MIN_SPEED_RPM / 3600 * PULSE_PER_REV;

void setup() {
  Serial.begin(115200);

  stepper.setEnablePin(ENB_PIN);
  stepper.setPinsInverted(false, false, false, false, true);
  stepper.enableOutputs();
  stepper.setAcceleration(ACCELERATION_SPS);
  stepper.setMaxSpeed(MAX_SPEED_SPS);
}

void  loop() {
  if(Serial.available()) {
    int parameter[5];
    int funcCase = Serial.read();
    Serial.print("function name : ");
    Serial.println(funcCase);
    int index = 0;
    while (Serial.available() > 0) {
      parameter[index] = Serial.read() << 8 | Serial.read();
      Serial.print("parameter ");
      Serial.print(index + 1);
      Serial.print(" : ");
      Serial.println(parameter[index]);
      index += 1; 
    }
    switch (funcCase) {
      case 0:   //get info
        break;
      case 1:   //home
        break;
      case 2:   //go to
        break;
      case 3:   //repeat go to
        break;
      case 4:   //motor off 
        motorOff();
        break;
      case 5:   //motor on 
        motorOn();
        break;
    }
  }
}

void motorOff(){
    stepper.disableOutputs();
}
void motorOn(){
    stepper.enableOutputs();
}