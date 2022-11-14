/**** myGPIO.h / myGPIO.cpp *********
   
These are the GPIO initialization routines:

void init_gpio_b,d(int pin,int i/o) initializes the specified port(a,b,c,d) 
pin(0-7) as input(0) or output(1)

         - output pins are software controlled
         - input pins are internally pulled up high.

Output routines:		 
void gpo_b,d(int pin,int i/o) sets the output pin(0-7) as on(1) or off(0)

Input routines:
int gpi_b,d(int pin) returns an active(0) or inactive(1)  since its internally 
pulled high 

Pin outs according to


INPUT/OUPUT  
SEE TABLES  14.3, 14.6, 14.9 IN ATmega328DataSheet.pdf for more pin details 
                  
                  13: B5/SCK     
                  12: B4/MISO    
                  11: B3/MOSI
                  10: B2/SS
                  9:  B1
RST: C6/RESET     8:  B0
                  7:  D7
                  6:  D6
A0: C0/ADC0       5:  D5
A1: C1/ADC1       4:  D4      
A2: C2/ADC2       3:  D3        
A3: C3/ADC3       2:  D2/INT0
A4: C4/ADC4/SDA   1:  D1 ONBOARD TXD
A5: C5/ADC5/SCL   0:  D0 ONBOARD RXD

*/

#ifndef myGPIO_H
#define myGPIO_H
#include <stdint.h>

void init_gpio_d(int,int);
void init_gpio_c(int,int);
void init_gpio_b(int,int);

void gpo_d(int,int);
void gpo_c(int,int);
void gpo_b(int,int);

int gpi_d(int);
int gpi_c(int);
int gpi_b(int);

#endif // myGPIO_H

