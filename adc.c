
#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"

void initializeADC(void){
	ADMUXA = 0x00;
	ADMUXB = (0<<REFS) |			//VCC used as analog reference 
		 (0<<MUX5); 
	ADCSRA = (1<<ADEN) |			//enable ADC
		 (0<<ADSC) |			//don't start conversion now
		 (0<<ADATE) |			//disable ADC auto trigger
		 (0<<ADIF) |
		 (0<<ADIE) |			//need to be decided later
		 (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //128 prescalar
	ADCSRB = (1<<ADLAR) |			//right shifted ADC data register
		 (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); //no need unless ADATE is enabled 
}

/*
to disable digital i/o functionality of ADC pins being used  
*/

void disableDigitalInputOnADC(void){ 		//to be decided later
	DIDR0 = 0x01;
	DIDR1 = 0x00;
	DIDR2 = 0x00;
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
uint16_t adcValue(uint16_t adcMux){		//adcMux decides from which ADC channel sampling is to be done 
	ADMUXA = adcMux;			//check if this will work!!!
	ADMUXB = (adcMux>>8);
	startSamplingADC();
	while(stillConverting());
	ADCSRA |= (1<<ADIF);			//clearing ADC conversion complete flag
	return (ADCL + 256*ADCH);		//according to right shifted ADC data register
}
*/

uint8_t adcValue(void){		//adcMux decides from which ADC channel sampling is to be done 
	//ADMUXA = adcMux;			//check if this will work!!!
	//ADMUXB = (adcMux>>8);
	startSamplingADC();
	while(stillConverting());
	ADCSRA |= (1<<ADIF);			//clearing ADC conversion complete flag
	return (ADCH);		//according to right shifted ADC data register
}
