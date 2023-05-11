/*
 * program8_2.c
 *
 * Created: 2020-05-29 오전 12:14:22
 *  Author: 이주현
 */ 
// 표준모드 비교일치 인터럽트를 사용한 주기적 LED 패턴 이동 -> 200msec마다

//200msec: 10msec를 20회 반복
// 10msec -> 분주비 1024 선택
//icount = 10 * 16 *1000 / 1024 = 156
//OCR0 += 156 으로 설정

#include <avr/io.h>
#include <avr/interrupt.h>
static unsigned char pattern[8]		// LED 패턴 테이블
	= {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
ISR(TIMER0_COMP_vect) // 비교일치 인터럽트 서비스루틴
{
	static int index = 0;	// 패턴 인덱스
	static char e_ener = 0;		// 인터럽트 횟수
	OCR0 += 156;	//10msec후에 이너럽트 발생
	e_ener++;	// 인터럽트 횟수 증가
	if(e_ener == 20)	//200msce
	{
		e_ener = 0;		//인터럽트 횟수 초기화 
		PORTA = pattern[index++];	//패턴 이동
		if(index==8) index=0;	//패턴 인텍스 초기화
	}
}

int main()
{
	DDRA=0xFF;	//포트A 출력으로 설정
	PORTA=0xFF;		//LED 소등
	
	TCCR0 = 0x00;	//표준모드, 타이머 정지
	OCR0 = 156;		//10msec 후에 비교일치 발생
	
	TIMSK = (1<<OCIE0);		//타이머 0 비교일치 인터럽트 허용
	sei();	//전역 인터럽트 허용
	TCCR0 |= (7<<CS00);		//분주비 1024로 타이머 시작
	while(1);	//무한루프
}