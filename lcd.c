#ifndef LCD
#define LCD

#include <p89lpc9351.h>
#include "pins.c"
#include "utilities.c"

// LCD declarations --------------------------------
// load data into LCD
void LCD_load();

// set the cursor
void LCD_setcursor(int x, int y);

// send a character
void LCD_write(char i);

//send a string
void LCD_writestring(char *string);

// 4 bits of data for LCD
void LCD_push(char i);

// send a command to the LCD
void LCD_cmd(char i);

// set LCD for operation
void LCD_init();


// LCD definitions ---------------------------------------------
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

void LCD_push(char i) {
	lcd_data_7 = i & 1;
	lcd_data_6 = (i >> 1) & 1;
	lcd_data_5 = (i >> 2) & 1;
	lcd_data_4 = (i >> 3) & 1;
	lcd_data_3 = (i >> 4) & 1;
	lcd_data_2 = (i >> 5) & 1;
	lcd_data_1 = (i >> 6) & 1;
	lcd_data_0 = (i >> 7) & 1;
}

void LCD_write(char i) {
	lcd_dc = 1; // set RS for data
	lcd_rw = 0; // set RW for write
	
	LCD_push(i);
	
	LCD_load();
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

void LCD_cmd(char i) {
	lcd_dc = 0; // set RS for command
	lcd_rw = 0; // set RW for write

	// four-bit data set
	LCD_push(i);
	LCD_load();
}

void LCD_load()
{
	// toggle enable bit
	lcd_enable = 1;
	delay();
	lcd_enable = 0;
}

#endif
