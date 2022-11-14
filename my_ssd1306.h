/*
Functions used for displaying on OLED ssd1306 128x64 pixel screen

Some are the most used functions:

********** void intSSD1306(); **************
Must run once durinig setup to initialize

**********  printChar(uint16_t);     *************
Print a single character with single quotes. 
ex  printChar('h');
*********** clearDisplay(void);   *************
Clears display by writing over the whole screen.
Takes a lot of time
Brings cursor back to 0,0
**************** writeString (uint16_t *c)  *********
Writes an array of characters using double quotes
Ex. writeString("Now is the time...");

*********** setLocation(uint16_t,uint16_t) ********
Brings cursor to specified location
screen dimenstions:  0,0  upper left
                     127,7 lower right
    
This set of commands will give space for printing the 'h' in
the lowest, rightmost space.	
	setLocation(122,7);
    printChar('h');

Use table from gfx to print characters  //specify position

*/

#ifndef my_ssd1306_H_
#define my_ssd1306_H_
#include "i2c_master.h"

/*
**  WHO_AM_I Device ID Register
*/
#define child_id          0x3C
#define SYSMOD                0x0B

//***** ssd Commands and data *************
#define SSD1306_LCDWIDTH      128
#define SSD1306_LCDHEIGHT      64
#define SSD1306_SETCONTRAST   0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// init according to SSD1306 data sheet
void  initSSD1306(void);

/******* Prototype Function declarations ******/
void  ssd1306_command(uint8_t);
void  ssd1306_data(uint8_t);
// Used when doing Horizontal or Vertical Addressing
void setColAddress(uint16_t);
// Used when doing Horizontal or Vertical Addressing
void setPageAddress(uint16_t);
// Transfers the local buffer to the CGRAM in the SSD1306
void transferBuffer(uint8_t *, uint16_t ,uint8_t, uint8_t);

// Use table from gfx to print characters  //specify position
void printChar(uint8_t);
void clearDisplay(void);
void setLocation(uint16_t,uint16_t);
void writeString (uint8_t *);
void printHexByte (uint8_t);
void printHexWord (uint16_t);
void printMem(uint16_t);

#endif //my_ssd1306_H_

