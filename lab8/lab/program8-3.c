/*
 * program8_3.c
 *
 * Created: 2020-05-29 오전 12:38:08
 *  Author: 이주현
 */
//CTC모드를 사용한 주기적 LED 패턴이동
/*비교일치이용하여 200msec마다 LED패턴 이동 & 타이머0의 출력 핀인 
OC0(PB4와 공유)에 비교일치발생할 때마다 상태 반전되는 펄스 출력*/
 
//200msec:10msec를 20회 반복
//10msec-> 분주비 1024 선택
// icount = 10 * 16 * 1000 / 1024 = 156;
// OCR0 + 1 = 156 => OCR0=155
 
#include <avr/io.h>
#include <avr/interrupt.h>
static unsigned char pattern[8]		//LED 패턴 테이블
	= {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

ISR(TIMER0_COMP_vect)	//비교일치 인터럽트서비스루틴
{
	static int index = 0;	//패턴 인덱스
	static char e_enter = 0; //인터럽트 횟수
	e_enter++;	//인터럽트 횟수 증가
	if(e_enter == 20) // 200msec
	{
		e_enter=0; //인터럽트 횟수 초기화
		PORTA = pattern[index++]; //패턴 이동
		if(index==8) index=0;	//패턴 인덱스 초기화
	}
} 

int main()
{
	DDRA = 0xFF;	// 포트 A 출력으로 설정
	DDRB |= (1<<DDB4);	// PB4(OC0)을 출력으로 설정
	PORTA = 0xFF;	//LED 끄기
	
	TCCR0 = (1<<WGM01) | (1<<COM00); //타이머/카운터0 설정: CTC모드, 타이머 정지, OC0핀 사용
	OCR0 = 155;		//10msec마다 비요일치 발생
	TIMSK = (1<<OCIE0);		// 타이머0 비교일치 인터럽트 허용
	sei();	//전역인터럽트 허용
	
	TCCR0 |= (7<<CS00);		//분주비 1024로 타이머 시작
	while(1);	//무한루프
}