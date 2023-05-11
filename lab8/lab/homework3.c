/*
 * homework3.c
 *
 * Created: 2020-05-29 오전 4:38:41
 *  Author: 이주현
 */ 
/*
 * homework2.c
 *
 * Created: 2020-05-29 오전 4:28:39
 *  Author: 이주현
 */ 
//Phase Correct PMW신호로 LED 밝기 조절
//COM01:0=3 -> 비교값 커지면 밝기 작아짐
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
	duty += 5;
	if(duty >= 250) duty = 250;
	msec_delay(DEBOUNCING_DELAY);
	while(~PIND&0X01);
	msec_delay(DEBOUNCING_DELAY);
	EIFR = (1<<INTF0);
}
ISR(INT1_vect)		// 외부 인터럽트 1 서비스루틴
{
	duty -= 5;
	if(duty <= 5) duty = 5;
	msec_delay(DEBOUNCING_DELAY);
	while(~PIND&0X02);
	msec_delay(DEBOUNCING_DELAY);
	EIFR = (1<<INTF1); 
}
int main()
{
	DDRB |= (1<<DDB4);
	TCCR0 = (1<<WGM00)|(2<<COM00);
	EICRA = (2<<ISC10)|(2<<ISC00);
	EIMSK = (1<<INT0)|(1<<INT1);
	sei();
	
	TCCR0 |=(2<<CS00);
	
	while(1)
	{
		OCR0 = duty;
	}
}
void msec_delay(int n)
{
	for(;n>0;n--)			// 1msec 시간지연 n회 반복
		_delay_ms(1);		// 1msec 시간지연
}