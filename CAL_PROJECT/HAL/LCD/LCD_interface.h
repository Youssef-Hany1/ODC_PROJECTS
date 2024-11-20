/*
 * LCD_interface.h
 *
 *  Created on: Sep 5, 2024
 *      Author: Youssef Hany
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/* LCD  Mode */
#define  _4_BIT_MODE     0
#define  _8_BIT_MODE     1

#define  LCD_MODE  _4_BIT_MODE

#define LCD_SHIFT_LEFT		0
#define LCD_SHIFT_RIGHT		1

void LCD_voidInit					(void);
void LCD_voidSendCommand			(u8 copy_u8cmnd);
void LCD_voidDisplayChar			(u8 copy_u8Data);
void LCD_voidDisplayString			(u8* copy_pu8String);
void LCD_voidDisplayNumber			(u32 copy_u32Number);
void LCD_voidDisplaySignedNumber	(s32 copy_s32Number);
void LCD_voidDisplayFloat			(f32 copy_f32Number);
void LCD_voidClear					(void);
void LCD_voidShift					(u8 copy_u8ShiftingDirection);
void LCD_voidGoToSpecificPosition	(u8 copy_u8LineNumber, u8 copy_u8Position);
void LCD_voidDrawData				(u8 copy_u8Pattern , u8* copy_pu8Data , u8 copy_u8X , u8 copy_u8Y);

#endif /* LCD_INTERFACE_H_ */
