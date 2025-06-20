/**********************************************************************************************************
 * [FILE NAME]		:			GPIO.h												                      *
 * [DESCRIPTION]	:			Header file for the AVR GPIO_driver										  *
 * [DATE CREATED]	: 			Sep 3, 2023																  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_

/************************************Header Files used*********************************************/
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>

/************************************Definitions*********************************************/
#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*****************************************Types definitions **********************************************/

/*[FUNCTION NAME]	: GPIO_PinDirectionType
 *[DESCRIPTION]		: Set Pin direction type
 */
typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

/*[FUNCTION NAME]	: GPIO_PortDirectionType
 *[DESCRIPTION]		: Set Port direction type
 */
typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;


/*****************************************Functions prototypes**********************************************/
/*[FUNCTION NAME]	: GPIO_setupPinDirection
 *[DESCRIPTION]		: Setup the direction of the required pin input/output,
 *             		  If the input port number or pin number are not correct, The function will not handle the request.
 *[ARGUMENTS]		: unit8 (port_num, pin_num) ,
 *		              GPIO_PinDirectionType Enum(direction)
 *[RETURNS]			: void
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*[FUNCTION NAME]	: GPIO_writePin
 *[DESCRIPTION]		: Write the value Logic High or Logic Low on the required pin.
 *                    If the input port number or pin number are not correct, The function will not handle the request.
 *                    If the pin is input, this function will enable/disable the internal pull-up resistor.
 *[ARGUMENTS]		: unit8 (port_num, pin_num, value)
 *[RETURNS]			: void
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*[FUNCTION NAME]	: GPIO_readPin
 *[DESCRIPTION]		: Read and return the value for the required pin, it should be Logic High or Logic Low.
 *                    If the input port number or pin number are not correct,
 *                    The function will return Logic Low.
 *[ARGUMENTS]		: unit8 (port_num, pin_num)
 *[RETURNS]			: unit8  "unsigned char"
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*[FUNCTION NAME]	: GPIO_setupPortDirection
 *[DESCRIPTION]		: Setup the direction of the required port all pins input/output.
 *                    If the direction value is PORT_INPUT all pins in this port should be input pins.
 *                    If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 *                    If the input port number is not correct, The function will not handle the request.
 *[ARGUMENTS]		: unit8 (port_num, direction)
 *[RETURNS]			: void
 */
void GPIO_setupPortDirection(uint8 port_num, uint8 direction);

/*[FUNCTION NAME]	: GPIO_writePort
 *[DESCRIPTION]		: Write the value on the required port.
 *                    If any pin in the port is output pin the value will be written.
 *                    If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 *                    If the input port number is not correct, The function will not handle the request.
 *[ARGUMENTS]		: unit8 (port_num, value)
 *[RETURNS]			: void
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*[FUNCTION NAME]	: GPIO_readPort
 *[DESCRIPTION]		: Read and return the value of the required port.
 *                    If the input port number is not correct, The function will return ZERO value.
 *[ARGUMENTS]		: unit8 (port_num)
 *[RETURNS]			: unit8  "unsigned char"
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_H_ */
