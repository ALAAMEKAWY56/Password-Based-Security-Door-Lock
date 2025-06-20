/**********************************************************************************************************
 * [FILE NAME]		:			GPIO.c											                          *
 * [DESCRIPTION]	:			Source file for the AVR GPIO_driver										  *
 * [DATE CREATED]	: 			Sep 3, 2023																  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

/************************************Header Files used*********************************************/
#include "gpio.h"
#include <avr/io.h>
/************************************Functions Definitions*********************************************/
/*[FUNCTION NAME]	: GPIO_setupPinDirection
 *[DESCRIPTION]		: Setup the direction of the required pin input/output,
 *             		  If the input port number or pin number are not correct, The function will not handle the request.
 *[ARGUMENTS]		: unit8 (port_num, pin_num) ,
 *		              GPIO_PinDirectionType Enum(direction)
 *[RETURNS]			: void
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction){

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		//switch on port number
		switch(port_num){

		//If pin is input clear DDRA with chosen pin number and if not set Pin in DDRA
		case PORTA_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRA,pin_num);
			}
			else{
				SET_BIT(DDRA,pin_num);
			}
			break;

			//If pin is input clear DDRB with chosen pin number and if not set Pin in DDRB
		case PORTB_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRB,pin_num);
			}
			else{
				SET_BIT(DDRB,pin_num);
			}
			break;

			//If pin is input clear DDRC with chosen pin number and if not set Pin in DDRC
		case PORTC_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRC,pin_num);
			}
			else{
				SET_BIT(DDRC,pin_num);
			}
			break;

			//If pin is input clear DDRD with chosen pin number and if not set Pin in DDRD
		case PORTD_ID:
			if(direction == PIN_INPUT){
				CLEAR_BIT(DDRD,pin_num);
			}
			else{
				SET_BIT(DDRD,pin_num);
			}

			break;
		}

	}
}


/*[FUNCTION NAME]	: GPIO_writePin
 *[DESCRIPTION]		: Write the value Logic High or Logic Low on the required pin.
 *                    If the input port number or pin number are not correct, The function will not handle the request.
 *                    If the pin is input, this function will enable/disable the internal pull-up resistor.
 *[ARGUMENTS]		: unit8 (port_num, pin_num, value)
 *[RETURNS]			: void
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value){

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		//switch on port number
		switch(port_num){

		//If value required is logic low clear chosen bit in PORTA and if not set bit in PORTA
		case PORTA_ID:
			if(value == LOGIC_LOW){
				CLEAR_BIT(PORTA,pin_num);
			}
			else{
				SET_BIT(PORTA,pin_num);
			}
			break;

			//If value required is logic low clear chosen bit in PORTB and if not set bit in PORTB
		case PORTB_ID:
			if(value == LOGIC_LOW){
				CLEAR_BIT(PORTB,pin_num);
			}
			else{
				SET_BIT(PORTB,pin_num);
			}
			break;

			//If value required is logic low clear chosen bit in PORTC and if not set bit in PORTC
		case PORTC_ID:
			if(value == LOGIC_LOW){
				CLEAR_BIT(PORTC,pin_num);
			}
			else{
				SET_BIT(PORTC,pin_num);
			}
			break;

			//If value required is logic low clear chosen bit in PORTD and if not set bit in PORTD
		case PORTD_ID:
			if(value == LOGIC_LOW){
				CLEAR_BIT(PORTD,pin_num);
			}
			else{
				SET_BIT(PORTD,pin_num);
			}

			break;

		}
	}
}


/*[FUNCTION NAME]	: GPIO_readPin
 *[DESCRIPTION]		: Read and return the value for the required pin, it should be Logic High or Logic Low.
 *                    If the input port number or pin number are not correct,
 *                    The function will return Logic Low.
 *[ARGUMENTS]		: unit8 (port_num, pin_num)
 *[RETURNS]			: unit8  "unsigned char"
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num){

	//set variable with logic low value (0)
	uint8 pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		//switch on port number
		switch(port_num){

		//check on chosen pin number in PORTA ,If high return pin value = 1 else pin value = 0
		case PORTA_ID:
			if(BIT_IS_SET(PINA,pin_num)){
				pin_value = LOGIC_HIGH;
			}
			else{
				pin_value = LOGIC_LOW;
			}
			break;

			//check on chosen pin number in PORTB ,If high return pin value = 1 else pin value = 0
		case PORTB_ID:
			if(BIT_IS_SET(PINB,pin_num)){
				pin_value = LOGIC_HIGH;
			}
			else{
				pin_value = LOGIC_LOW;
			}
			break;

			//check on chosen pin number in PORTC ,If high return pin value = 1 else pin value = 0
		case PORTC_ID:
			if(BIT_IS_SET(PINC,pin_num)){
				pin_value = LOGIC_HIGH;
			}
			else{
				pin_value = LOGIC_LOW;
			}
			break;

			//check on chosen pin number in PORTD ,If high return pin value = 1 else pin value = 0
		case PORTD_ID:
			if(BIT_IS_SET(PIND,pin_num)){
				pin_value = LOGIC_HIGH;
			}
			else{
				pin_value = LOGIC_LOW;
			}

			break;
		}
	}
	return pin_value;
}

/*[FUNCTION NAME]	: GPIO_setupPortDirection
 *[DESCRIPTION]		: Setup the direction of the required port all pins input/output.
 *                    If the direction value is PORT_INPUT all pins in this port should be input pins.
 *                    If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 *                    If the input port number is not correct, The function will not handle the request.
 *[ARGUMENTS]		: unit8 (port_num, direction)
 *[RETURNS]			: void
 */
