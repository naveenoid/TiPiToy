#ifndef _I2C_H
#define _I2C_H

void i2c_init(void);

#define I2C_ADDRESS 0x03 //7 bit address of slave, not left-shifted
#define REG_SIZE 24

#endif
