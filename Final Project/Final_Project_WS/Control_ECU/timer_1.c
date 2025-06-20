/**********************************************************************************************************
 * [FILE NAME]		:			timer_1.h								                                  *
 * [DESCRIPTION]	:			Header file for the Timer_1 AVR driver									  *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
/************************************Header Files used*****************************************************/
#include "timer_1.h"
#include "common_macros.h"
#include "gpio.h"
#include <avr/io.h>          /* To use Timer1 Registers */
#include <avr/interrupt.h>  /* For Timer1 ISR */
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR){
		/*call back function in main apllictaion after edge deteced*/
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR){
		/*call back function in main apllictaion after edge deteced*/
		(*g_callBackPtr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/
/*[FUNCTION NAME]	: Timer1_init
 *[DESCRIPTION]		: Function to initialize the Timer driver.
 *[ARGUMENTS]		: pointer to Structure of type Timer1_ConfigType
 *[RETURNS]			: void
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	/*first two bits is common in two modes 00 for both*/
	TCCR1A = (1 << FOC1A) | (Config_Ptr->mode & 3);
	if (Config_Ptr->mode == TIMER1_COMPARE_MODE_4) {
		/* Set the Compare value to value in Configuration */
		OCR1A = Config_Ptr->compare_value;

		/* Enable Timer1 Compare A Interrupt */
		TIMSK |= (1 << OCIE1A);
		TCCR1B = (Config_Ptr->prescaler) | ((Config_Ptr->mode >> 2) << 3);
	}
	if (Config_Ptr->mode == TIMER1_Normal_MODE) {
		/*Timer_ 1 Overflow  Interrupt Enable*/
		TIMSK |= (1<<TOIE1);
		/*set prescaler chosen in Configuration*/
		TCCR1B = (Config_Ptr->prescaler);
	}
	TCNT1 = Config_Ptr->initial_value;
}

/*[FUNCTION NAME]	: Timer1_deInit
 *[DESCRIPTION]		: Function to disable the Timer1.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Timer1_deInit(void){
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
}

/*[FUNCTION NAME]	: Timer1_setCallBack
 *[DESCRIPTION]		: Function to set the Call Back function address.
 *[ARGUMENTS]		: pointer to Call Back function.
 *[RETURNS]			: void
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = a_ptr;
}
