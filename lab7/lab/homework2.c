/*
 * homework2.c
 *
 * Created: 2020-06-10 오후 9:05:35
 *  Author: 이주현
 */ 
// sw0누르면 A->B->C->D 순으로 변함, sw1누르면 역순으로 변함
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DEBOUNCING_DELAY	40

void msec_delay(int n);

static int row = 0;
static int col = 0;
unsigned char pattern[4][8]
		={{0xE7, 0xDB, 0xDB, 0xDB, 0x81, 0xBD, 0xBD, 0xBD},  //A
		  {0x83, 0xBD, 0xBD, 0x83,0xBD, 0xBD, 0xBD, 0x83,},  //B
		  {0xE1, 0xDF, 0xBF, 0xBF, 0xBF, 0xBF, 0xDF, 0xE1},  //C
		  {0x87, 0xBB, 0xBD, 0xBD, 0xBD, 0xBD, 0xBB, 0x87}}; //D
			  
ISR(INT0_vect)					//외부 인터럽트 0 서비스 루틴
{
	if(++row==4) row=0;					//행 증가값 4이면 0으로 리셋
	msec_delay(DEBOUNCING_DELAY);		//스위치 누름에 대한 디바운싱
	while(~PIND & 0x01);					//스위치 해제를 기다림
	msec_delay(DEBOUNCING_DELAY);		//스위취 해제에 대한 디바운싱
	EIFR = (1<<INTF0);					//인터럽트 프러그 INTF0 리셋
}

ISR(INT1_vect)
{
	if(--row == -1) row=3;
	msec_delay(DEBOUNCING_DELAY);		//스위치 누름에 대한 디바운싱
	while(~PIND & 0x02);					//스위치 해제를 기다림
	msec_delay(DEBOUNCING_DELAY);		//스위취 해제에 대한 디바운싱
	EIFR = (1<<INTF1);
}

int main()
{
	DDRA = 0xFF;
	DDRE = 0xFF;
	PORTE = 0X01 << 0; //첫 행을 켠다
	PORTA = pattern[0][0]; //처음 패턴으로 LED를 켠다
	
	EICRA = (2>>ISC00) | (2<<ISC10); //INT0 하강모서리 트리거
	EIMSK = (1<<INT0) | (1<<INT1);
	
	sei();
	
	while(1)
	{
		msec_delay(1);			//모든 행에 불이 켜지도록한다.
		if(++col==8) col=0;		//증가 값이 8이면 0으로 리셋
		PORTE= 0x01<<col;		//행을 변갈아가며 불을 켜준다.
		PORTA= pattern[row][col]; //패턴을 번갈아가며 불을 켜준다.
	}
}

void msec_delay(int n)
{
	for (; n>0; n--)
		_delay_ms(1);
}
