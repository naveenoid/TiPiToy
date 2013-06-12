//timer.h

#include <avr/io.h>

//deciding output pwm pins....to be decided later
#define RIGHT_PWM_OUT1 0x00
#define RIGHT_PWM_OUT0 0x00
#define LEFT_PWM_OUT1 0x00
#define LEFT_PWM_OUT0 0xb0

//deciding the compare match point
#define RIGHT_OCR 19999-10000
#define LEFT_OCR 19999-10000

//deciding the top value of count
#define TOP_VAL 0x4e1f  //19999

//PWM output PORT
#define SERVO1 PC6
#define SERVO2 PC7

//Function declarations
void initializeTimer(void);
void stopPWM(void);
