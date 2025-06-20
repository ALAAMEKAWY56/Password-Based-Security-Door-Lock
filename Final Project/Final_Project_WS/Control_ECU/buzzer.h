/**********************************************************************************************************
 * [FILE NAME]		:			buzzer.h											                      *
 * [DESCRIPTION]	:			Header file for buzzer_driver										      *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

/************************************Header Files used*********************************************/
#include "std_types.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define BUZZER_PORT_ID  PORTA_ID
#define BUZZER_PIN_ID   PIN0_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*[FUNCTION NAME]	: Buzzer_init
 *[DESCRIPTION]		: Setup the direction for the buzzer pin as output pin through the GPIO driver.
 *		              turn off buzzer through GPIO
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Buzzer_init(void);

/*[FUNCTION NAME]	: Buzzer_on
 *[DESCRIPTION]		: Function to enable the Buzzer through the GPIO.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Buzzer_on(void);

/*[FUNCTION NAME]	: Buzzer_off
 *[DESCRIPTION]		: Function to disable the Buzzer through the GPIO.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
