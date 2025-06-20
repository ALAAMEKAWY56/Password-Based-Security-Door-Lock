/**********************************************************************************************************
 * [FILE NAME]		:	pwm.h									                                          *
 * [DESCRIPTION]	:	Header file for AVR PWM timer mode  driver								          *
 * [DATE CREATED]	: 	OCT 9, 2023																          *
 * [AURTHOR]		: 	Alaa Mekawi															              *
 *********************************************************************************************************/
#ifndef PWM_H_
#define PWM_H_

/************************************Header Files used*****************************************************/
#include "std_types.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*[FUNCTION NAME]	: PWM_Timer0_Start
 *[DESCRIPTION]		: The function responsible for trigger the Timer0 with the PWM Mode.
 *[ARGUMENTS]		: The required duty cycle percentage of the generated PWM signal.
 *[RETURNS]			: void
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
