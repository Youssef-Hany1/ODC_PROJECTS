/*
 * LCD_config.h
 *
 *  Created on: Sep 5, 2024
 *      Author: Youssef Hany
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* Macros for Rs configuration */
#define LCD_RS_PORT		DIO_PORTB
#define LCD_RS_PIN		DIO_PIN1

/* Macros for RW configuration */
#define LCD_RW_PORT		DIO_PORTB
#define LCD_RW_PIN		DIO_PIN2

/* Macros for Enable configuration */
#define LCD_E_PORT		DIO_PORTB
#define LCD_E_PIN		DIO_PIN3

#if LCD_MODE == _4_BIT_MODE

/* 4 Bit Mode Data Pins Configuration */
#define LCD_D4_PORT		DIO_PORTA
#define LCD_D4_PIN		DIO_PIN4

#define LCD_D5_PORT		DIO_PORTA
#define LCD_D5_PIN		DIO_PIN5

#define LCD_D6_PORT		DIO_PORTA
#define LCD_D6_PIN		DIO_PIN6

#define LCD_D7_PORT		DIO_PORTA
#define LCD_D7_PIN		DIO_PIN7

#elif LCD_MODE == _8_BIT_MODE

/* 8 Bit Mode Data Pins Configuration */
#define LCD_DPORT		DIO_PORTA

#endif

#endif /* LCD_CONFIG_H_ */
