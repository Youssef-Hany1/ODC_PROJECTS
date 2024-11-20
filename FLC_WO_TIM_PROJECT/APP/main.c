/*
 * main.c
 *
 *  Created on: Sep 4, 2024
 *      Author: Youssef Hany
 */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_interface.h"
#define F_CPU 16000000UL

void DC_MOTOR_voidForward()
{
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH);
}
void DC_MOTOR_voidRight()
{
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_LOW);
}
void DC_MOTOR_voidLeft()
{
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_HIGH);
}
void DC_MOTOR_voidReverse()
{
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN0,DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN1,DIO_PIN_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_PIN_LOW);
}

int main()
{
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN0,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_PIN_OUTPUT);

	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_PIN_OUTPUT);

	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN4,DIO_PIN_HIGH);
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN5,DIO_PIN_HIGH);

	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_INPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_INPUT);

	while(1)
	{
		if((DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)==0)&&(DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)==0)){
			DC_MOTOR_voidForward();
		}
		if((DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)==0)&&(DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)==1)){
			DC_MOTOR_voidLeft();
		}
		if((DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)==1)&&(DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)==0)){
			DC_MOTOR_voidRight();
		}
		if((DIO_u8GetPinValue(DIO_PORTA,DIO_PIN0)==1)&&(DIO_u8GetPinValue(DIO_PORTA,DIO_PIN1)==1)){
			DC_MOTOR_voidReverse();
		}
	}
}
