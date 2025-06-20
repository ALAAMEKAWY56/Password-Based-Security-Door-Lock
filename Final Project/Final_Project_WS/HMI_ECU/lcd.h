/**********************************************************************************************************
 * [FILE NAME]		:			lcd.h												                      *
 * [DESCRIPTION]	:			Header file for the AVR lcd_driver										  *
 * [DATE CREATED]	: 			Sep 30, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
#ifndef LCD_H_
#define LCD_H_

/************************************Header Files used*****************************************************/
#include "std_types.h"

/*LCD Data bits mode configuration*/
#define LCD_DATA_BITS_MODE 8

#if ((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif
/************************************Definitions*****************************************************/
#define LCD_RS_PORT_ID        PORTA_ID
#define LCD_RS_PIN_ID         PIN0_ID

#define LCD_E_PORT_ID         PORTA_ID
#define LCD_E_PIN_ID          PIN1_ID

#define LCD_DATA_PORT_ID      PORTC_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID        PIN3_ID
#define LCD_DB5_PIN_ID        PIN4_ID
#define LCD_DB6_PIN_ID        PIN5_ID
#define LCD_DB7_PIN_ID        PIN6_ID

#endif

/************************************LCD Commands*****************************************************/
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*****************************************Functions prototypes**********************************************/
/*[FUNCTION NAME]	: LCD_init
 *[DESCRIPTION]		: Initialize the LCD
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void LCD_init(void);

/*[FUNCTION NAME]	: LCD_sendCommand
 *[DESCRIPTION]		: Send the required command to the screen
 *[ARGUMENTS]		: uint8 command
 *[RETURNS]			: void
 */
void LCD_sendCommand(uint8 command);

/*[FUNCTION NAME]	: LCD_displayCharacter
 *[DESCRIPTION]		: Display the required character on the screen
 *[ARGUMENTS]		: uint8 Data
 *[RETURNS]			: void
 */
void LCD_displayCharacter(uint8 Data);

/*[FUNCTION NAME]	: LCD_displayString
 *[DESCRIPTION]		: Display the required string on the screen
 *[ARGUMENTS]		: pointer to char 'string'
 *[RETURNS]			: void
 */
void LCD_displayString(const char *str);

/*[FUNCTION NAME]	: LCD_moveCursor
 *[DESCRIPTION]		: Move the cursor to a specified row and column index on the screen
 *[ARGUMENTS]		: uint8(row,col)
 *[RETURNS]			: void
 */
void LCD_moveCursor(uint8 row, uint8 col);

/*[FUNCTION NAME]	: LCD_displayStringRowColumn
 *[DESCRIPTION]		: Display the required string in a specified row and column index on the screen
 *[ARGUMENTS]		: uint8(row,col) and pointer to string
 *[RETURNS]			: void
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str);

/*[FUNCTION NAME]	: LCD_integerToString
 *[DESCRIPTION]		: Display the required decimal value on the screen
 *[ARGUMENTS]		: int data
 *[RETURNS]			: void
 */
void LCD_integerToString(int data);

/*[FUNCTION NAME]	: LCD_clearScreen
 *[DESCRIPTION]		: Send the clear screen command
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
