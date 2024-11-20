/*
 * TIM0_intrface.h
 *
 *  Created on: Sep 9, 2024
 *      Author: Asus
 */

#ifndef MCAL_TIMER0_TIM0_INTERFACE_H_
#define MCAL_TIMER0_TIM0_INTERFACE_H_

#define NO_PRESCALER	1
#define _8_PRESCALER	2
#define _64_PRESCALER	3
#define _256_PRESCALER	4
#define _1024_PRESCALER	5

#define TIM0_PRESCALER	_64_PRESCALER

#define OV_MODE			0
#define CTC_MODE		1

#define OCR_VAL			250

void TIM0_voidOVCTCInit		(u8 copy_u8mode);
void TIM0_voidSetCallBack	(void(*ptr)(void),u8 copy_u8mode);

#endif /* MCAL_TIMER0_TIM0_INTERFACE_H_ */
