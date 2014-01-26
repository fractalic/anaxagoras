#include <stdlib.h>
#include <stdio.h>
#include <p89lpc9351.h>

// doing some more damage

#define XTAL 7373000L
#define BAUD 115200L

// initialize the ports to proper I/O mode
void init_ports();

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

// make some light
void lights(char i);

// waitabit
void delay(void)
{
    int j, k;
    for(j=0; j<100; j++)
    {
        for(k=0; k<1000; k++);
    }
}

void main(void)
{
	init_ports();
	
	LCD_init();
	
	while(1)
	{
		lights(0x02);
		LCD_write(0x41);
		delay();
		LCD_write(0x42);
		lights(0x01);
		delay();
	}		
}

void init_ports() {
	// set port 1 to quasi-bidirectional
	P1M1 = 0;
	P1M2 = 0;
	// set port 2 to quasi-bidirectional
	P2M1 = 0;
	P2M2 = 0;
}

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

void lights(char i) {
	// run lights
	P1_3 = (i) & 0x01;
	P1_2 = (i>>1) & 0x01;
}