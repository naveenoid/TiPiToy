
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"

//timer for two pwms

void initializeTimer(void){

	TCCR1A = (1<<COM1A1) | (0<<COM1A0) | //Non-inverting mode
		 (1<<COM1B1) | (0<<COM1B0);  //i.e. set on compare match, clear at bottom) 
		 (1<<WGM11) | (0<<WGM10);     //mode 12, CTC mode
	TCCR1B = (1<<WGM13) | (0<<WGM12) |
		 (0<<CS12) | (0<<CS11) | (1<<CS10); //No prescalar
	TCCR1C = (0<<FOC1A) | (0<<FOC1B); //disable force output compare
	TOCPMSA1 = (RIGHT_PWM_OUT1) | (LEFT_PWM_OUT1); //deciding output pwm pins
	TOCPMSA0 = (RIGHT_PWM_OUT0) | (LEFT_PWM_OUT0);

	TCNT1 = 0x0000; //timer starts from 0
	
	OCR1A = RIGHT_OCR;
	OCR1B = LEFT_OCR;

	ICR1 = TOP_VAL;

}

void stopPWM(void){

	OCR1A = ICR1;
	OCR1B = ICR1;

}
