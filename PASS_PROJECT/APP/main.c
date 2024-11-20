/*
 * main.c
 *
 *  Created on: Sep 8, 2024
 *      Author: Youssef Hany
 */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/KEYPAD/KEYPAD_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#define F_CPU 16000000UL

#include <util/delay.h>

int main()
{
	u8 counter = 0;
	u16 psw = 1234;
	u16 entered_psw;
	u8 i, num = 0xFF;

	u8 Correct_psw[] = {"CORRECT PASSWORD"};
	u8 Wrong_psw[] = {"PLEASE TRY AGAIN"};

	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_PIN_OUTPUT);

	LCD_voidInit();
	KEYPAD_voidInit();

	u8 first_char[] = {
		0b00000,
		0b01100,
		0b00010,
		0b11111,
		0b00000,
		0b00000,
		0b00000,
		0b00000
	};
	u8 second_char[] = {
		0b00000,
		0b00000,
		0b00000,
		0b00111,
		0b00100,
		0b01000,
		0b10000,
		0b00000
	};
	u8 third_char[] = {
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00000,
		0b00000,
		0b00000,
		0b00000
	};
	u8 fourth_char[] = {
		0b00000,
		0b00111,
		0b00101,
		0b11111,
		0b00000,
		0b00000,
		0b00000,
		0b00000
	};
	u8 fifth_char[] = {
		0b00000,
		0b00000,
		0b00010,
		0b00101,
		0b10110,
		0b10010,
		0b01110,
		0b00000,
	};

	while(1)
	{
		u16 entered_psw = 0;
		for (i = 0; i < 4; ++i) {
			num = 0xFF;
			while(num == 0xFF){
				num = KEYPAD_u8AdjustKeyPadNum();
			}
			LCD_voidDisplayNumber(num);
			LCD_voidGoToSpecificPosition(0,i);
			_delay_ms(500);
			LCD_voidDisplayChar('*');
			entered_psw = entered_psw*10 + num;
		}
		if (entered_psw == psw){
			LCD_voidClear();
			LCD_voidDisplayString(Correct_psw);
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_HIGH);
			_delay_ms(10000);
			LCD_voidClear();
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_PIN_LOW);
			counter = 0;
		} else{
			if (counter < 1) {
				counter++;
				LCD_voidClear();
				LCD_voidDisplayString(Wrong_psw);
				_delay_ms(1500);
				LCD_voidClear();
			} else {
				LCD_voidClear();
				LCD_voidDrawData(0, first_char, 0, 11);
				LCD_voidDrawData(1, second_char, 0, 10);
				LCD_voidDrawData(2, third_char, 0, 9);
				LCD_voidDrawData(3, fourth_char, 0, 8);
				LCD_voidDrawData(4, fifth_char, 0, 7);
				DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_HIGH);
				_delay_ms(1000);
				LCD_voidClear();
				DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_PIN_LOW);
				counter = 0;
			}
		}
	}
}
