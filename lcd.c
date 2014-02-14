#ifndef LCD
#define LCD

#include <p89lpc9351.h>
#include "pins.c"
#include "utilities.c"

// LCD declarations --------------------------------
// load data into LCD
void LCD_load();

// send a character
void LCD_write(char i);

// 4 bits of data for LCD
void LCD_push(char i);

// send a command to the LCD
void LCD_cmd(char i);

// set LCD for operation
void LCD_init();


// LCD definitions ---------------------------------------------
void LCD_init() {
	P2_5 = 0;
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
	P2_4 = i & 1;
	P2_3 = (i >> 1) & 1;
	P2_2 = (i >> 2) & 1;
	P2_1 = (i >> 3) & 1;
	P2_0 = (i >> 4) & 1;
	P1_7 = (i >> 5) & 1;
	P1_6 = (i >> 6) & 1;
	P1_4 = (i >> 7) & 1;
}

void LCD_write(char i) {
	P2_7 = 1; // set RS for data
	P2_6 = 0; // set RW for write
	
	LCD_push(i);
	
	LCD_load();
}

void LCD_cmd(char i) {
	P2_7 = 0; // set RS for command
	P2_6 = 0; // set RW for write

	// four-bit data set
	LCD_push(i);
	LCD_load();
}

void LCD_load()
{
	// toggle enable bit
	P2_5 = 1;
	delay();
	P2_5 = 0;
}

#endif