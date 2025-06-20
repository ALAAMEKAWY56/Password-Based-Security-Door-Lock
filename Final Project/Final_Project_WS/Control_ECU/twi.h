/**********************************************************************************************************
 * [FILE NAME]		:			twi.h								                                      *
 * [DESCRIPTION]	:			Header file for the TWI(I2C) AVR driver									  *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

#ifndef TWI_H_
#define TWI_H_

/************************************Header Files used*********************************************/
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef uint8 TWI_Address;

typedef enum{
	BIT_RATE_NORMAL_MODE     = 100000  ,
	BIT_RATE_FAST_MODE       = 400000  ,
	BIT_RATE_FAST_MODE_PLUS  = 1000000 ,
	BIT_RATE_HIGH_SPEED_MODE = 3400000 ,
}TWI_BaudRate;

typedef struct{
 TWI_Address address;
 TWI_BaudRate bit_rate;
}TWI_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*[FUNCTION NAME]	: TWI_init
 *[DESCRIPTION]		: Initialize the I2C driver as required.
 *[ARGUMENTS]		: pointer to Structure of type TWI_ConfigType
 *[RETURNS]			: void
 */
void TWI_init(const TWI_ConfigType * Config_Ptr);

/*[FUNCTION NAME]	: TWI_start
 *[DESCRIPTION]		: send start bit to start Frame communication
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void TWI_start(void);

/*[FUNCTION NAME]	: TWI_stop
 *[DESCRIPTION]		: send stop bit to stop Frame communication
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void TWI_stop(void);

/*[FUNCTION NAME]	: TWI_writeByte
 *[DESCRIPTION]		: send data "Byte" to receiver
 *[ARGUMENTS]		: uint8 data
 *[RETURNS]			: void
 */
void TWI_writeByte(uint8 data);

/*[FUNCTION NAME]	: TWI_readByteWithACK
 *[DESCRIPTION]		: Receive data From transmitter with ACK
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 TWI_readByteWithACK(void);

/*[FUNCTION NAME]	: TWI_readByteWithNACK
 *[DESCRIPTION]		: Receive data From transmitter with NACK
 *		              informs transmitter to stop sending data
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 TWI_readByteWithNACK(void);

/*[FUNCTION NAME]	: TWI_getStatus
 *[DESCRIPTION]		: get five bits that reflect status of the TWI logic
 *		              and two-wire Serial Bus
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 TWI_getStatus(void);
#endif /* TWI_H_ */
