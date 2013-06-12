#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>

//Function Declarations :
void adc_init(void);
void disableDigitalInputOnADC(void);
void startSamplingADC(void);
uint8_t stillConverting(void);
uint8_t adcValue(void);

#endif
