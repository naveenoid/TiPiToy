#ifndef _I2C_H
#define _I2C_H

void i2c_init(void);

#define I2C_ADDRESS 0x03 //7 bit address of slave, not left-shifted
#define REG_SIZE 26
#define ADC_DATA_SIZE 22
#define PWM_DATA_SIZE 4

#endif
