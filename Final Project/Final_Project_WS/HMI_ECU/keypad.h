/**********************************************************************************************************
 * [FILE NAME]		:			keypad.h									                              *
 * [DESCRIPTION]	:			Header file for the Keypad driver									      *
 * [DATE CREATED]	: 			Sep 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_ROWS 4
#define KEYPAD_NUM_COLS 4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID         PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID    PIN0_ID

#define KEYPAD_COL_PORT_ID         PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID    PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED      LOGIC_LOW
#define KEYPAD_BUTTON_RELESED      LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*[FUNCTION NAME]	: KEYPAD_getPressedKey
 *[DESCRIPTION]		: Get the Keypad pressed button
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
