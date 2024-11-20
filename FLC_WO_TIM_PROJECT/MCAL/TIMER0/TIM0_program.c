/*
 * TIM0_program.c
 *
 *  Created on: Sep 9, 2024
 *      Author: Asus
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../DIO/DIO_interface.h"

#include "TIM0_interface.h"
#include "TIM0_reg.h"

void (*TIM0_OV_PTR)(void) = NULL;
void (*TIM0_CTC_PTR)(void) = NULL;

void TIM0_voidOVCTCInit(u8 copy_u8mode)
{
	TCCR0_REG &= 0b11111000;
	TCCR0_REG |= TIM0_PRESCALER;

	if (copy_u8mode == OV_MODE) {
		CLR_BIT(TCCR0_REG,3);
		CLR_BIT(TCCR0_REG,6);

		SET_BIT(TIMSK_REG,0);
	} else if(copy_u8mode == CTC_MODE){
		SET_BIT(TCCR0_REG,3);
		CLR_BIT(TCCR0_REG,6);

		SET_BIT(TIMSK_REG,1);

		OCR0_REG = OCR_VAL;
	}
}

void TIM0_voidSetCallBack(void(*ptr)(void),u8 copy_u8mode){
	switch (copy_u8mode) {
		case OV_MODE:
			TIM0_OV_PTR = ptr;
			break;
		case CTC_MODE:
			TIM0_CTC_PTR = ptr;
			break;
	}
}

void OV_LED()
{
	static u8 count = 0;
	count ++;
	if (count==98) {
		DIO_voidTogglePinValue(DIO_PORTA,DIO_PIN0);
		count = 0;
	}
}

void CTC_LED()
{
	static u16 count = 0;
	count ++;
	if (count==500) {
		DIO_voidTogglePinValue(DIO_PORTA,DIO_PIN0);
		count = 0;
	}
}

void __vector_10(void)__attribute__((signal));
void __vector_10(void){
	TIM0_CTC_PTR();
}

void __vector_11(void)__attribute__((signal));
void __vector_11(void){
	TIM0_OV_PTR();
}
