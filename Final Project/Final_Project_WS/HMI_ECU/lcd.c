/**********************************************************************************************************
 * [FILE NAME]		:			lcd.h												                      *
 * [DESCRIPTION]	:			source file for the AVR lcd_driver										  *
 * [DATE CREATED]	: 			Sep 30, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

/************************************Header Files used*********************************************/
#include "gpio.h"
#include "lcd.h"
#include <util/delay.h>
#include "common_macros.h" /* For GET_BIT Macro */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*[FUNCTION NAME]	: LCD_init
 *[DESCRIPTION]		: Initialize the LCD
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void LCD_init(void){

	/*RS and enable is o/p */
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

	_delay_ms(20);
#if(LCD_DATA_BITS_MODE == 4)
	/*Configure 4 pins in data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);

	/*Send for 4 bit initialization of lcd*/
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 8)
	/*set data port direction o/p*/
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

	/*2 lines and 8 bit*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif

	/*cursor off*/
	LCD_sendCommand(LCD_CURSOR_OFF);

	/*clear screen*/
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}
/*[FUNCTION NAME]	: LCD_sendCommand
 *[DESCRIPTION]		: Send the required command to the screen
 *[ARGUMENTS]		: uint8 command
 *[RETURNS]			: void
 */
void LCD_sendCommand(uint8 command){

	/* RS = 0 */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

	/* Enable = 1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8)
	/* send command */
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	_delay_ms(1);

	/* Enable = 0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#endif

}
/*[FUNCTION NAME]	: LCD_displayCharacter
 *[DESCRIPTION]		: Display the required character on the screen
 *[ARGUMENTS]		: uint8 Data
 *[RETURNS]			: void
 */
void LCD_displayCharacter(uint8 data){
	/* RS = 0 */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

	/* Enable = 1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif (LCD_DATA_BITS_MODE == 8)
	/* send command */
	GPIO_writePort(LCD_DATA_PORT_ID, data);
	_delay_ms(1);

	/* Enable = 0 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#endif

}
/*[FUNCTION NAME]	: LCD_displayString
 *[DESCRIPTION]		: Display the required string on the screen
 *[ARGUMENTS]		: pointer to char 'string'
 *[RETURNS]			: void
 */
void LCD_displayString(const char *str){
	uint8 i = 0;
	while(str[i] != '\0'){
		LCD_displayCharacter(str[i]);
		i++;
	}
}
/*[FUNCTION NAME]	: LCD_moveCursor
 *[DESCRIPTION]		: Move the cursor to a specified row and column index on the screen
 *[ARGUMENTS]		: uint8(row,col)
 *[RETURNS]			: void
 */
void LCD_moveCursor(uint8 row, uint8 col){
	uint8 address;
	switch(row){
	case 0:
		address = col;
		break;
	case 1:
		address = col + 0x40;
		break;
	case 2:
		address = col + 0x10;
		break;
	case 3:
		address = col + 0x50;
		break;
	}
	LCD_sendCommand(address | LCD_SET_CURSOR_LOCATION);
}

/*[FUNCTION NAME]	: LCD_displayStringRowColumn
 *[DESCRIPTION]		: Display the required string in a specified row and column index on the screen
 *[ARGUMENTS]		: uint8(row,col) and pointer to string
 *[RETURNS]			: void
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str){
	LCD_moveCursor(row,col);
	LCD_displayString(str);

}

/*[FUNCTION NAME]	: LCD_integerToString
 *[DESCRIPTION]		: Display the required decimal value on the screen
 *[ARGUMENTS]		: int data
 *[RETURNS]			: void
 */
void LCD_integerToString(int data){
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}

/*[FUNCTION NAME]	: LCD_clearScreen
 *[DESCRIPTION]		: Send the clear screen command
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void LCD_clearScreen(void)
{
	/* Send clear display command */
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}

