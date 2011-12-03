#include "Df_stepper.h"


Df_stepper motor(800);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("#############Stepper test!");

  motor.setSpeed(10);  // 10 rpm   
  Serial.print(motor.stepsPerRev);
  Serial.print(motor.millisecs_per_step);
}

void loop() {
  int i;
  Serial.println("Single coil steps");
  motor.step(1000, BACKWARD);
  Serial.println("Step1=");
  Serial.print(motor.getCurrentStep());
  delay(1000);
  motor.step(1000, FORWARD);
  Serial.println("Step2=");
  Serial.print(motor.getCurrentStep());
  delay(2000);
}


