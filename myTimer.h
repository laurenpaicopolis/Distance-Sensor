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

Time wasting delays

void myDelay10us(void);
void myDelay100us(void);
void myDelay1ms(int); tTick to keep
track of time in 4ms increments in the main program.
*************************************************************

These are time wasting delays
They just tie up the CPU and waste time in loops.
void myDelay10us(int);
void myDelay100us(int);
void myDelay1ms(int);

*/

#ifndef myTimer_H
#define myTimer_H
 
void initPWM(uint16_t);
void pwmPW(uint16_t);
void myDelay10us(void);
void myDelay100us(void);
void myDelay1ms(int);

#endif // myTimer_H