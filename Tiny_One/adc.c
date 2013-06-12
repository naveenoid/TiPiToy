//adc.c

#include <avr/io.h>

#include "adc.h"
#include "i2c.h"

uint8_t dataPacketSent = 1;
uint8_t buffer[REG_SIZE];			//REG_SIZE defined in i2c.h

void adc_init(void){

	DDRA |= 0x00;				//PORT initializations for ADC0 to ADC21 (except PC6 and PC7)
	DDRB |= 0x00;
	DDRC |= 0X00;

	ADMUXA = 0x00;
	ADMUXB = (0<<REFS) |			//VCC used as analog reference 
		 (0<<MUX5); 
	ADCSRA = (1<<ADEN) |			//enable ADC
		 (0<<ADSC) |			//don't start conversion now
		 (0<<ADATE) |			//disable ADC auto trigger
		 (0<<ADIF) |
		 (0<<ADIE) |			//need to be decided later
		 (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0); //16 prescalar
	ADCSRB = (1<<ADLAR) |			//left shifted ADC data register
		 (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); //no need unless ADATE is enabled 
}

/*
to disable digital i/o functionality of ADC pins being used  
*/

void disableDigitalInputOnADC(void){ 		//adc channels used from ADC0 to ADC21
	DIDR0 = 0xff;
	DIDR1 = 0xff;
	DIDR2 = 0x3f;
	DIDR3 = 0x00;
}

void startSamplingADC(void){
	ADCSRA |= (1<<ADSC);
}

uint8_t stillConverting(void){
	if(ADCSRA & (1<<ADSC)) {
		return 1;
	}
	return 0;
}

/*
uint16_t adcValue(void){	 
	
	startSamplingADC();
	while(stillConverting());
	ADCSRA |= (1<<ADIF);			//clearing ADC conversion complete flag
	return (ADCL + 256*ADCH);		//according to right shifted ADC data register
}
*/

uint8_t adcValue(void){	 

	startSamplingADC();
	while(stillConverting());
	ADCSRA |= (1<<ADIF);			//clearing ADC conversion complete flag
	return (ADCH);				//according to left shifted ADC data register

}

uint8_t *adcPacket(void){		 
	
	dataPacketSent = 0;
	ADMUXA = 0x00;			
	for(int i =0; i<ADC_DATA_SIZE; i++){
		
		buffer[i] = adcValue();
		ADMUXA++;
		
	}
	
	return buffer;	
}




