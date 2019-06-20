/*
 * final_code.c
 *
 * Created: 12/12/2017 10:33:41 AM
 * Author : Hager  && Aliaa && Noura
 */ 

#define	F_CPU	8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "common.h"

int main(void)
{
	DDRB=0xff;
	DDRA = 0xFF;

	lcd_init();
	lcd_CLR();
	
	_delay_ms(300);
	lcd_string_write("Press any key ");

	while(1)
	{
		unsigned char x;
		unsigned char y=0 , i=0 ;
		float Pow=1;
		float Num[16] , Num1[16]={0,0,0,0,0,0};
		float Sum=0.0;
		
		x=Keypad_Scan();
		lcd_CLR();
		_delay_ms(300);
		
		
		while(x)
		{ 
			
			while(y!='=')
			{  
				y=Keypad_Scan();
				
				lcd_data_write(y);
					
				Num[i]=y-48;
				if (Num[i]==('C'-48))  // clear
				{
					// start from the value of i and clear each element step by step moving to left
					i--;
					lcd_SetCursor(i,0);
					lcd_data_write(' ');
					lcd_data_write(' ');
					lcd_SetCursor(i,0);
					i--;
					_delay_ms(100);
				}
				_delay_ms(50);
				i++;
				_delay_ms(400);  //FOR scanning keypad

			} 
			i=0;
			unsigned char N=0;
			while (Num[i]!=13)  // '=' =61-48=13
			{
				// 12.5*1+2-3=11.5
				// 12.5+2-4*2=21       solving the first mathematical operation then next els.
				//                     doesn't use the periority of operations
				
				// in case the value of Num[i] is number between 0 and 9
				if (Num[i]>=0 && Num[i]<=9)
				{
					
					if (Pow==1 || Pow==10)   
					{
						Num1[N]=Num[i]+(Num1[N]*Pow);  // using this equation to understand the meaning of 123 as (one hundred twenty three ) not using it as (one , two , three)
						if (Pow==1){Pow*=10;}          // by making pow=10 instead of 1     (resulting the upper value of the number)   
					}
					else
					{
						Num1[N]+=(Num[i]*Pow);         // this equation using to the same target but it (result the lower value of the number ) 
						Pow*=(1.0/10);                 // and making pow changes by 0.1
					}
				}
				
				// in case the value of Num[i] is a symbol
				else   
				{
					// if this symbol is dot(.)
					
					if (Num[i]==(-2))   //'.' =46     (46-48=-2)
					{Pow=(1.0/10.0);}
					
					// if this symbol is one of this ( + | - | * | / )
					else
					{
						N++;
						Num1[N]=Num[i];
						N++;
						Num1[N]=1;     // this step is an using requirement in the next  for loop to ensure that not enter two symbols together (12+*3  error)
						N++;
						
						Pow=1;
					}
				}
				
				i++;
				_delay_ms(10);
			}
			     
			for (int a=0;a<=N;a++)
			{
				_delay_ms(1);
				if (Num1[a]==(-6) && Num1[a+1]==1)   // '*' =42-48=-6
				{
					Sum*=Num1[a+2];
					a+=2;
				}
				else if (Num1[a]==(-5)&& Num1[a+1]==1)  // '+' =43-48=-5
				{
					Sum+=Num1[a+2];
					a+=2;
				}
				else if (Num1[a]==(-3)&& Num1[a+1]==1)   // '-' =45-48=-3
				{
					Sum-=Num1[a+2];
					a+=2;
				}
				else if (Num1[a]==(-1)&& Num1[a+1]==1)  // '/' =47-48=-1
				{
					Sum/=Num1[a+2];
					a+=2;
				}
				else{
					Sum=Num1[a];
				}
				
			}
			lcd_Print_Num(Sum);
			_delay_ms(1000);
			x=0;
		} //----- while(x)----
	} //-------while(1)------
}