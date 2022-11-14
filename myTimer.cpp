/* myTimer.c/h

PWM routines

Uses timerA connected to B1 (pin 9 on UNO and Metro)

Arguments in micro seconds
    
void initPWM(uint16_t);
void pwmPW(uint16_t);

Initialize once with
initPWM(1000)   this will give a 1000 us period or 1 ms.

Set the pulse width in your loop.
pwmPW(500) will give a 500 us pulse width or 0.5ms

Time wasting delays:

void myDelay10us(void);
void myDelay100us(void);
void myDelay1ms(int); tTick to keep
track of time in 4ms increments in the main program.

*/

#include <avr/io.h> 
#include <avr/interrupt.h>
#include "myTimer.h"

void pwmPW(uint16_t PW) {
	  OCR1A = 2 * PW;
}

void initPWM(uint16_t MOD) {
     //  Output on B1
    DDRB |= ( 1 << DDB1 );
    TCCR1A = 0b0;
    //non-inverting mode of PWM
    TCCR1A |= ( 1 << COM1A1 ) | ( 1 << COM1B1 );
    //Fast mode PWM with ICR1 as TOP:
    ICR1 = 2 * MOD; // set the top value (up to 2^16)
    TCCR1A |= ( 1 << WGM11 );
    TCCR1B = 0b0;
	
    TCCR1B |= ( 1 << WGM12 ) | ( 1 << WGM13 );
    TCCR1B |= ( 1<<CS11 ); // enable output, Prescale=8
}

/*  Time wasting delays   */
void myDelay10us(void) {
  volatile static int i, j = 0;
  for (i = 0; i < 4; i++)
      j++;
  return;
}

void myDelay100us(void) {
  volatile static int i;
  for (i = 0; i < 10; i++)
      myDelay10us();
  return;
}

void myDelay1ms(int n) {
  volatile static int i;
  for( i = 0; i < (10*n); i++)
      myDelay100us();
  return;
}

/*
my string = this is a splendid string
 61fcf0    t
 61fd00    i
 61fd10    a
 61fd20    s
 61fd30    s
 61fd40
 61fd50
 61fd60
 61fd70
 61fd80
Process returned 0 (0x0)   execution time : 0.227 s
Press any key to continue.
*/
