/*
 * KeyPad_interface.h
 *
 *  Created on: Sep 5, 2024
 *      Author: Youssef Hany
 */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

#define ROWS_NUM 4
#define COLS_NUM 4

#define FIRST_ROWS_PIN 4
#define FIRST_COLS_PIN 2

u8		KEYPAD_u8AdjustKeyPadNum	(void);
void 	KEYPAD_voidInit				(void);

#endif /* KEYPAD_INTERFACE_H_ */
