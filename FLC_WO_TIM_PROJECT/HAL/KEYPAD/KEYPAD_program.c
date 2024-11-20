/*
 * KeyPad_program.c
 *
 *  Created on: Sep 5, 2024
 *      Author: Youssef Hany
 */

#include <util/delay.h>

/* UTILES_LIB */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/* MCAL */
#include "../../MCAL/DIO/DIO_interface.h"

/* HAL */
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"

u8 KEYPAD_ARR[ROWS_NUM][COLS_NUM] = {	{7,8,9,'/'},
										{4,5,6,'*'},
										{1,2,3,'-'},
										{'c','0','=','+'}	};

void KEYPAD_voidInit (void)
{
	u8 ROW_ARR[ROWS_NUM] = {KeyPad_R1_PIN,KeyPad_R2_PIN,KeyPad_R3_PIN,KeyPad_R4_PIN};
	u8 COL_ARR[COLS_NUM] = {KeyPad_C1_PIN,KeyPad_C2_PIN,KeyPad_C3_PIN,KeyPad_C4_PIN};

	u8 local_u8i;
	for (local_u8i = 0; local_u8i < COLS_NUM; ++local_u8i) {
		DIO_voidSetPinDirection(KeyPad_RPORT,ROW_ARR[local_u8i],DIO_PIN_INPUT);
		DIO_voidSetPinValue(KeyPad_RPORT,ROW_ARR[local_u8i],DIO_PIN_HIGH);
		DIO_voidSetPinDirection(KeyPad_CPORT,COL_ARR[local_u8i],DIO_PIN_OUTPUT);
		DIO_voidSetPinValue(KeyPad_CPORT,COL_ARR[local_u8i],DIO_PIN_HIGH);
	}
}

u8 KEYPAD_u8AdjustKeyPadNum	(void)
{
	u8 ROW_ARR[ROWS_NUM] = {KeyPad_R1_PIN,KeyPad_R2_PIN,KeyPad_R3_PIN,KeyPad_R4_PIN};
	u8 COL_ARR[COLS_NUM] = {KeyPad_C1_PIN,KeyPad_C2_PIN,KeyPad_C3_PIN,KeyPad_C4_PIN};

	u8 local_u8Row, local_u8Col;
	u8 val = 0xFF;

	for (local_u8Col = 0; local_u8Col < COLS_NUM; ++local_u8Col) {
		DIO_voidSetPinValue(KeyPad_CPORT,COL_ARR[local_u8Col],DIO_PIN_LOW);

		for (local_u8Row = 0; local_u8Row < ROWS_NUM; ++local_u8Row) {
			if(DIO_u8GetPinValue(KeyPad_RPORT,ROW_ARR[local_u8Row]) == 0)
			{
				val = KEYPAD_ARR[local_u8Row][local_u8Col];
				while(DIO_u8GetPinValue(KeyPad_RPORT,ROW_ARR[local_u8Row]) == 0){}
				return val;
			}
		}

		DIO_voidSetPinValue(KeyPad_CPORT,COL_ARR[local_u8Col],DIO_PIN_HIGH);
	}
	return val;
}
