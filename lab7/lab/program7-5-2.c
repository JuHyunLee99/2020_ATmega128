/*
 * program7_5_2.c
 *
 * Created: 2020-05-29 오전 2:07:33
 *  Author: 이주현
 */ 
//외부 인터럽트 INT0을 사용하여 LED패턴 이동(main()함수에서 패턴 출력)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DEBOUNCING_DELAY	20
void msec_delay(int n);			//시간지연함수
static unsigned char pattern[8]			//LED 패턴 테이블
= {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
static int index = 0;				//패턴 인덱스

ISR(INT0_vect)						//인터럽트 서비스루틴
{
	if(++index==8) index=0;			//인텍스 8이면 0으로 리셋
	msec_delay(DEBOUNCING_DELAY);	//디바운싱
	while(~PIND&0x01);				//스위치 해제를 기다림
	msec_delay(DEBOUNCING_DELAY);	//디바운싱
	
	EIFR = (1<<INTF0);				//인터럽트 플래그 INT0을 리셋
}

int main()
{
	DDRA = 0xFF;					//포트A를 출력으로 설정
	PORTA = pattern[0];				//처음 패턴으로 켠다
	
	EICRA = (2<<ISC00);				//ISC01:0=2 하강 모서리 트리거 
	EIMSK = (1<<INT0);				//INT0 인터럽트 허용
	sei();							//전역 인터럽트 허용
	
	while(1)						//무한루프
	{
		PORTA = pattern[index];		//index번째 패턴으로 켠다
	}
}

void msec_delay(int n)
{
	for (;n>0;n--)					//1msec 시간지연 n회 반복
		_delay_ms(1);				//1msec 시간지연
}