/*
 * CFile2.c
 *
 * Created: 2020-06-11 오전 5:21:33
 *  Author: 이주현
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void msec_delay(int n);
static char lcdtitle[]="LCD Display";

int main()
{
	char i;
	char string[20];
	
	LcdInit();
	LcdMove(0, 0);
	LcdPuts(lcdtitle);
	
	string[0]='M';
	string[1]='E';
	string[2]='C';
	string[3]='H';
	string[4]='A';
	string[5]='\0';
	
	LcdMove(1, 0);
	LcdPuts(string);
	
	while(1)
	{
		for(i=0;i<10;i++)
		{
			msec_delay(1000);
			LcdCommand(DISP_RSHIFT);
		}
		for(i=0;i<10;i++)
		{msec_delay(1000);
		LcdCommand(DISP_LSHIFT);
		}
	}
}

void msec_delay(int n)
{
	for(; n>0; n--)
		_delay_ms(1);
}