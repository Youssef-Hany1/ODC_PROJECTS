/*
 * LCD_program.c
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
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

void LCD_voidInit (void)
{
	/* Initialized LCD pins as Output Pins */
	DIO_voidSetPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT,LCD_E_PIN,DIO_PIN_OUTPUT);

	_delay_ms(35);

	/* N (# of lines) - F (font) */
	/* Function Set (2 Lines, 5*7 font) */
	/* set Rs pin = 0 (command) */
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	/* set RW pin = 0 (write) */
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);

	#if LCD_MODE == _4_BIT_MODE

	PRV_voidWriteHalfPort(0b0010);
	PRV_voidEnableTriggerWrite();
	LCD_voidSendCommand(0b00101000); //0b0010NFXX

	#elif LCD_MODE == _8_BIT_MODE

	LCD_voidSendCommand(0b00111000);

	#endif

	_delay_us(45);

	/* D (display ON/OFF) - C (cursor ON/OFF) - B (blink cursor ON/OFF) */
	/* Display On/Off Control (Display on, Cursor on, Blink on) */
	LCD_voidSendCommand(0b00001100); //ob00001DCB
	_delay_us(45);

	/* Display Clear */
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);

	/* I (increment mode (inc = 1 / dec = 0)) - S (shift) */
	/* Entry Mode Set (Increment on, Shift off) */
	LCD_voidSendCommand(0b00000110); //0b000001IS

}

void LCD_voidDisplayChar (u8 copy_u8Data)
{
	/* set Rs pin = 1 (data) */
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);

	/* set RW pin = 0 (write) */
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);

	/* Write The Most 4 bits of data on Data Pins */
	PRV_voidWriteHalfPort(copy_u8Data>>4);

	/* Enable */
	PRV_voidEnableTriggerWrite();

	/* Write The Least 4 bits of data on Data Pins */
	PRV_voidWriteHalfPort(copy_u8Data);

	/* Enable */
	PRV_voidEnableTriggerWrite();
}

void LCD_voidSendCommand (u8 copy_u8cmnd)
{
	/* set Rs pin = 0 (command) */
	DIO_voidSetPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);

	/* set RW pin = 0 (write) */
	DIO_voidSetPinValue(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);

	/* Write The Most 4 bits of command on Data Pins */
	PRV_voidWriteHalfPort(copy_u8cmnd>>4);

	/* Enable */
	PRV_voidEnableTriggerWrite();

	/* Write The Least 4 bits of command on Data Pins */
	PRV_voidWriteHalfPort(copy_u8cmnd);

	/* Enable */
	PRV_voidEnableTriggerWrite();
}

void LCD_voidDisplayString (u8* copy_pu8String)
{
	if (copy_pu8String != NULL) {
		u8 local_u8i = 0;
		while(copy_pu8String[local_u8i]!='\0')
		{
			LCD_voidDisplayChar(copy_pu8String[local_u8i]);
			local_u8i++;
		}
	} else {
		//return Error State
	}
}

void LCD_voidDisplayNumber (u32 copy_u32Number)
{
	if (copy_u32Number == 0) {
		LCD_voidDisplayChar(48);
	} else {
		s8 local_u8i = 0;
		u8 local_u8Number[16];
		while(copy_u32Number != 0)
		{
			local_u8Number[local_u8i] = copy_u32Number%10 + 48;
			local_u8i++;
			copy_u32Number /= 10;
		}
		local_u8i--;
		while(local_u8i >= 0)
		{
			LCD_voidDisplayChar(local_u8Number[local_u8i]);
			local_u8i--;
		}
	}
}

void LCD_voidDisplaySignedNumber(s32 copy_s32Number) {
    if (copy_s32Number < 0) {
        LCD_voidDisplayChar('-');
        copy_s32Number = -copy_s32Number;
    }
    LCD_voidDisplayNumber((u32)copy_s32Number);
}

void LCD_voidDisplayFloat(f32 copy_f32Number) {
	if (copy_f32Number < 0) {
		LCD_voidDisplayChar('-');
		copy_f32Number = -copy_f32Number;
	}
    u32 local_u32IntegerPart = (u32)copy_f32Number;
    LCD_voidDisplayNumber(local_u32IntegerPart);

    LCD_voidDisplayChar('.');

    f32 local_f32FractionalPart = copy_f32Number - local_u32IntegerPart;
    local_f32FractionalPart = local_f32FractionalPart * 100;
    LCD_voidDisplayNumber((u32)local_f32FractionalPart);
}


void LCD_voidDrawData(u8 copy_u8Pattern , u8* copy_pu8Data , u8 copy_u8X , u8 copy_u8Y){
	  u8 loc_i=0 ;
	  u8 address_CGRAM=copy_u8Pattern*8 ;  // set address
	  /* set CGRAM */
	  CLR_BIT(address_CGRAM,7) ;
	  SET_BIT(address_CGRAM,6) ;
	  LCD_voidSendCommand(address_CGRAM) ;

	  /* draw data in CGRAM */
	  for (loc_i=0 ; loc_i<8 ;loc_i++)
	  {
		  LCD_voidDisplayChar(copy_pu8Data[loc_i]);
	  }
	  LCD_voidGoToSpecificPosition(copy_u8X,copy_u8Y);
	  LCD_voidDisplayChar(copy_u8Pattern) ;
}

void LCD_voidClear (void)
{
	LCD_voidSendCommand(0b00000001);
}

void LCD_voidShift (u8 copy_u8ShiftingDirection)
{
	if (copy_u8ShiftingDirection <= LCD_SHIFT_RIGHT) {
		switch (copy_u8ShiftingDirection) {
			case LCD_SHIFT_LEFT:
				LCD_voidSendCommand(0b00011000);
				break;
			case LCD_SHIFT_RIGHT:
				LCD_voidSendCommand(0b00011100);
				break;
		}
	} else {
		//return Error State
	}
}

void LCD_voidGoToSpecificPosition (u8 copy_u8LineNumber, u8 copy_u8Position)
{
	/* set address */
	u8 ddram_address= copy_u8Position+copy_u8LineNumber*0x40 ;

	/*set DDRAM */
	SET_BIT(ddram_address,7) ;  // set bit7 in ddram

	LCD_voidSendCommand(ddram_address) ;
}

static void PRV_voidWriteHalfPort (u8 copy_u8cmnd)
{
	DIO_voidSetPinValue(LCD_D4_PORT,LCD_D4_PIN,GET_BIT(copy_u8cmnd,0));
	DIO_voidSetPinValue(LCD_D5_PORT,LCD_D5_PIN,GET_BIT(copy_u8cmnd,1));
	DIO_voidSetPinValue(LCD_D6_PORT,LCD_D6_PIN,GET_BIT(copy_u8cmnd,2));
	DIO_voidSetPinValue(LCD_D7_PORT,LCD_D7_PIN,GET_BIT(copy_u8cmnd,3));
}


static void PRV_voidEnableTriggerWrite (void)
{
	/* Enable Pulse *//* H => L */
	DIO_voidSetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}
