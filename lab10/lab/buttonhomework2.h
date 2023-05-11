/*
 * button.h
 *
 * Created: 2020-06-09 오전 1:08:46
 *  Author: 이주현
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#define BTN_SW0		0X01	//SW0을 누름
#define BTN_SW1		0X02	//SW1을 누름
#define BTN_SW2		0X04	//SW2을 누름
#define NO_BTN		0X00	//입력이 없음
#define BTN_MASK	(BTN_SW0 | BTN_SW1)

void BtnInit(void);
unsigned char BtnInput(void);
unsigned char BtnIput_Press(unsigned char *pressed);

#endif /* BUTTON_H_ */