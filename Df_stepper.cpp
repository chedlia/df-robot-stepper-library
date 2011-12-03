#include <avr/io.h>
#include "WProgram.h"
#include "Df_stepper.h"
#define PWR 250
#define DELAY 1

void
Step0()
{
	// 0
	digitalWrite(M1,HIGH);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, 0);   //PWM Speed Control
	//delay(DELAY);
}
void
Step1()
{
	// 1
	digitalWrite(M1,HIGH);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, PWR);   //PWM Speed Control
	//delay(DELAY);
}
void
Step2()
{
	// 2
	digitalWrite(M1,HIGH);
	analogWrite(E1, 0);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, PWR);   //PWM Speed Control
	//delay(DELAY);
}
void
Step3()
{
	// 3
	digitalWrite(M1,LOW);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, PWR);   //PWM Speed Control
	//delay(DELAY);
}
void
Step4()
{
	// 4
	digitalWrite(M1,LOW);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, HIGH);
	analogWrite(E2, 0);   //PWM Speed Control
	//delay(DELAY);
}
void
Step5()
{
	// 5
	digitalWrite(M1,LOW);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, LOW);
	analogWrite(E2, PWR);   //PWM Speed Control
	//delay(DELAY);
}
void
Step6()
{
	// 6
	digitalWrite(M1,LOW);
	analogWrite(E1, 0);   //PWM Speed Control

	digitalWrite(M2, LOW);
	analogWrite(E2, PWR);   //PWM Speed Control
	//delay(DELAY);
}
void
Step7()
{
	// 7
	digitalWrite(M1,HIGH);
	analogWrite(E1, PWR);   //PWM Speed Control

	digitalWrite(M2, LOW);
	analogWrite(E2, PWR);   //PWM Speed Control
	//delay(DELAY);
}



Df_stepper::Df_stepper(uint16_t stepsPerRev)
{
	this->stepsPerRev = stepsPerRev;
	currentstep = 7;
	step_funcs[0]= &Step0;
	step_funcs[1]= &Step1;
	step_funcs[2]= &Step2;
	step_funcs[3]= &Step3;
	step_funcs[4]= &Step4;
	step_funcs[5]= &Step5;
	step_funcs[6]= &Step6;
	step_funcs[7]= &Step7;
}

void Df_stepper::stopMotor(void)
{
	digitalWrite(M1,LOW);
	analogWrite(E1, 0);   //PWM Speed Control

	digitalWrite(M2, LOW);
	analogWrite(E2, 0);   //PWM Speed Control
}


void Df_stepper::setSpeed(uint16_t rpm)
{
	//revsteps : gives steps per rev
	//revsteps x rpm = steps taken per min
	//steps take per microsec = (steps take per min)/ 60 x 1000
	//
	uint32_t stepsPerMin = rpm * stepsPerRev;
	millisecs_per_step   =(uint32_t) ( (60000)/(stepsPerMin));
}

int Df_stepper::getCurrentStep(void)
{
	return currentstep;
}

uint8_t Df_stepper::onestep(uint8_t dir, uint8_t style)
{
	int movement;

	if (dir == FORWARD)
	{
		movement = 1;
	} else //BACKWARD
	{
		movement = -1;
	}
	currentstep = (((uint8_t)(currentstep + movement)) % NUM_STEPS);
	(step_funcs[currentstep])();

	delay(millisecs_per_step);
	//delay(DELAY);
}

void Df_stepper::step(uint16_t steps, uint8_t dir, uint8_t style)
{

	for (int i=0; i< steps; i++)
	{
		onestep(dir, style);
	}
	stopMotor();
}
