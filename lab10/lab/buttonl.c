/*
 * button.c
 *
 * Created: 2020-06-09 오전 1:13:20
 *  Author: 이주현
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "button.h"

#define  BTN_INPORT		PIND		//버튼입력포트
#define  BTN_DDR		DDRD		//방향 포트
static unsigned char psw=NO_BTN;	//이전 버튼 값

void BtnInit(void)
{
	BTN_DDR &= ~(BTN_MASK);		//버튼 입력 핀을 입력으로 설정
}

unsigned char BtnInput(void)
{
	unsigned char sw, sw1;
	sw = ~BTN_INPORT & BTN_MASK;	//버튼 입력을 받는다.
	while(1)		//연속 두번 읽은 값이 같을때까지 루프를 돈다.
	{				//디바운싱 시간 지연
		_delay_ms(10); _delay_ms(10); _delay_ms(10);
		sw1 = ~BTN_INPORT & BTN_MASK;
		
		if(sw==sw1)
			break;
		sw = sw1;
	}
	
	if(sw==psw) return 0;
	psw = sw;
	return sw;
}

