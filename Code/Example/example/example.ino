/*  Step Delay= 500 micro seconds (500 micro seconds for LOW and 500 microseconds for HIGH)
    Step Duration= 2 x 500 micro seconds = 1000 micro seconds = 0.001 seconds
    Step Frequency (Hz) = 1/Step Duration = 1/ 0.001 =1000 Hz
    Motor Speed (RPM) = (Step Frequency (Hz) x 60 ) / Driver Resolution */
#include <AccelStepper.h>

#define ENB_PIN 2 
#define DIR_PIN 3
#define PUL_PIN 4 

#define MAX_SPEED 

int parameter[5];

void setup() {
  Serial.begin(115200);
}

void  loop() {
  if(Serial.available()) {
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
  }
}