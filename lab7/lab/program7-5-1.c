/*
 * program7_5_1.c
 *
 * Created: 2020-05-29 오전 1:37:00
 *  Author: 이주현
 */ 
// 외부 인터럽트 INT0을 사용하여 LED 패턴이동 (인터럽트 서비스 루틴안에 패턴출력 포함)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DEBOUNCING_DELAY	20
void msec_delay(int n);			//시간지연함수
static unsigned char pattern[8]			//LED 패턴 테이블
	= {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
ISR(INT0_vect)		//인터럽트 서비스 루틴
{
	static int i=0;			//패턴 인덱스
	if(++i==8) i=0;			//증가값이 8이면 0으로 리셋
	PORTA = pattern[i];			//i번째 패턴으로 LED 켠다
	msec_delay(DEBOUNCING_DELAY);	//디바운싱
	while(~PIND&0X01);		//스위치 해제를 기다림
	msec_delay(DEBOUNCING_DELAY);	//디바운싱
	
	EIFR = (1<<INTF0);		//인터럽트 플래그 INTF0을 리셋
}

int main()
{
	DDRA=0xFF;		//포트A 출력으로 설정
	PORTA = pattern[0]; //처음 패턴으로 켠다
	
	EICRA=(2<<ISC00);	//ICS01:2=2 하강 모거시 트리거
	EIMSK=(1<<INT0);	//INT0 인터럽트 허용
	sei();				//전역 인터럽트 허용
	while(1);			//무한루프
}

void msec_delay(int n)
{
	for(; n>0; n--)		//1msec 시간 지연 n회 반복
		_delay_ms(1);	//1msec 시간 지연
}