/*
 * lcd.h
 *
 * Created: 2020-06-10 오후 7:57:16
 *  Author: 이주현
 */ 


#ifndef LCD_H_
#define LCD_H_

//LCD 제어명령
#define ALLCLR 0x01 //화면을지운다
#define HOME 0x02 //커서를 홈으로 보낸다.
#define LN21 0xc0 //커서를 2번째라인의 첫번째 위치에 위치

#define ENTMOD 0x06 //entry mode
#define FUNSET 0x28 //function set
#define DISP_ON 0x0c //디스플레이를 켠다
#define DISP_OFF 0x08 //디스플레이를 끈다
#define CURSOR_ON 0x0e //커서를 켠다
#define CURSOR_OFF 0x0c //커서를 끈다
#define CURSOR_LSHIFT 0x10 //커서를 왼쪽으로이동
#define CURSOR_RSHIFT 0x14 //커서를 오른쪽으로 이동
#define DISP_LSHIFT 0x18 //디스플레이를 왼쪽으로이동
#define DISP_RSHIFT 0x1c //디스플레이를 오른쪽으로 이동

//LCD 제어 모듈 함수
void LcdInit(void); //초기화
void LcdCommand(char command);  //디스플레이 이동
void LcdMove(char line, char pos); //커서이동(행, 열)
void LcdPutchar(char ch); //한글자 입력
void LcdPuts(char *str); //문자열 입역
void LcdNewchar(char ch, char font[]);



#endif /* LCD_H_ */