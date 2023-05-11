/*
 * program10_1.c
 *
 * Created: 2020-06-09 오전 12:46:18
 *  Author: 이주현
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "iseg7.h"
#include "button.h"

int main()
{
	unsigned char btn;
	unsigned short data = 0;
	ISeg7Init();
	BtnInit();
	sei();
	ISeg7DispNum(data, 10);
	while(1)
	{
		btn=BtnInput();		//버튼 입력을 받는다.
		switch(btn)
		{
		case BTN_SW0:
			  data += 1;
			  break;
		case BTN_SW1:
			  data += 2;
			  break;
		case BTN_SW2:
			  data += 3;
			  break;
		default:
			  break; 
		}
		ISeg7DispNum(data, 10);
	}
}