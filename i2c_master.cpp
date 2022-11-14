/**** i2c_master.h /i2c_master.cpp *********
   
These are the i2c routines:

void i2c_init(void)  initializes for 100kHz baud rate with 16 MHz clock assumed

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

#ifndef  F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/twi.h>
#include "i2c_master.h"
#include <stdio.h>
#include <inttypes.h>

#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

#define I2C_READ 0x01
#define I2C_WRITE 0x00

void i2c_init(void) {
	TWBR = (uint8_t)TWBR_val;
}

uint8_t i2c_start(uint8_t address) {
	
    address=address << 1;
    // activate internal pullups for twi.
	// reset TWI control register
	TWCR = 0;
	// transmit START condition 
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for end of transmission
	while (!(TWCR & (1<<TWINT)));
	
	// check if the start condition was successfully transmitted
	if ((TWSR & 0xF8) != TW_START){ return 1; }
	
	// load slave address into data register
	TWDR = address;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while(!(TWCR & (1<<TWINT)));
	
	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) return 2;
	
	return 0;
}

void i2c_stop(void) {
	// transmit STOP condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

uint8_t i2c_write(uint8_t data) {
	// load data into data register
	TWDR = data;
	// start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while (!(TWCR & (1<<TWINT)));
	
	if ((TWSR & 0xF8) != TW_MT_DATA_ACK){ return 1; }
	
	return 0;
}

uint8_t i2c_read_ack(void) {
	
	// start TWI module and acknowledge data after reception
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); 
	// wait for end of transmission
	while (!(TWCR & (1<<TWINT)));
	// return received data from TWDR
	return TWDR;
}

uint8_t i2c_read_nack(void) {
	
	// start receiving without acknowledging reception
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while (!(TWCR & (1<<TWINT)));
	// return received data from TWDR
	return TWDR;
}

uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length) {
	if (i2c_start(address | I2C_WRITE)) return 1;
	for (uint16_t i = 0; i < length; i++) {
		if (i2c_write(data[i])) return 1;
	}
	i2c_stop();
	return 0;
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length) {
	if (i2c_start(address | I2C_READ)) return 1;
	for (uint16_t i = 0; i < (length-1); i++) {
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();
	i2c_stop();
	return 0;
}

uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length) {
	if (i2c_start(devaddr | 0x00)) return 1;
	i2c_write(regaddr);
	for (uint16_t i = 0; i < length; i++) {
		if (i2c_write(data[i])) return 1;
	}
	i2c_stop();
	return 0;
}

uint8_t i2c_writeByteReg(uint8_t devaddr, uint8_t regaddr, uint8_t data){
	if (i2c_start(devaddr | 0x00)) return 1;
	i2c_write(regaddr);
	if (i2c_write(data)) return 1;
	i2c_stop();
	return 0;
}

uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length) {
	if (i2c_start(devaddr)) return 1;
	i2c_write(regaddr);
	if (i2c_start(devaddr | 0x01)) return 1;
	for (uint16_t i = 0; i < (length-1); i++) {
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();
	i2c_stop();
	return 0;
}

