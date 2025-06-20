/**********************************************************************************************************
 * [FILE NAME]		:			buzzer.c											                      *
 * [DESCRIPTION]	:			Source file for buzzer_driver										      *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

/************************************Header Files used*********************************************/
#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*[FUNCTION NAME]	: Buzzer_init
 *[DESCRIPTION]		: Setup the direction for the buzzer pin as output pin through the GPIO driver.
 *		              turn off buzzer through GPIO
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Buzzer_init(void){
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

/*[FUNCTION NAME]	: Buzzer_on
 *[DESCRIPTION]		: Function to enable the Buzzer through the GPIO.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

/*[FUNCTION NAME]	: Buzzer_off
 *[DESCRIPTION]		: Function to disable the Buzzer through the GPIO.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}
