 /**********************************************************************************************************
 * [FILE NAME]		:			timer_1.h								                                  *
 * [DESCRIPTION]	:			Header file for the Timer_1 AVR driver									  *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
#ifndef TIMER_1_H_
#define TIMER_1_H_
/************************************Header Files used*****************************************************/
#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	NO_CLOCK_SOURCE        ,         /* 0 */
	TIMER1_PRESCALER_1     ,        /* 1 */
	TIMER1_PRESCALER_8     ,       /* 2 */
	TIMER1_PRESCALER_64    ,      /* 3 */
	TIMER1_PRESCALER_256   ,     /* 4 */
	TIMER1_PRESCALER_1024  ,    /* 5 */
	EXTERNAL_CLOCK_FALLING ,   /* 6 */
	EXTERNAL_CLOCK_RISING     /* 7 */
}Timer1_Prescaler;

typedef enum{
	TIMER1_Normal_MODE           ,         /* 0 */
	TIMER1_COMPARE_MODE_4  =  4  ,        /* 4 */
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; /*it will be used in compare mode only.*/
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*[FUNCTION NAME]	: Timer1_init
 *[DESCRIPTION]		: Function to initialize the Timer driver.
 *[ARGUMENTS]		: pointer to Structure of type Timer1_ConfigType
 *[RETURNS]			: void
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*[FUNCTION NAME]	: Timer1_deInit
 *[DESCRIPTION]		: Function to disable the Timer1.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Timer1_deInit(void);

/*[FUNCTION NAME]	: Timer1_setCallBack
 *[DESCRIPTION]		: Function to set the Call Back function address.
 *[ARGUMENTS]		: pointer to Call Back function.
 *[RETURNS]			: void
 */
void Timer1_setCallBack(void(*a_ptr)(void));
#endif /* TIMER_1_H_ */