void GPIO_setupPortDirection(uint8 port_num, uint8 direction){

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		//switch on port number
		switch(port_num){

		//SET direction of PORTA directly from REG: DDRA
		case PORTA_ID:
			DDRA = direction;
			break;

			//SET direction of PORTB directly from REG: DDRB
		case PORTB_ID:
			DDRB = direction;
			break;

			//SET direction of PORTC directly from REG: DDRC
		case PORTC_ID:
			DDRC = direction;
			break;

			//SET direction of PORTD directly from REG: DDRD
		case PORTD_ID:
			DDRD = direction;
			break;

		}
	}
}


/*[FUNCTION NAME]	: GPIO_writePort
 *[DESCRIPTION]		: Write the value on the required port.
 *                    If any pin in the port is output pin the value will be written.
 *                    If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 *                    If the input port number is not correct, The function will not handle the request.
 *[ARGUMENTS]		: unit8 (port_num, value)
 *[RETURNS]			: void
 */
void GPIO_writePort(uint8 port_num, uint8 value){

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		//switch on port number
		switch(port_num){

		//Write value in PORTA
		case PORTA_ID:
			PORTA = value;
			break;

			//Write value in PORTB
		case PORTB_ID:
			PORTB = value;
			break;

			//Write value in PORTC
		case PORTC_ID:
			PORTC = value;
			break;

			//Write value in PORTD
		case PORTD_ID:
			PORTD = value;
			break;

		}
	}

}


/*[FUNCTION NAME]	: GPIO_readPort
 *[DESCRIPTION]		: Read and return the value of the required port.
 *                    If the input port number is not correct, The function will return ZERO value.
 *[ARGUMENTS]		: unit8 (port_num)
 *[RETURNS]			: unit8  "unsigned char"
 */
uint8 GPIO_readPort(uint8 port_num){
	//set variable with logic low value (0)
	uint8 port_value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{

		//switch on port number
		switch(port_num){

		//check on PORTA value from PINA REG.
		case PORTA_ID:
			port_value = PINA;
			break;

			//check on PORTB value from PINB REG.
		case PORTB_ID:
			port_value = PINB;
			break;

			//check on PORTC value from PINC REG.
		case PORTC_ID:
			port_value = PINC;
			break;

			//check on PORTD value from PIND REG.
		case PORTD_ID:
			port_value = PIND;
			break;
		}
	}
	return port_value;

}
