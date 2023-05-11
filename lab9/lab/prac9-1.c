/*
 * prac9_1.c
 *
 * Created: 2020-06-08 오후 10:45:46
 *  Author: 이주현
 */ 
#include <avr/io.h>
#include "seg7.h"		//7세그먼트 출력 프로그램 헤더파일

int main()
{
	unsigned short data=205;
	
	Seg7Init();			//7세스먼트 초기화
	
	while(1)
	{
		Seg7DispNum(data, 10);	//10진수로 표시
	}
}