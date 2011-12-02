#include <avr/io.h>
#include "WProgram.h"
#include "Df_stepper.h"
#define PWR 255
#define DELAY 10

void
Step0()
{
	// 0
	digitalWrite(M1,HIGH);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, 0);   //PWM Speed Control
	delay(DELAY);
}
void
Step1()
{
	// 1
	digitalWrite(M1,HIGH);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, PWR);   //PWM Speed Control
	delay(DELAY);
}
void
Step2()
{
	// 2
	digitalWrite(M1,HIGH);
	analogWrite(E1, 0);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, PWR);   //PWM Speed Control
	delay(DELAY);
}
void
Step3()
{
	// 3
	digitalWrite(M1,LOW);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, PWR);   //PWM Speed Control
	delay(DELAY);
}
void
Step4()
{
	// 4
	digitalWrite(M1,LOW);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, 0);   //PWM Speed Control
	delay(DELAY);
}
void
Step5()
{
	// 5
	digitalWrite(M1,LOW);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, LOW);
	analogWrite(E2, PWR);   //PWM Speed Control
	delay(DELAY);
}
void
Step6()
{
	// 6
	digitalWrite(M1,LOW);
	analogWrite(E1, 0);   //PWM Speed Control

	digitalWrite(M2, LOW);
	analogWrite(E2, PWR);   //PWM Speed Control
	delay(DELAY);
}
void
Step7()
{
	// 7
	digitalWrite(M1,HIGH);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, LOW);
	analogWrite(E2, PWR);   //PWM Speed Control
	delay(DELAY);
}



Df_stepper::Df_stepper(uint16_t stepsPerRev)
{
	this->stepsPerRev = stepsPerRev;
	currentstep = 0;
	step_funcs[0]= &Step0;
	//step_funcs.push_back(&Step1);
	//step_funcs.push_back(&Step2);
	//step_funcs.push_back(&Step3);
	//step_funcs.push_back(&Step4);
	//step_funcs.push_back(&Step5);
	//step_funcs.push_back(&Step6);
	//step_funcs.push_back(&Step7);
}

void Df_stepper::setSpeed(uint16_t rpm)
{
	//revsteps : gives steps per rev
	//revsteps x rpm = steps taken per min
	//steps take per microsec = (steps take per min)/ 60 x 1000
	//
	uint32_t stepsPerMin = rpm * stepsPerRev;
	microsecs_per_step = (stepsPerMin * rpm) / (60 * 1000);
}

uint8_t Df_stepper::onestep(uint8_t dir, uint8_t style)
{
	int movement;
	int currentstep;

	if (dir = FORWARD)
	{
		movement = 1;
	} else //BACKWARD
	{
		movement = -1;
	}
	currentstep = (currentstep + movement) % NUM_STEPS;
	(step_funcs[currentstep])();

	delay(microsecs_per_step);
}

void Df_stepper::step(uint16_t steps, uint8_t dir, uint8_t style)
{

	for (int i=0; i< steps; i++)
	{
		onestep(dir, style);
	}
}


