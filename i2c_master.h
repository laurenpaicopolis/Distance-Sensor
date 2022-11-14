/**** i2c_master.h /i2c_master.cpp *********
   
These are the i2c routines:

void i2c_init(void)  initializzes for 100kHz baud rate with 16 MHz clock assumed

uint8_t i2c_start(uint8_t address)  <<< needed to start i2c communication
uint8_t i2c_read_ack(void)          <<< waiting for ACK bits to be set 
uint8_t i2c_read_nack(void)         <<< if ACK bits are not set
uint8_t i2c_write(uint8_t data)     <<< writes a byte to the i2c line  

For reading and writing bytes from a specified register in the child device

uint8_t i2c_writeByteReg(uint8_t devaddr, uint8_t regaddr, uint8_t data){
uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)

****These have not been tested!!!!
For reading and writing an array of bytes from the child
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length)
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length)

------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
Pin outs according to


INPUT/OUPUT  
SEE TABLES  14.3, 14.6, 14.9 IN ATmega328DataSheet.pdf for more pin details 
     
Tie your device sda and scl lines high to since they are assumed active low.  ~2k pullup
Many devices like the sd1306 oled is tied high internally so no external Rs needed.	 
                  
								  13: B5/SCK     
								  12: B4/MISO    
								  11: B3/MOSI
								  10: B2/SS
				RST: C6/RESET     9:  B1
								  8:  B0
								  7:  D7
				A0: C0/ADC0       6:  D6
				A1: C1/ADC1       5:  D5      
				A2: C2/ADC2       4:  D4       
				A3: C3/ADC3       2:  D2/INT0
		sda <<<	A4: C4/ADC4/SDA   1:  D1 ONBOARD TXD
		scl	<<<	A5: C5/ADC5/SCL   0:  D0 ONBOARD RXD

*/

#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include <stdint.h>
#define I2C_READ 0x01
#define I2C_WRITE 0x00

void i2c_init(void);  
uint8_t i2c_start(uint8_t address);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_ack(void);
uint8_t i2c_read_nack(void);
uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);

uint8_t i2c_writeByteReg(uint8_t devaddr, uint8_t regaddr, uint8_t data);

uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void i2c_stop(void);

#endif // I2C_MASTER_H

