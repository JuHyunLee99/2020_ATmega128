/*
 * homework1.c
 *
 * Created: 2020-05-29 오전 2:40:43
 *  Author: 이주현
 */ 
/*도트 매트릭스의 행을 바꾸어가며 주어진 LED패턴을 켠다
이를 5msec마다 타이머 인터럽트 서비스루틴에서 행을 바꾸며 LED패턴을 변경*/
 
//CTC모드 사용
//5msec-> 분주비 1024 선택
// icount = 5 * 16 * 1000 / 1024 = 78;
// OCR0 + 1 = 78 => OCR0=77
 
#include <avr/io.h>
#include <avr/interrupt.h>
static unsigned char pattern[8]		//LED 패턴 테이블
	= {0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F};

ISR(TIMER0_COMP_vect)	//비교일치 인터럽트서비스루틴
{
	static int index = 0;	//패턴 인덱스
	
	PORTC = 0x01 << index;	//(i+1)번째 행 LED 켜짐
	PORTA = pattern[index]; //i패턴 LED 켜짐
	if(++index==8) index=0;	//패턴 인덱스 증가, 리셋
} 

int main()
{
	DDRA = 0xFF;	// 포트 A 출력으로 설정
	DDRC = 0xFF;	// 포트 C 출력으로 설정
	PORTA = 0xFF;	//패턴 LED 끄기
	PORTC = 0x00;	//행 LED 끄기
	
	TCCR0 = (1<<WGM01); //타이머/카운터0 설정: CTC모드, 타이머 정지, OC0핀 사용
	OCR0 = 77;		//10msec마다 비요일치 발생
	TIMSK = (1<<OCIE0);		// 타이머0 비교일치 인터럽트 허용
	sei();	//전역인터럽트 허용
	
	TCCR0 |= (7<<CS00);		//분주비 1024로 타이머 시작
	while(1);	//무한루프
}