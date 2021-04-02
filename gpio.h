#ifndef IO_GPIO_H
#define IO_GPIO_H

#include <Arduino.h>

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define p_b_out(x)      DDRB|=x
#define p_b_in(x)       DDRB&=~x
#define p_b_high(x)     PORTB|=x
#define p_b_low(x)      PORTB&=~x
#define p_b_toggle(x)   PORTB^=x
#define p_b_data(x)     PORTB=x
#define p_b_read(x)     (PINB & x)

#define p_c_out(x)      DDRC|=x
#define p_c_in(x)       DDRC&=~x
#define p_c_high(x)     PORTC|=x
#define p_c_low(x)      PORTC&=~x
#define p_c_toggle(x)   PORTC^=x
#define p_c_data(x)     PORTC=x
#define p_c_read(x)     (PINC & x)

#define p_d_out(x)      DDRD|=x
#define p_d_in(x)       DDRD&=~x
#define p_d_high(x)     PORTD|=x
#define p_d_low(x)      PORTD&=~x
#define p_d_toggle(x)   PORTD^=x
#define p_d_data(x)     PORTD=x
#define p_d_read(x)     (PIND & x)

#endif
