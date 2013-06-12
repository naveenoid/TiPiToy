//i2c.c

#include <avr/io.h>
#include <avr/interrupt.h>

#include "i2c.h"
#include "led.h"
//#define I2C_ADDRESS 0x03 // 7 bit address of slave, not left-shifted
//#define REG_SIZE 2

char status; // FIXME: For debugging
uint8_t write_index, read_index;
extern uint8_t buffer[REG_SIZE];
extern uint8_t dataPacketSent;

void i2c_init(void){

    	TWSCRA = _BV(TWDIE) | _BV(TWASIE) | _BV(TWSIE) | _BV(TWEN); // Enable data, address & stop interrupt, turn TWI module on
    	TWSA = (I2C_ADDRESS << 1);
}

void i2c_send_ack(void){

    	TWSCRB = _BV(TWCMD1) | _BV(TWCMD0);
}

void i2c_send_nack(void){

    	TWSCRB = _BV(TWAA) | _BV(TWCMD1) | _BV(TWCMD0);
}

ISR(TWI_SLAVE_vect){

    	status = TWSSRA;
    	if( (TWSSRA & _BV(TWDIR)) && (TWSSRA & _BV(TWDIF)) ){ // sending data

        	TWSD = buffer[read_index];
        	if(read_index+1 < REG_SIZE)
        	{
        		read_index++;
        		i2c_send_ack();
        	}
        	else
        	{
            		i2c_send_nack();
			dataPacketSent = 1;
        	}
    	}
    	
	else if( (TWSSRA & _BV(TWASIF)) && ( TWSSRA & _BV(TWAS)) ){ // we have been addressed
    	
        	read_index = 0;
		write_index = ADC_DATA_SIZE;
        	i2c_send_ack();
    	}
    
	else if(TWSSRA & _BV(TWDIF)){ // receiving data
    
        	if(write_index < REG_SIZE){

            		buffer[write_index++] = TWSD;
            		i2c_send_ack();
        	}
        	else{

            		i2c_send_nack();
        	}
    	}
   
 	else if( TWSSRA & _BV(TWASIF)){ // stop condition
  
        	i2c_send_nack();
        	uint16_t tmpA = (buffer[ADC_DATA_SIZE] << 8) | buffer[ADC_DATA_SIZE + 1];
        	uint16_t tmpB = (buffer[ADC_DATA_SIZE + 2] << 8) | buffer[ADC_DATA_SIZE + 3];
		OCR1A = tmpA;
		OCR1B = tmpB;
    	}
    
	else{ // anything else
    	
        	i2c_send_nack();
    	}

}
