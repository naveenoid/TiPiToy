
#include <avr/io.h>
#include <util/delay.h>

#include "timer.h"
#include "led.h"
#include "i2c.h"

volatile char status = 85;

void delay_ms(uint16_t count) {
    while(count--) _delay_ms(1);
} 

int main(void){
	initializeTimer();
    led_init();
    i2c_init();
    sei();
	//_delay_ms(5000);
	//stopPWM();

	while(1)
    {
        led_toggle();
        _delay_ms(500);
    }

	return 0;

}
