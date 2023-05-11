/*
 * program10_1.c
 *
 * Created: 2020-06-09 오전 12:46:18
 *  Author: 이주현
 */ 
// 0.5초 이상 누르고 있으면 100msec 마다 누른 스위치에 해당하는 증분값으로 값 증가
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "iseg7.h"
#include "button.h"

int main()
{
	unsigned char btn;		//버튼 입력값
	unsigned char pressed;	//버튼을 계속 누르는 것인지 판단
	unsigned short data = 0;
	ISeg7Init();
	BtnInit();
	sei();
	ISeg7DispNum(data, 10);
	while(1)
	{
		btn = BtnInput_Press(&pressed);		//버튼 입력을 받는다.
		
		switch(btn)
		{
		case BTN_SW0:
			  data += 1;
			  break;
		case BTN_SW1:
			  data += 2;
			  break;
		case BTN_SW2:
			if(pressed) break;		//계속 누른 입력은 배제
			  data += 3;
			  break;
		default:					//입력이 없거나, 여러 버튼이 눌러진 경우 제외
			  break; 
		}
		ISeg7DispNum(data, 10);
	}
}