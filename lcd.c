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