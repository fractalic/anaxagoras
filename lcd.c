#ifndef LCD
#define LCD

#include <p89lpc9351.h>
#include "pins.c"
#include "utilities.c"

// LCD declarations --------------------------------

// LCD_writeString(char*)
// write a sequence of characters to the LCD
void LCD_writeString(const char *string);

// LCD_cmd(character)
// write a command to the LCD
// (sends a clock pulse)
void LCD_cmd(char i);

// LCD_clock()
// send a clock pulse to the lcd
// to make it read the current bits
// applied to its input ports
void LCD_clock();

// LCD_apply(character)
// apply data to the LCD ports
// (does not send a clock pulse)
void LCD_apply(char i);

// LCD_init()
// wakeup the LCD and get ready for use
void InitLCD();

// GLOBAL VARS ----------------------------------
// nothing here

// LCD definitions ---------------------------------------------

// LCD_writeString(char*) - TESTED WORKS
// write a sequence of characters to the LCD
void LCD_writeString(const char *string)
{
    int i = 0;
    int d = 5;
    
	lcd_dc = 1; // set RS for data
	lcd_rw = 0; // set RW for write

    while (string[i] != 0)
    {
    	LCD_apply(string[i]);
		LCD_clock();
        i++;
    }
}

// LCD_cmd(character) - TESTED WORKS
// write a command to the LCD
// (sends a clock pulse)
void LCD_cmd(char i) {
	lcd_dc = 0; // set RS for command
	lcd_rw = 0; // set RW for write

	// four-bit data set
	LCD_apply(i);
	LCD_clock();
}

// LCD_init()
// wakeup the LCD and get ready for use
void InitLCD() {
	lcd_enable = 0;
	delay();
	LCD_cmd(0x30); // wake up
	delay();
	LCD_cmd(0x30); // wake up 2
	delay();
	LCD_cmd(0x30); // wake up 3
	delay();
	
	LCD_cmd(0x38); // 8bit/2line
	
	LCD_cmd(0x10); // function set
	LCD_cmd(0x0c); // display on cursor on
	LCD_cmd(0x06); // set display mode
	delay();
	LCD_cmd(0x01); // clear screen
}

// LCD_apply(character)
// apply data to the LCD pins
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
