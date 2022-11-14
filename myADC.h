/**** myADC.h myADC.cpp *********
   
Pin outs according to

INPUT/OUPUT  
SEE TABLES  14.3, 14.6, 14.9 IN ATmega328DataSheet.pdf for more pin details 
     
ADC channels are 0-5.  Specify which one you want to read. 
Pin assignment for the Adafruit MetroMini
                                       13: B5/SCK   <<< pB2
                                       12: B4/MISO  <<< pB1   
                                       11: B3/MOSI    
                                       10: B2/SS
                  RST: C6/RESET         9:  B1 
                                        8:  B0  
                                        7:  D7
                                        6:  D6
                  A0: C0/ADC0           5:  D5     
                  A1: C1/ADC1           4:  D4     <<<led1
                  A2: C2/ADC2           3:  D3        <<<led2 
                  A3: C3/ADC3           2:  D2/INT0 <<<led3
ssd1306 sda >>>  A4: C4/ADC4/SDA       1:  D1 ONBOARD TXD
ssd1306 scl >>>  A5: C5/ADC5/SCL       0:  D0 ONBOARD RXD

*/

#ifndef MYADC_H
#define MYADC_H
#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

void initADC(void);  // function prototype for ADC initialization
uint16_t readADC(uint8_t); // prototype for reading

#endif // myADC_H



