/*  
    Note : stepper fomura
    Step Delay= 500 micro seconds (500 micro seconds for LOW and 500 microseconds for HIGH)
    Step Duration= 2 x 500 micro seconds = 1000 micro seconds = 0.001 seconds
    Step Frequency (Hz) = 1/Step Duration = 1/ 0.001 =1000 Hz
    Motor Speed (RPM) = (Step Frequency (Hz) x 60 ) / Driver Resolution */
#include <AccelStepper.h>

#define SPIN_ENB_PIN A2 
#define SPIN_DIR_PIN A1
#define SPIN_PUL_PIN A0

#define PEN_ENB_PIN A5
#define PEN_DIR_PIN A4
#define PEN_PUL_PIN A3

#define LIMIT_PIN 13

#define GEAR_RATIO 1/9
#define MAX_SPEED_RPM 15000       // RPM
#define MIN_SPEED_RPM 50        // RPM
#define ACCELERATION_RPS 500000   //RPS^2
#define PULSE_PER_REV 3200
#define END_STOP_POSITION 0 // step

bool homed = false;


AccelStepper stepper(AccelStepper::DRIVER, SPIN_PUL_PIN, SPIN_DIR_PIN);
AccelStepper pen(AccelStepper::DRIVER, PEN_PUL_PIN, PEN_DIR_PIN);

const int MAX_SPEED_SPS = MAX_SPEED_RPM  / 60 * PULSE_PER_REV;
const int MIN_SPEED_SPS = MIN_SPEED_RPM  / 60 *  PULSE_PER_REV;
const int ACCELERATION_SPS = ACCELERATION_RPS * PULSE_PER_REV;

int homeStepPosition;
void setup() {
  Serial.begin(115200);

  stepper.setEnablePin(SPIN_ENB_PIN);
  stepper.setPinsInverted(false, false, false, false, true);
  stepper.enableOutputs();
  stepper.setMinPulseWidth(20);
  stepper.setMaxSpeed(MAX_SPEED_SPS);
  stepper.setAcceleration(ACCELERATION_SPS);
  stepper.setCurrentPosition(0);

  pen.setEnablePin(PEN_ENB_PIN);
  pen.setPinsInverted(false, false, true);
  pen.enableOutputs();
  pen.setMinPulseWidth(20);
  pen.setMaxSpeed(3200);
  pen.setAcceleration(9000);
  pen.setCurrentPosition(0);

  digitalWrite(SPIN_PUL_PIN, LOW);
  digitalWrite(PEN_PUL_PIN, LOW);
  pinMode(LIMIT_PIN, INPUT_PULLUP);

  // repeatGoto(10800, 10);
  // penDown();
  // home();
  // goToPoint(90);
  // motorOff();
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
    motorOn();
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
        repeatGoto(parameter[0], parameter[1]);
        break;
      case 4:   //motor off 
        motorOff();
        break;
      case 5:   //motor on 
        motorOn();
        break;
      case 6 : 
        penDown();
        break;
    }
  }
}

void motorOff(){
    stepper.disableOutputs();
    pen.disableOutputs();
}
void motorOn(){
    stepper.enableOutputs();
    pen.enableOutputs();
}

void home(){
  if (homed) {
    gotoStep(300);
  }
  stepper.setSpeed(-500);
  while (digitalRead(LIMIT_PIN)) {
    stepper.runSpeed();
  }
  stepper.stop();
  // Serial.println("done");
  delay(100);
  stepper.setSpeed(400);
  while (!digitalRead(LIMIT_PIN)) {
    stepper.runSpeed();
  }
  stepper.stop();
  // gotoStep(stepper.currentPosition() + 500);
  // Serial.println("done");
  delay(100);
  stepper.setSpeed(-200);
  while (digitalRead(LIMIT_PIN)) {
    stepper.runSpeed();
    // Serial.println((digitalRead(LIMIT_PIN)));
  }
  delay(500);
  // Serial.println("done");
  stepper.setCurrentPosition(0);
  homeStepPosition = stepper.currentPosition();
  // Serial.println(homeStepPosition);
  homed = true;
}

void goToPoint(int point){
  gotoStep(point);
  // penDown();
}

void repeatGoto(int point, int time){
  for(int i = 0; i < time; i++){
    home();
    goToPoint(point);
    delay(1000);
    penDown();
    delay(1000);
    gotoStep(300);
  }
}

void gotoStep(long position){
  stepper.moveTo(position);
  while (stepper.currentPosition() != stepper.targetPosition()) {
    stepper.runToPosition();
  }
  stepper.stop();
}

void penDown(){
  pen.moveTo(400);
  while (pen.currentPosition() != pen.targetPosition()) {
    pen.runToPosition();
  }
  pen.stop();
  delay(200);
  pen.moveTo(0);
  while (pen.currentPosition() != pen.targetPosition()) {
    pen.runToPosition();
  }
  pen.stop();
}