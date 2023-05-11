/*
 * program8_4.c
 *
 * Created: 2020-05-29 오전 3:01:45
 *  Author: 이주현
 */ 
//FAST PMW 신호로 LED 밝기 조절
//COM01:0=2 -> 듀티비 커지면 밝기 낮아짐
//SW0 누르면 듀티비 +5, SW1 누르면 듀티비 -5
//분주비 8
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define DEBOUNCING_DELAY	20		//msec
void msec_delay(int n);				//시간지연함수

static volatile unsigned char duty = 125; //듀티비 초기값

ISR(INT0_vect)		// 외부 인터럽트 0 서비스루틴
{
	duty += 5;		// 듀티비 5 증가
	if(duty >= 250) duty = 250;
	msec_delay(DEBOUNCING_DELAY);
	while(~PIND&0x01);		//스위치 해제 기다림
	msec_delay(DEBOUNCING_DELAY);
	EIFR = (1<<INTF0);		// 외부 인터럽트0 플래그 리셋
}
ISR(INT1_vect)		// 외부 인터럽트 1 서비스루틴
{
	duty -= 5;		// 듀티비 5 감소
	if(duty <=5) duty = 5;
	msec_delay(DEBOUNCING_DELAY);
	while(~PIND&0x02);		// 스위치 해제 기다림
	msec_delay(DEBOUNCING_DELAY);
	EIFR = (1<<INTF1);		// 외부 인터럽트1 플래그 리셋
}
int main()
{
	DDRB |= (1<<DDB4);		// PB4(OC0)를 출력으로 설정
	TCCR0 = (1<<WGM01)|(1<<WGM00)|(2<<COM00);
	// 타이머/카운터 0 설정: FAST PWM모드, 타이머 정지, OC0 사용
	EICRA = (2<<ISC10)|(2<<ISC00);		//INT0,1 하강 모서리
	EIMSK = (1<<INT0)|(1<<INT1);		//외부 인터럽트 0, 1 허용
	sei();					// 전역 인터럽트 허용
	 
	TCCR0 |= (2<<CS00);		//분주지 8로 타이머 시작
	
	while(1)
	{
		OCR0 = duty;		// PMW 신호의 듀티비를 바꾼다
	}
}
void msec_delay(int n)
{
	for(;n>0;n--)			// 1msec 시간지연 n회 반복
		_delay_ms(1);		// 1msec 시간지연
}