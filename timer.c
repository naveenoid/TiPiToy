
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"

#define SERVO1 PC2
#define SERVO2 PC3

//timer for two pwms

void initializeTimer(void){


	DDRC |= _BV(SERVO1) | _BV(SERVO2);
 
	TCCR1A = (1<<COM1A1) | (0<<COM1A0) | //Non-inverting mode
		 (1<<COM1B1) | (0<<COM1B0) |  //i.e. set on compare match, clear at bottom) 
		 (1<<WGM11) | (0<<WGM10);     //mode 14, fast PWM
	TCCR1B = (1<<WGM13) | (1<<WGM12) |
		 (0<<CS12) | (0<<CS11) | (1<<CS10); //No prescalar
	TCCR1C = (0<<FOC1A) | (0<<FOC1B); //disable force output compare
    TOCPMSA0 = (1 << TOCC3S1) | (0 << TOCC3S0); // route OC1A to TOCC3
//	TOCPMSA1 = (RIGHT_PWM_OUT1) | (LEFT_PWM_OUT1); //deciding output pwm pins
//	TOCPMSA0 = (RIGHT_PWM_OUT0) | (LEFT_PWM_OUT0);
    TOCPMCOE = (1 << TOCC3OE); // timer/counter OC pin mux chan. OE

	ICR1 = 20000; // 20000*50 Hz = 1 MHz = CPU-Frequency
	OCR1A = 1000; // Initial position; corresponds to 1 ms

}

void stopPWM(void){

	OCR1A = ICR1;
	OCR1B = ICR1;

}
