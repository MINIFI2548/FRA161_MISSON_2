/*  
    Note : stepper fomura
    Step Delay= 500 micro seconds (500 micro seconds for LOW and 500 microseconds for HIGH)
    Step Duration= 2 x 500 micro seconds = 1000 micro seconds = 0.001 seconds
    Step Frequency (Hz) = 1/Step Duration = 1/ 0.001 =1000 Hz
    Motor Speed (RPM) = (Step Frequency (Hz) x 60 ) / Driver Resolution */
#include <AccelStepper.h>

#define ENB_PIN A0 
#define DIR_PIN A1
#define PUL_PIN A2
#define LIMIT_PIN 13

#define GEAR_RATIO 1/9
#define MAX_SPEED_RPM 100       // RPM
#define MIN_SPEED_RPM 50        // RPM
#define ACCELERATION_RPS 50   //RPS^2
#define PULSE_PER_REV 3200
#define END_STOP_POSITION 0 // step



AccelStepper stepper(AccelStepper::DRIVER, PUL_PIN, DIR_PIN);

const int MAX_SPEED_SPS = MAX_SPEED_RPM  / 60 * PULSE_PER_REV;
const int MIN_SPEED_SPS = MIN_SPEED_RPM  / 60 *  PULSE_PER_REV;
const int ACCELERATION_SPS = ACCELERATION_RPS * PULSE_PER_REV;

int homeStepPosition;
void setup() {
  Serial.begin(115200);

  stepper.setEnablePin(ENB_PIN);
  stepper.setPinsInverted(false, false, false, false, true);
  stepper.enableOutputs();
  stepper.setMinPulseWidth(20);
  stepper.setMaxSpeed(MAX_SPEED_SPS);
  stepper.setAcceleration(ACCELERATION_SPS);
  stepper.setCurrentPosition(0);
  digitalWrite(PUL_PIN, LOW);
  pinMode(LIMIT_PIN, INPUT_PULLUP);

  // home();
  // goToPoint(90);
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
        home();
        break;
      case 2:   //go to
        goToPoint(parameter[0]);
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

void home(){
  stepper.setSpeed(-10 * PULSE_PER_REV);
  while (!digitalRead(LIMIT_PIN)) {
    stepper.runSpeed();
  }
  stepper.stop();
  // Serial.println("done");
  delay(1000);
  gotStep(stepper.currentPosition() + 1000);
  // Serial.println("done");
  delay(1000);
  stepper.setSpeed(-0.5 * PULSE_PER_REV);
  while (!digitalRead(LIMIT_PIN)) {
    stepper.runSpeed();
    // Serial.println((digitalRead(LIMIT_PIN)));
  }
  // Serial.println("done");
  stepper.setCurrentPosition(0);
  homeStepPosition = stepper.currentPosition();
  // Serial.println(homeStepPosition);
}

void goToPoint(int point){
  // float position = (((point) * 180 / 36) * PULSE_PER_REV * 9  / 360) ;
  float position = (((point)) * PULSE_PER_REV / 8) ;
  // Serial.println(position);
  gotStep(position);
}

void gotStep(long position){
  stepper.moveTo(position);
  while (stepper.currentPosition() != stepper.targetPosition()) {
    stepper.runToPosition();
  }
  stepper.stop();
}