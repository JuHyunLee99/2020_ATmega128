/*
 * program8_4.c
 *
 * Created: 2020-05-29 오전 3:01:45
 *  Author: 이주현
 */ 
// 외부 인터럽트대신에 button 함수를 이용하여 입력을 받아드려 듀티비 조절하기
//FAST PMW 신호로 LED 밝기 조절
//COM01:0=2 -> 듀티비 커지면 밝기 낮아짐
//SW0 누르면 듀티비 +5, SW1 누르면 듀티비 -5
//분주비 8
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "buttonhomework2.h"

int main()
{
	unsigned char btn;
	unsigned char duty = 125;
	BtnInit();
	
	DDRB |= (1<<DDB4);		// PB4(OC0)를 출력으로 설정
	TCCR0 = (1<<WGM01)|(1<<WGM00)|(2<<COM00);
	// 타이머/카운터 0 설정: FAST PWM모드, 타이머 정지, OC0 사용
	 
	TCCR0 |= (2<<CS00);		//분주지 8로 타이머 시작
	
	while(1)
	{
		btn = BtnInput();		//버튼 입력을 받는다.
		
		switch(btn)
		{
			case BTN_SW0:
			duty += 5;		// 듀티비 5 증가
			if(duty >= 250) duty = 250;
			break;
			case BTN_SW1:
			duty -= 5;		// 듀티비 5 감소
			if(duty <=5) duty = 5;
			break;
			default:					//입력이 없거나, 여러 버튼이 눌러진 경우 제외
			break;
		}
		OCR0 = duty;
	}		// PMW 신호의 듀티비를 바꾼다
}