#include <inttypes.h>
#include <avr/io.h>
using namespace std;


#define  NUM_STEPS  8

#define E1 6
#define M1 7
#define E2 5
#define M2 4


//typedef void func_ptr
enum step_type {
	SINGLE = 0
};

enum direction {
	BACKWARD = 0,
	FORWARD = 1
};
typedef void (*f_ptr)(void);

class Df_stepper {
  public:
     Df_stepper(uint16_t stepsPerRev);
     void step(uint16_t steps, uint8_t dir,  uint8_t style = SINGLE);
     void setSpeed(uint16_t);
     uint8_t onestep(uint8_t dir, uint8_t style);
     void release(void);
     uint16_t stepsPerRev; // # steps per revolution
     uint8_t steppernum;
     uint32_t microsecs_per_step, steppingcounter;
     //void Step0();
     //void Step1();
     //void Step2();
     //void Step3();
     //void Step4();
     //void Step5();
     //void Step6();
     //void Step7();
     //int *steps[NUM_STEPS];
     f_ptr step_funcs[NUM_STEPS];

     private:
     uint8_t currentstep;

};
