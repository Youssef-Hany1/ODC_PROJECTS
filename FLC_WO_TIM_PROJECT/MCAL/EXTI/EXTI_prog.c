/*
 * EXTI_prog.c
 *
 * Created: 8/24/2024 4:22:03 PM
 *  Author: AMIT
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "EXTI_interface.h" 
#include "EXTI_reg.h" 

/*array of function pointers */
//void(*INT_PTR[3])(void)={null} ; 

void (*INT0_PTR)(void) = NULL;
void (*INT1_PTR)(void) = NULL;
void (*INT2_PTR)(void) = NULL;

void EXTI_voidInit(u8 copy_u8interrupt, u8 copy_u8sense ){
	switch(copy_u8interrupt){
		case _INT_0 :
			if(copy_u8sense == LOW_LEVEL){
				CLR_BIT(MCUCR_REG,0) ;
				CLR_BIT(MCUCR_REG,1) ;
			}
			else if (copy_u8sense==ANY_LOGICAL_CHANCH)
			{
				SET_BIT(MCUCR_REG,0) ;
				CLR_BIT(MCUCR_REG,1) ;
			}
			else if (copy_u8sense ==FALLING_EDGE)
			{
				CLR_BIT(MCUCR_REG,0) ;
				SET_BIT(MCUCR_REG,1) ;
			}
			else if (copy_u8sense==RISING_EDGE)
			{
				SET_BIT(MCUCR_REG,0) ;
				SET_BIT(MCUCR_REG,1) ;
			}
			else{
			} break;
		case _INT_1 :
			if(copy_u8sense == LOW_LEVEL)
			{
				CLR_BIT(MCUCR_REG,2) ;
				CLR_BIT(MCUCR_REG,3) ;
			}
			else if (copy_u8sense==ANY_LOGICAL_CHANCH)
			{
				SET_BIT(MCUCR_REG,2) ;
				CLR_BIT(MCUCR_REG,3) ;
			}
			else if (copy_u8sense ==FALLING_EDGE)
			{
				CLR_BIT(MCUCR_REG,2) ;
				SET_BIT(MCUCR_REG,3) ;
			}
			else if (copy_u8sense==RISING_EDGE)
			{
				SET_BIT(MCUCR_REG,2) ;
				SET_BIT(MCUCR_REG,3) ;
			}
			else{
			}
			break ;
		case _INT_2 :
			if (copy_u8sense ==FALLING_EDGE)
			{
				CLR_BIT(MCUCSR_REG,6) ;
			}
			else if (copy_u8sense==RISING_EDGE)
			{
				SET_BIT(MCUCSR_REG,6) ;
			}
			break ;
	}
}

void EXT_voidEnable(u8 copy_u8IntNum) {
	switch (copy_u8IntNum) {
		case _INT_0:
			SET_BIT(GICR_REG,6);
			break;
		case _INT_1:
			SET_BIT(GICR_REG,7);
			break;
		case _INT_2:
			SET_BIT(GICR_REG,5);
			break;
	}
}

void EXT_voidDisable(u8 copy_u8IntNum){
	switch (copy_u8IntNum) {
		case _INT_0:
			CLR_BIT(GICR_REG,6);
			break;
		case _INT_1:
			CLR_BIT(GICR_REG,7);
			break;
		case _INT_2:
			CLR_BIT(GICR_REG,5);
			break;
	}
}

void EXTI_voidSetCallBack(void(*ptr)(void),u8 copy_u8IntNum){
	switch (copy_u8IntNum) {
		case _INT_0:
			INT0_PTR = ptr;
			break;
		case _INT_1:
			INT1_PTR = ptr;
			break;
		case _INT_2:
			INT2_PTR = ptr;
			break;
	}
}

void __vector_1(void)__attribute__((signal));
void __vector_1(void){
	INT0_PTR() ;
}

void __vector_2(void)__attribute__((signal));
void __vector_2(void){
	INT1_PTR() ;
}

void __vector_3(void)__attribute__((signal));
void __vector_3(void){
	INT2_PTR() ;
}
