#ifndef LCD
#define LCD

#include <p89lpc9351.h>
#include "pins.c"
#include "utilities.c"

// LCD declarations --------------------------------

// testing

// LCD_clock()
// send a clock pulse to the lcd
// to make it read the current bits
// applied to its input ports
void LCD_clock();

// LCD_write(character)
// write a character to the LCD
// (sends a clock pulse)
void LCD_write(char i);

// LCD_apply(character)
// apply data to the LCD ports
// (does not send a clock pulse)
void LCD_apply(char i);

// set the cursor
void LCD_setcursor(int x, int y);

// send a character
void LCD_write(char i);

//send a string
void LCD_writestring(char *string);

// LCD_cmd(character)
// write a command to the LCD
// (sends a clock pulse)
void LCD_cmd(char i);

// LCD_init()
// wakeup the LCD and get ready for use
void LCD_init();


// LCD definitions ---------------------------------------------

// LCD_init()
// wakeup the LCD and get ready for use
void LCD_init() {
	lcd_enable = 0;
	delay();
	LCD_cmd(0x30); // wake up
	delay();
	LCD_cmd(0x30); // wake up 2
	delay();
	LCD_cmd(0x30); // wake up 3
	delay();
	LCD_cmd(0x38); // 8bit/2line
	LCD_cmd(0x10); // return home
	LCD_cmd(0x0c); // display on cursor on
	LCD_cmd(0x06); // set display mode
	delay();
	LCD_cmd(0x01); // clear screen
}

// LCD_apply(character)
// apply data to the LCD ports
// (does not send a clock pulse)
void LCD_apply(char i) {
	lcd_data_7 = i & 1;
	lcd_data_6 = (i >> 1) & 1;
	lcd_data_5 = (i >> 2) & 1;
	lcd_data_4 = (i >> 3) & 1;
	lcd_data_3 = (i >> 4) & 1;
	lcd_data_2 = (i >> 5) & 1;
	lcd_data_1 = (i >> 6) & 1;
	lcd_data_0 = (i >> 7) & 1;
}

// LCD_write(character)
// write a character to the LCD
// (sends a clock pulse)
void LCD_write(char i) {
	lcd_dc = 1; // set RS for data
	lcd_rw = 0; // set RW for write
	
	LCD_apply(i);
	
	LCD_clock();
}

//NOT YET TESTED DO NOT KNOW IF WILL COMPILE
void LCD_writestring(char *string)
{
    
    int i = 0;
    while (string[i] != 0)
    {
        LCD_write(string[i]);
        i++;
        delay();
    }
    
}

// NOT YET TESTED DO NOT KNOW IF WILL COMPILE
void LCD_setcursor(int x, int y) // x is row [0,15], y [0,1]
{
    //nothing in here yet
}

// LCD_cmd(character)
// write a command to the LCD
// (sends a clock pulse)
void LCD_cmd(char i) {
	lcd_dc = 0; // set RS for command
	lcd_rw = 0; // set RW for write

	// four-bit data set
	LCD_apply(i);
	LCD_clock();
}

// LCD_clock()
// send a clock pulse to the lcd
// to make it read the current bits
// applied to its input ports
void LCD_clock()
{
	// toggle enable bit
	lcd_enable = 1;
	delay();
	lcd_enable = 0;
}

#endif
