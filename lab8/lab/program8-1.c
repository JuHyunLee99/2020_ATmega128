/*
 * program8_1.c
 *
 * Created: 2020-05-28 오후 11:47:31
 *  Author: 이주현
 */
//표준모드 오버플로 인터럽트를 사용한 주기적 LED 패턴 이동 : 200msec 마다

//200msec: 10msec를 20반 반복
//10mse -> 분주비 1024 선택
// icount = 10 * 16*1000 / 1024 = 156
//TCNT0초기값 = 256 - 156 = 100 으로 설정

#include <avr/io.h>
#include <avr/interrupt.h>
static unsigned char pattern[8]		//패턴 인덱스
	= {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};
		
ISR(TIMER0_OVF_vect) //타이머 0 오버플로 인터럽트 서비스루틴
{
	static int index = 0;		//패턴 인덱스
	static char n_enter=0;		//인터럽트 횟수
	
	TCNT0 = 100;		//10msec후에 인터럽트 발생
	n_enter++;		//인터럽트 횟수 증가
	
	if(n_enter == 20)		//20msec
	{
		n_enter = 0;		//인터럽트 횟수 초기화
		PORTA = pattern[index++];		//패턴 이동
		if(index==8) index=0;			//패턴 인덱스 초기화
	}	
}

int main()
{
	DDRA=0xFF;		//포트A를 출력으로 설정
	PORTA=0xFF;		//LED 소등
	
	TCCR0 = 0x00;		//표준모드, 타이머 정지
	TCNT0 = 100;		//타이머 초기값 설정
	
	TIMSK = (1<<TOIE0);			// 타이머0 오버플로 인터럽트 허용
	sei();		//전역 인터럽트 허용
	
	TCCR0 |= (7<<CS00);			//분주비 1024로 타이머 시작
	
	while(1);		//무한루프
}