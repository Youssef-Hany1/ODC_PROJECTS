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

void CAL();

int main()
{
    LCD_voidInit();
    KEYPAD_voidInit();

    while(1)
    {
    	CAL();
    }
}

void CAL()
{
    f32 num1 = 0;
    f32 num2 = 0;
    f32 out_num;
    u8 num;
    u8 op;
    //first number
    while(num1 == 0){
        num = 0xFF;
        while(num == 0xFF){
            num = KEYPAD_u8AdjustKeyPadNum();
        }
        if (num == 0) {
            LCD_voidDisplayNumber(num);
            break;
        }
        if((num >= 1) && (num <= 9)){
            num1 = num1*10 + num;
            LCD_voidDisplayNumber(num);
        }
    }

    num = 0xFF;
    while(num == 0xFF){
        num = KEYPAD_u8AdjustKeyPadNum();
    }

    if (num1 != 0) {
        do {
            if((num >= 0) && (num <= 9)){
                num1 = num1*10 + num;
                LCD_voidDisplayNumber(num);
            }
            num = 0xFF;
            while(num == 0xFF){
                num = KEYPAD_u8AdjustKeyPadNum();
            }
        }while ((num >= 0) && (num <= 9));
    }

    LCD_voidDisplayChar(' ');
    op = num;
    LCD_voidDisplayChar((char)op);
    LCD_voidDisplayChar(' ');

    //second number
    while(num2 == 0){
        num = 0xFF;
        while(num == 0xFF){
            num = KEYPAD_u8AdjustKeyPadNum();
        }
        if (num == 0) {
            LCD_voidDisplayNumber(num);
            break;
        }
        if((num >= 1) && (num <= 9)){
            num2 = num2*10 + num;
            LCD_voidDisplayNumber(num);
        }
    }

    num = 0xFF;
    while(num == 0xFF){
        num = KEYPAD_u8AdjustKeyPadNum();
    }

    if (num2 != 0) {
        do {
            if((num >= 0) && (num <= 9)){
                num2 = num2*10 + num;
                LCD_voidDisplayNumber(num);
            }
            num = 0xFF;
            while(num == 0xFF){
                num = KEYPAD_u8AdjustKeyPadNum();
            }
        }while ((num >= 0) && (num <= 9));
    }

    LCD_voidDisplayChar(' ');
    LCD_voidDisplayChar('=');
    LCD_voidDisplayChar(' ');

    // Perform the operation
    switch (op) {
        case '+':
            out_num = num1 + num2;
            break;
        case '-':
            out_num = num1 - num2;
            break;
        case '*':
            out_num = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                out_num = num1 / num2;
                LCD_voidDisplayFloat(out_num);
            } else {
                LCD_voidDisplayString("ERR");
            }
            break;
        default:
            break;
    }

    // Display the result
    if(op != '/') {
        LCD_voidDisplaySignedNumber((s32)out_num);
    }

    // Wait for the user to press 'c' to clear
    do {
        num = 0xFF;
        while(num == 0xFF){
            num = KEYPAD_u8AdjustKeyPadNum();
        }
    } while (num != 'c');

    LCD_voidClear();
}
