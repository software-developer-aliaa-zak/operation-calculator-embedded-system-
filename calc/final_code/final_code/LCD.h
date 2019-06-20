/*
 * LCD.h
 *
 * Created: 12/12/2017 10:36:36 AM
 *  Author: Hager  && Aliaa && Noura
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define LCD_DATA_PORT PORTB
#define LCD_CONT_PORT PORTA
#define LCD_RS PA7
#define LCD_RW PA3
#define LCD_EN PA6

#ifndef LCD_H_
#define LCD_H_


void lcd_data_write(char data);
void lcd_command_write( char command);
void lcd_init();
void lcd_string_write( char *string);
void lcd_number_write(int number,unsigned char radix);
void lcd_CLR();
void lcd_GoHome();
void lcd_SetCursor(unsigned char x , unsigned char y);
void lcd_Print_Num(float Num);


#endif /* LCD_H_ */