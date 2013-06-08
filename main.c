
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "timer.h"
#include "led.h"

#define SERVO1 PC2
#define SERVO2 PC3

int main(void){

	DDRC = _BV(SERVO1) | _BV(SERVO2);
	cli();
	sei();
	initializeTimer();
    led_init();
	//_delay_ms(5000);
	//stopPWM();

	while(1)
    {
        led_toggle();
        _delay_ms(500);
    }

	return 0;

}

ISR(TIMER1_OVF_vect){

        TCNT1 = 0x0000;


}

