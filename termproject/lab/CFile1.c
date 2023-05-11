/*
 * CFile1.c
 *
 * Created: 2020-06-11 오전 1:35:16
 *  Author: 이주현
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"
#include "button.h"

void msec_delay(int n);

static int row = 0;
static unsigned char pattern[4][8]
	={{0xE7, 0xCF, 0xD9, 0x64, 0x26, 0x9B, 0xD3, 0xE7},
	{0x7E, 0xBD, 0xDB, 0xE7, 0xE7, 0xDB, 0xBD, 0x7E},
	{0xEF, 0xEF, 0xEF, 0xE0, 0x07, 0xF7, 0xF7, 0xF7},  //사이렌2
	{0xF3, 0xE7, 0x6F, 0x21, 0x84, 0xF6, 0xE7, 0xCF}}; //사이렌4
		
static char lcdtitle[] = "PATTERN";	
static char han[] = "PATTERN1";
static char se[] = "PATTERN2";
static char yug[] = "PATTERN3";
static char gu[] = "PATTERN4";

int main()
{

	
	LcdInit();
	
	unsigned char btn;		//버튼 입력값
	unsigned char pressed;	//버튼을 계속 누르는 것인지 판단
	BtnInit();
	
	DDRA = 0xFF;
	DDRE = 0xFF;
	PORTE = 0x01; 
	PORTA = pattern[0][0]; 
	
	LcdMove(0, 0);
	LcdPuts(lcdtitle);
	
	
	TCCR0 = (1<<WGM01); //CTC모드/타이머 정지, 0C0핀 미사용
	OCR0 = 60;			//5msec마다 비교일치 인터럽트 발생
	TIMSK |= (1<<OCIE0); //타이머0 비교일치 인터럽트 허용
	sei();
	
	TCCR0 |= 0x07;		//분주비 1024로 타이머 시작
	
	while(1)
	{
		btn = BtnInput_Press(&pressed);		//버튼 입력을 받는다.
		switch(btn)
		{
			case BTN_SW0:
			if(++row==4) row=0;
			
			break;
			
			case BTN_SW1:
			while(1)
			{
				if(++row==4) row=0;
				btn = BtnInput_Press(&pressed);
				msec_delay(50);
				if(btn==BTN_SW0)
				break;
			}
			break;
			
			default:					//입력이 없거나, 여러 버튼이 눌러진 경우 제외
			break;
		}
	}
}
	ISR(TIMER0_COMP_vect) //카운터/타이머0 비교일치 인터럽트
	{
		static int col = 0;
		PORTE= 0x01<<col;		//행을 변갈아가며 불을 켜준다.
		PORTA= pattern[row][col];
		if(++col==8) col=0; //증가 값이 8이면 0으로 리셋
		switch(row)
		{
			case 0:
			LcdMove(1, 0);
			LcdPuts(han);
			break;
			case 1:
			LcdMove(1, 0);
			LcdPuts(se);
			break;
			case 2:
			LcdMove(1, 0);
			LcdPuts(yug);
			break;
			case 3:
			LcdMove(1, 0);
			LcdPuts(gu);
			break;
			default:
			break;
		}
	}
	
void msec_delay(int n)
{
	for (; n>0; n--)
	{
		_delay_ms(10);
	}
}