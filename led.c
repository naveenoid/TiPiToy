#include "led.h"
#include <avr/io.h>

#define PIN _BV(PC1)

void led_init()
{
    DDRC = PIN;
}


void led_on()
{
    PORTC |= PIN;
}

void led_off()
{
    PORTC &= ~ PIN;
}

void led_toggle()
{
    PORTC ^= PIN;
}
