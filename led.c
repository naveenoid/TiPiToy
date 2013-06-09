#include "led.h"
#include <avr/io.h>

#define PIN _BV(PC1)

void led_init(void)
{
    DDRC |= PIN;
}


void led_on(void)
{
    PORTC |= PIN;
}

void led_off(void)
{
    PORTC &= ~ PIN;
}

void led_toggle(void)
{
    PORTC ^= PIN;
}
