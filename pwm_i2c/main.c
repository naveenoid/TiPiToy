//main.c

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h> 

//#include "adc.h"
#include "led.h"
#include "i2c.h"

extern char status;
//extern char buffer[REG_SIZE];
//extern uint8_t samplingComplete;

void delay_ms(uint16_t count) {
    while(count--) _delay_ms(1);
} 

int main(void){


	//uint8_t *adcPointer;
	//uint16_t adc;	

    	wdt_enable(WDTO_8S); // see silicon errata
	//adc_init();
	//disableDigitalInputOnADC();
    	led_init();
    	cli();
	i2c_init();
	//cli();
    	sei();

	while(1)
    	{
        	wdt_reset();
		
		//led_on();
		//if(samplingComplete){
		//	adcPointer = adcPacket();
		//}
		//buffer[0] = adc;
		//buffer[1] = (adc>>8);	
	
		// Test: Dump I2C status register
        	led_on();
        	_delay_us(10);
        	led_off();
        	for(int i=15; i >= 0; i--)
        	{
           		((OCR1B >> i) & 0x01) ? led_on() : led_off();
           		_delay_ms(1);
        	}
        	led_off();
        	delay_ms(100);

    	}

	return 0;

}
