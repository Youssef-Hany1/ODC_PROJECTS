/*
 * STD_TYPES.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Youssef Hany
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef signed char             s8;
typedef unsigned char           u8;

typedef signed short int        s16;
typedef unsigned short int      u16;

typedef signed long int         s32;
typedef unsigned long int       u32;

typedef float                   f32;
typedef double                  f64;

typedef enum
{
	FALSE,
	TRUE
}Bool;

#define NULL					(void*)0

#endif /* STD_TYPES_H_ */
