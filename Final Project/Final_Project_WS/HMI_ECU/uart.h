/**********************************************************************************************************
 * [FILE NAME]		:			uart.h												                      *
 * [DESCRIPTION]	:			Header file for the UART AVR driver									      *
 * [DATE CREATED]	: 			oct 17, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
#ifndef UART_H_
#define UART_H_

/************************************Header Files used*****************************************************/
#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	BIT_DATA_5_BITS ,        /* 0 */
	BIT_DATA_6_BITS ,       /* 1 */
	BIT_DATA_7_BITS ,      /* 2 */
	BIT_DATA_8_BITS ,     /* 3 */
	BIT_DATA_9_BITS = 7  /* 7 */
}UART_BitData;
typedef enum{
	 DISABLED    ,      /* 0 */
	 RESERVED    ,     /* 1 */
	 EVEN_PARITY ,    /* 2 */
	 ODD_PARITY      /* 3 */
}UART_Parity;

typedef enum{
	 STOP_BIT_1    ,      /* 0 */
	 STOP_BIT_2          /* 1 */
}UART_StopBit;

typedef enum{
	 BAUD_RATE_10     = 10     ,
	 BAUD_RATE_300    = 300    ,
	 BAUD_RATE_600    = 600    ,
	 BAUD_RATE_1200   = 1200   ,
	 BAUD_RATE_2400   = 2400   ,
	 BAUD_RATE_4800   = 4800   ,
	 BAUD_RATE_9600   = 9600   ,
	 BAUD_RATE_14400  = 14400  ,
	 BAUD_RATE_19200  = 19200  ,
	 BAUD_RATE_38400  = 38400  ,
	 BAUD_RATE_57600  = 57600  ,
	 BAUD_RATE_115200 = 115200 ,
	 BAUD_RATE_128000 = 128000 ,
	 BAUD_RATE_256000 = 256000
}UART_BaudRate;

typedef struct{
 UART_BitData bit_data;
 UART_Parity parity;
 UART_StopBit stop_bit;
 UART_BaudRate baud_rate;
}UART_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*[FUNCTION NAME]	: UART_init
 *[DESCRIPTION]		: Functional responsible for Initialize the UART device by:
 *                    1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 *                    2. Enable the UART.
 *                    3. Setup the UART baud rate.
 *[ARGUMENTS]		: pointer to Structure of type UART_ConfigType
 *[RETURNS]			: void
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*[FUNCTION NAME]	: UART_sendByte
 *[DESCRIPTION]		: Functional responsible for send byte to another UART device.
 *[ARGUMENTS]		: uint8 data
 *[RETURNS]			: void
 */
void UART_sendByte(const uint8 data);

/*[FUNCTION NAME]	: UART_sendByte
 *[DESCRIPTION]		: Functional responsible for receive byte from another UART device.
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 UART_recieveByte();

/*[FUNCTION NAME]	: UART_sendString
 *[DESCRIPTION]		: Send the required string through UART to the other UART device.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void UART_sendString(const uint8 *Str);

/*[FUNCTION NAME]	: UART_sendString
 *[DESCRIPTION]		: Receive the required string until the '#' symbol through UART from the other UART device.
 *[ARGUMENTS]		: uint8 pointer to string
 *[RETURNS]			: void
 */
void UART_recieveString(uint8 *Str);


#endif /* UART_H_ */
