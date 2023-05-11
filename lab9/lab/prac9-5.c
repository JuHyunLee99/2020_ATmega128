/*
 * prac9_1.c
 *
 * Created: 2020-06-08 오후 10:45:46
 *  Author: 이주현
 */ 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "iseg7.h"		//7세그먼트 출력 프로그램 헤더파일

void msec_delay(int n);

int main()
{
	unsigned short data=0;
	
	ISeg7Init();			//7세스먼트 초기화
	
	sei();
	
	while(1)
	{
		msec_delay(1000);
		data += 10;
		ISeg7DispNum(data, 10);	//10진수로 표시
	}
}

void msec_delay(int n)
{
	for(; n>0; n--)
		_delay_ms(1);
}