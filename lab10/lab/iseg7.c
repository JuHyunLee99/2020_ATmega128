/*
 * seg7.c
 *
 * Created: 2020-06-08 오후 10:48:46
 *  Author: 이주현
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "iseg7.h"		//7-세그먼트 구동 헤더파일

#define N_BUF		5		//수를 저장할 버퍼의 크기
#define N_SEGMENT	4		//7-세그먼트의 개수
#define SSEG_CONT	PORTD	//7세그먼트 제어 포트
#define DDR_CONT	DDRD
#define SSEG_DATA	PORTA	//7세그먼트 데이터 포트
#define DDR_DATA	DDRA

#define CONT_MASK	((1<<PD7)|(1<<PD6)|(1<<PD5)|(1<<PD4))
							 //제어 포트로 사용하는 포트 마스크
#define OUTPUT_VALUE (1<<PD4)//제어 포트 중 최하위 비트로 설정

static unsigned char SegTable[17] //7-세그먼트 코드값
	={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
	 0x7F, 0x6F, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71,
	  0x00};
	  
static unsigned char cnumber[N_BUF]={16, 16, 16, 16, 16};

void ISeg7Init()
{
	SSEG_CONT &= ~CONT_MASK; //모든 7-세그먼트를 끈다.
	DDR_CONT |= CONT_MASK;	//제어 포트의 상위 니블을 출력으로 설정
	
	DDR_DATA = 0xFF; //데이터 포트는 모두 출력으로 설정
	
	//타이머/카운터 0 비교일치 인터럽트설정, CTC모드로 동작
	TCCR0 = (1<<WGM01); //CTC모드/타이머 정지, 0C0핀 미사용
	OCR0 = 78;			//5msec마다 비교일치 인터럽트 발새
	TIMSK |= (1<<OCIE0); //타이머0 비교일치 인터럽트 허용
	
	TCCR0 |= 0x07;		//분주비 1024로 타이머 시작
}

void ISeg7DispNum(unsigned short num, unsigned short radix)
{
	int j;
	TIMSK &= ~(1<<OCIE0); //비교일치 인터럽트 금지
	
	for(j=0; j<N_BUF; j++) cnumber[j]=16;
	// num의 각 자리를 분리하여 배열에 저장
	j=0;							//1자리를 가리킴
	do{
		cnumber[j++]= num % radix;		//나머지
		num /= radix;					//몫
	}while(num);
	
	TIMSK |= (1<<OCIE0);		//비교일치 인터럽트 허용
}

ISR(TIMER0_COMP_vect) //카운터/타이머0 비교일치 인터럽트
{
	static int index = 0;
	SSEG_CONT=(SSEG_CONT & ~CONT_MASK) | ((OUTPUT_VALUE <<index) & (CONT_MASK));
	SSEG_DATA= ~SegTable[cnumber[index]];
	
	index++;
	if(index==N_SEGMENT) index=0;
}
	