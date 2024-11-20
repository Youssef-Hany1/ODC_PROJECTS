/*
 * EXTI_interface.h
 *
 * Created: 8/24/2024 4:20:26 PM
 *  Author: AMIT
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


/* senes control  */

#define   LOW_LEVEL              0 
#define   ANY_LOGICAL_CHANCH     1
#define   FALLING_EDGE           2 
#define   RISING_EDGE            3 


/* interrupt pins */

#define  _INT_0      0 
#define  _INT_1      1 
#define  _INT_2      2 

void EXTI_voidInit(u8 copy_u8interrupt, u8 copy_u8sense ) ; 
void EXTI_voidSetCallBack(void(*ptr)(void),u8 copy_u8IntNum) ;
void EXT_voidEnable(u8 copy_u8IntNum);
void EXT_voidDisable(u8 copy_u8IntNum);

#endif /* EXTI_INTERFACE_H_ */
