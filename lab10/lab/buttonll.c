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


#define PRESS_THRESHOLD			16

unsigned char BtnInput_Press(unsigned char *pressed)
{
	static unsigned char press_cnt=0;
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
	*pressed = 0;
	
	 if(sw==psw)
	 {
		 press_cnt++;			//누른 시간 증가
		 if(press_cnt > PRESS_THRESHOLD)
		 { 
			 if(sw != 0)		//안누르고 있을 경우 제거
			 {
				 *pressed = 1;
				 _delay_ms(10); _delay_ms(10);
				 _delay_ms(10); _delay_ms(10);
				 _delay_ms(10); _delay_ms(10);
				 _delay_ms(10);
			 }
		} 
		else
		{	//짥은 시간 누르고 있으므로 입력이 없는 것으로 판단
			return 0;
		}
	}
	else
	{	//새 버튼이 눌러졌거나, 버튼을 땠음.
		press_cnt=0;		//누른 시간을 리셋한다.
	}
	
	 psw = sw;				//이전 값을 저장한다.
	 return sw;				//버튼 입력값을 리턴
 
}
