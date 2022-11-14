/* *** myADC.h /myADC.cpp *********
   
These are the basic ADC routines:
void ADC_init(void) turns on tje ADC module
ADC_read(x) reads the channel.  Returns a 10 bit ADC value.

     min = 0
	 max = 0x3ff  or 4095

------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
Pin outs according to

INPUT/OUPUT  
SEE TABLES  14.3, 14.6, 14.9 IN ATmega328DataSheet.pdf for more pin details 
     
ADC channels are 0-5.  Specify which one you want to read. 
                  
								  13: B5/SCK     
								  12: B4/MISO    
								  11: B3/MOSI
								  10: B2/SS
				RST: C6/RESET     9:  B1
								  8:  B0
								  7:  D7
			>>>	A0: C0/ADC0       6:  D6
			>>>	A1: C1/ADC1       5:  D5      
			>>>	A2: C2/ADC2       4:  D4       
			>>>	A3: C3/ADC3       2:  D2/INT0
		    >>>	A4: C4/ADC4/SDA   1:  D1 ONBOARD TXD
			>>>	A5: C5/ADC5/SCL   0:  D0 ONBOARD RXD

*/

#include <avr/io.h>
#include "myADC.h"
#include <stdio.h>
#include <inttypes.h>

void initADC(void) {
    // AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t readADC(uint8_t ch) {
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7
  ch &= 0b00000111;  // AND operation with 7
  ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
 
  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1<<ADSC);
 
  // wait for conversion to complete
  // ADSC becomes ’0′ again
  // till then, run loop continuously
  while(ADCSRA & (1<<ADSC));
 
  return (ADC);
}
