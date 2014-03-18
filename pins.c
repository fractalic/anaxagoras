#ifndef PINS
#define PINS

// XTAL is twice the clock speed of the p89lpc we're using
// XTAL is in Hz (7.373MHz)
#define XTAL 7373000L
#define BAUD 115200L

/* Pin sequence on controller
right-to-left with usb connector to your right
	
	GND
	+5V
	P0.0
	P0.1
	P0.2
	P0.3
	P0.4
	P0.5
	P0.6
	P0.7
	P3.0
	P3.1
	P1.2
	P1.3
	P1.4
	P1.6
	P1.7
	P2.0
	P2.1
	P2.2
	P2.3
	P2.4
	P2.5
	P2.6
	P2.7
*/

//miscellaneous pins
#define light_0 P1_2
#define light_1 P1_3
//#define batterypin  P1_2 //battery input pin	

// lcd pins
#define	lcd_data_0	P1_4
#define lcd_data_1	P1_6
#define lcd_data_2	P1_7
#define lcd_data_3	P2_0
#define lcd_data_4	P2_1
#define lcd_data_5	P2_2
#define lcd_data_6	P2_3
#define lcd_data_7	P2_4
#define lcd_dc		P2_7 // lcd data-command select
#define lcd_rw		P2_6 // lcd read-write select
#define lcd_enable	P2_5 // lcd clock pulse pin

// sensor pins
#define inductor_left	P0_5 // read in voltage signal from left inductor for PID
#define	inductor_right	P0_6 // read in voltage signal from right inductor for PID
#define inductor_front	P0_7 // read in voltage signal from front inductor to detect 'traffic signals'

// pwm pins
#define left_wheel	P3_0 // output motor speed from PID to pwm signal for left wheel 
#define right_wheel	P3_1 // output motor speed from PID to pwm signal for right wheels

#endif