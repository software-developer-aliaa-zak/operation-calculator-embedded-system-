/*
 * Keypad.h
 *
 * Created: 12/12/2017 10:36:56 AM
 *  Author: Hager  && Aliaa && Noura
 */ 

#include "common.h"
#define KEY1 '1'
#define KEY2 '2'
#define KEY3 '3'
#define KEY4 '4'
#define KEY5 '5'
#define KEY6 '6'
#define KEY7 '7'
#define KEY8 '8'
#define KEY9 '9'
#define KEY10 '10'
#define KEY11 '11'
#define KEY12 '12'
#define KEY13 '13'
#define KEY14 '14'
#define KEY15 '15'
#define KEY16 '16'

// Rows at PC0:PC3and Columns at PC4:PC7

void init_keypad()
{
	DDRD=0xf0;
	PORTD=0xff;
}


unsigned char Keypad_Scan(){
		
	unsigned char Key[16]={ '1','4','7','C','2','5','8','0','3','6','9','.','+','-','*','='};
	unsigned char Code[16] ={0xee,0xed,0xeb,0xe7,0xde,0xdd,0xdb,0xd7,0xbe,0xbd,0xbb,0xb7,0x7e,0x7d,0x7b,0x77}	;
	unsigned char Button=0xff;
	while (Button==0xff)
	{
		DDRD=0x0f;
		PORTD=0xf0;
		_delay_us(5);
		Button=PIND;
		
		DDRD=0xf0;
		PORTD=0x0f;
		_delay_us(5);
		Button= Button|PIND;
		
		
		if (Button!=0xff)
		{
			
			for (int i=0;i<16;i++)
			{
				if (Button==Code[i])
				{
					return Key[i];
				}
			}
		}
		Button=0xff;
	}
}



