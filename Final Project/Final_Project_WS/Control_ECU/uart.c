/**********************************************************************************************************
 * [FILE NAME]		:			uart.h												                      *
 * [DESCRIPTION]	:			Source file for the UART AVR driver									      *
 * [DATE CREATED]	: 			oct 17, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

/************************************Header Files used*****************************************************/
#include "common_macros.h"
#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
/*******************************************************************************
 *                      Functions Definitions                                     *
 *******************************************************************************/

/*[FUNCTION NAME]	: UART_init
 *[DESCRIPTION]		: Functional responsible for Initialize the UART device by:
 *                    1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 *                    2. Enable the UART.
 *                    3. Setup the UART baud rate.
 *[ARGUMENTS]		: pointer to Structure of type UART_ConfigType
 *[RETURNS]			: void
 */
void UART_init(const UART_ConfigType * Config_Ptr){

	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 ***********************************************************************/
	UCSRB |= (1<<RXEN) | (1<<TXEN);

	/*configure baud rate
	 * for 9 bit mode */
	if(Config_Ptr->bit_data == BIT_DATA_9_BITS){
		UCSRB |= (1<<UCSZ2);
		/* The URSEL must be one when writing to UCSRC */
		UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	}
	else{
		/*for 5 , 6 , 7 ,8 bit mode */
		UCSRC |= (1<<URSEL);
		UCSRC = (UCSRC & 0xF9) | ((Config_Ptr->bit_data)<<1);
	}

	/* choose parity and stop bit */
	UCSRC = (UCSRC & 0xCF ) | ((Config_Ptr->parity)<<4);
	UCSRC = (UCSRC & 0xF7 ) | ((Config_Ptr->stop_bit)<<3);

	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;

}

/*[FUNCTION NAME]	: UART_sendByte
 *[DESCRIPTION]		: Functional responsible for send byte to another UART device.
 *[ARGUMENTS]		: uint8 data
 *[RETURNS]			: void
 */
void UART_sendByte(const uint8 data){

	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data;
}

/*[FUNCTION NAME]	: UART_sendByte
 *[DESCRIPTION]		: Functional responsible for receive byte from another UART device.
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 UART_recieveByte(){
	while(BIT_IS_CLEAR(UCSRA,RXCIE));
	return UDR;
}

/*[FUNCTION NAME]	: UART_sendString
 *[DESCRIPTION]		: Send the required string through UART to the other UART device.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void UART_sendString(const uint8 *Str){
	uint8 i =0;
	while(Str[i] != '\0'){
		UART_sendByte(Str[i]);
		i++;
	}
}

/*[FUNCTION NAME]	: UART_sendString
 *[DESCRIPTION]		: Receive the required string until the '#' symbol through UART from the other UART device.
 *[ARGUMENTS]		: uint8 pointer to string
 *[RETURNS]			: void
 */
void UART_recieveString(uint8 *Str){
	uint8 i =0;
	Str[i]= UART_recieveByte();
	while(Str[i] != '#'){
		i++;
		Str[i]= UART_recieveByte();
	}
	Str[i] = '\0';
}
