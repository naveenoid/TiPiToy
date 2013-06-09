
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
        led_toggle();
        _delay_ms(500);
    }

	return 0;

}
