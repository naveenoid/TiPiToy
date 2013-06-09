
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h> 

#include "timer.h"
#include "led.h"
#include "i2c.h"

extern char status;

void delay_ms(uint16_t count) {
    while(count--) _delay_ms(1);
} 

int main(void){
    wdt_enable(WDTO_8S); // see silicon errata
	initializeTimer();
    led_init();
    i2c_init();
    sei();

	while(1)
    {
        wdt_reset();

// Test: Dump I2C status register
        led_on();
        _delay_us(10);
        led_off();
        for(int i=7; i >= 0; i--)
        {
           ((status >> i) & 0x01) ? led_on() : led_off();
           _delay_ms(1);
        }
        led_off();
        delay_ms(100);

// Test: slide PWM duty cycle from 1 ms to 2ms
//        OCR1A++;
//        if(OCR1A > 2000) OCR1A = 1000;
    }

	return 0;

}
