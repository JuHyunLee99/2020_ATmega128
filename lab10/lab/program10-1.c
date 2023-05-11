/*
 * program10_1.c
 *
 * Created: 2020-06-09 오전 12:46:18
 *  Author: 이주현
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "iseg7.h"
void msec_delay(int n);
int main()
{
	unsigned char sw;
	unsigned short data = 0;
	ISeg7Init();
	sei();
	ISeg7DispNum(data, 10);
	while(1)
	{
		while((sw=~PIND &0x07)==0);
		msec_delay(30);
		while((~PIND & 0x07));
		msec_delay(30);
		if(sw==0x01)
			data += 1;
		else if (sw== 0x02)
			data +=2;
		else if (sw==0x04)
			data +=3;
			
		ISeg7DispNum(data, 10);
	}
}
void msec_delay(int n)
{
	for(; n>0; n--)
	 _delay_ms(1);

}