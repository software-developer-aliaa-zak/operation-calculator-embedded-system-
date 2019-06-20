/*
 * LCD.c
 *
 * Created: 12/12/2017 10:37:13 AM
 *  Author: Hager  && Aliaa && Noura
 */ 

#include "common.h"
#define LCD_DATA_PORT PORTB
#define LCD_CONT_PORT PORTA
#define LCD_RS PA7
#define LCD_RW PA3
#define LCD_EN PA6



void lcd_data_write(char data)
{
	LCD_DATA_PORT =data;
	LCD_CONT_PORT |= (1<<LCD_RS);
	LCD_CONT_PORT |= (1<<LCD_EN);
	_delay_us(2);
	LCD_CONT_PORT &= ~(1<<LCD_EN);
	_delay_us(100);

}


void lcd_command_write(char command)
{
	LCD_DATA_PORT= command;
	LCD_CONT_PORT &= ~(1<<LCD_RS);
	LCD_CONT_PORT |= (1<<LCD_EN);
	_delay_us(1);
	LCD_CONT_PORT &= ~(1<<LCD_EN);
	_delay_ms(3);

}

void lcd_init()
{
	lcd_command_write(0x38);
	lcd_command_write(0x01);
	lcd_command_write(0x06);
	lcd_command_write(0x0e);
}

void lcd_string_write(char *string)
{
	while (*string)
	lcd_data_write(*string++);
}

void lcd_CLR(){
	_delay_ms(10);
	lcd_command_write(0x01);
	_delay_us(10);
}

void lcd_GoHome(){
	
	_delay_ms(10);
	lcd_command_write(0x02);
	_delay_ms(2);
	
}

void lcd_SetCursor(unsigned char x , unsigned char y){
	
	lcd_GoHome();
	if (y==0){
		for (int H=0;H<x;H++){
			lcd_command_write(0x14);
			_delay_us(50);
		}
	}
	else if(y==1){
		for (int H=0;H<(x+40);H++){
			lcd_command_write(0x14);
			_delay_us(50);
		}
	}
}


void lcd_Print_Num(float Num)
{
	long int H_Num=0;
	float L_Num=0.0;
	signed char i=0,Polr=0,L=0;
	unsigned char N[16],N_L[10];
	/* ------------------------------------(Num==0)--------------------------------------------*/
	if (Num==0)
	{
		lcd_data_write('0');
	}
	/* ----------------------------------------------------------------------------------------*/
	
	/* ------------------------------------(Num!=0)--------------------------------------------*/
	else
	{
		/* ---------------------------------(Num<0)--------------------------------------------*/
		if (Num<0)
		{
			Num*= -1;
			Polr=1;
		}
		/* -------------------------------------------------------------------------------------*/
		
		H_Num=(int)Num;
		
		L_Num=(Num-H_Num);
		
		/* ---------------------------------(L_Num>0)-------------------------------------------*/
		if (L_Num>0)
		{
			/* -------------------------------(L<=4)--------------------------------------------*/
			while(L<=4)
			{
				L_Num*=10;
				N_L[L+5]=48;
				N_L[L]=((int)L_Num)+48;
				L_Num=L_Num-N_L[L]+48;
				
				L++;
			}
			/* ---------------------------------------------------------------------------------*/
			
			/* ---------------------------------------------------------------------------------*/
			for (L--;L>=0;L--)
			{
				if( N_L[L]!=48 || N_L[L+1]!=48 || N_L[L+2]!=48 ||N_L[L+3]!=48 ||N_L[L+4]!=48)
				{
					
					N[i]=N_L[L];
					i++;
				}
				
			}
			/* ---------------------------------------------------------------------------------*/
			
			N[i]=46; //  46=.
			i++;
		}
		/* -------------------------------------------------------------------------------------*/
		
		/* -------------------------------------------------------------------------------------*/
		while(H_Num!=0)
		{
			N[i]=(H_Num%10)+48;
			H_Num/=10;
			i++;
		}
		/* --------------------------------------------------------------------------------------*/
		
		/* --------------------------------------------------------------------------------------*/
		if (Polr==1)
		{
			N[i]=45;// 45=-
			i++;
		}
		/* ---------------------------------------------------------------------------------------*/
		i--;
		/* ---------------------------------------------------------------------------------------*/
		while(i>=0)
		{
			lcd_data_write(N[i]);
			i--;
			_delay_ms(1);
		}
		/* ---------------------------------------------------------------------------------------*/

	}
}




