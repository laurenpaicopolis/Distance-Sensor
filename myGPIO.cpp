/**** myGPIO.h / myGPIO.cpp *********
   
These are the GPIO initialization routines:

void init_gpio_b,d(int pin,int i/o) initializes the specified port(a,b,c,d) pin(0-7) as input(0) or output(1)
         - output pins are software controlled
         - input pins are internally pulled up high.

Output routines:		 
void gpo_b,d(int pin,int i/o) sets the output pin(0-7) as on(1) or off(0)

Input routines:
int gpi_b,d(int pin) returns an active(0) or inactive(1) since its internally pulled high
*/

#include <avr/io.h>
#include "myGPIO.h"
#include <stdio.h>
#include <inttypes.h>

void init_gpio_d(int pin, int dd) {
    if (dd==1)
        DDRD |= 1<<pin; 
    else 
        DDRD &=~(1<<pin);   
    PORTD |= 1<<pin; //initialze so 1 or if input, so pullup enabled
}

void init_gpio_c(int pin, int dd) {
    if (dd==1) 
        DDRC |= 1<<pin; 
    else 
        DDRC &=~(1<<pin);   
    PORTC |= 1<<pin;   //initialze so 1 or if input, so pullup enabled
}

void init_gpio_b(int pin, int dd) {
    if (dd==1) 
        DDRB |= 1<<pin; 
    else 
        DDRB &=~(1<<pin);   
    PORTB |= 1<<pin;   //initialze so 1 or if input, so pullup enabled
}

void gpo_d(int pin, int val) {
   if (val==1) 
       PORTD|=(1<<pin);
   else 
       PORTD&=~(1<<pin);
}

void gpo_c(int pin, int val) {
   if (val==1) 
       PORTC|=(1<<pin);
   else 
       PORTC&=~(1<<pin);
}

void gpo_b(int pin, int val) {
   if (val==1)
       PORTB|=(1<<pin);
   else 
       PORTB&=~(1<<pin);
}

int gpi_d(int pin) {
  return 1&(PIND>>pin);
}

int gpi_c(int pin) {
  return 1&(PINC>>pin);
}

int gpi_b(int pin) {
  return 1&(PINB>>pin);
}