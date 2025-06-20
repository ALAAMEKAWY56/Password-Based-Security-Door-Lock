/**********************************************************************************************************
 * [FILE NAME]		:			twi.c								                                      *
 * [DESCRIPTION]	:			Source file for the TWI(I2C) AVR driver									  *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
/************************************Header Files used*********************************************/
#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*[FUNCTION NAME]	: TWI_init
 *[DESCRIPTION]		: Initialize the I2C driver as required.
 *[ARGUMENTS]		: const TWI_ConfigType * Config_Ptr
 *[RETURNS]			: void
 */
void TWI_init(const TWI_ConfigType * Config_Ptr){

	/* Bit Rate from configuration using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	/*TWBR = ((uint8)(uint16)((F_CPU/(Config_Ptr->bit_rate))- 16)* 2);*/
	TWBR = ((uint8) ((uint16)(F_CPU/((Config_Ptr->bit_rate)*2)))-8);
	TWSR = 0x00;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	   General Call Recognition: Off */
	/* address from configuration*/
	TWAR = (Config_Ptr->address);

	/* enable TWI */
	TWCR = (1<<TWEN);
}

/*[FUNCTION NAME]	: TWI_start
 *[DESCRIPTION]		: send start bit to start Frame communication
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void TWI_start(void){

	/* at beginning of each function clear flag by writing logical one
	 * enable I2C
	 * Set the start bit*/
	TWCR = (1<<TWEN) | (1<<TWSTA) | (1<<TWINT);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*[FUNCTION NAME]	: TWI_stop
 *[DESCRIPTION]		: send stop bit to stop Frame communication
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void TWI_stop(void){

	/* at beginning of each function clear flag by writing logical one
	 * enable I2C
	 * Set the stop bit*/
	TWCR = (1<<TWEN) | (1<<TWSTO) | (1<<TWINT);

	/*No polling as we end the frame no need to wait*/
}

/*[FUNCTION NAME]	: TWI_writeByte
 *[DESCRIPTION]		: send data "Byte" to receiver
 *[ARGUMENTS]		: uint8 data
 *[RETURNS]			: void
 */
void TWI_writeByte(uint8 data){

	/* Put data On TWI data Register */
	TWDR = data;
	/* at beginning of each function clear flag by writing logical one
	 * enable I2C */
	TWCR = (1<<TWEN) | (1<<TWINT);

	/* Wait for TWINT flag set in TWCR Register (data bits is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*[FUNCTION NAME]	: TWI_readByteWithACK
 *[DESCRIPTION]		: Receive data From transmitter with ACK
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 TWI_readByteWithACK(void){

	/* at beginning of each function clear flag by writing logical one
	 * enable I2C
	 * Enable sending ACK after reading or receiving data TWEA=1 */
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);

	/* Wait for TWINT flag set in TWCR Register (data received is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/*Read data*/
	return TWDR;
}

/*[FUNCTION NAME]	: TWI_readByteWithNACK
 *[DESCRIPTION]		: Receive data From transmitter with NACK
 *		              informs transmitter to stop sending data
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 TWI_readByteWithNACK(void){

	/* at beginning of each function clear flag by writing logical one
	 * enable I2C8 */
	TWCR = (1<<TWEN) | (1<<TWINT);

	/* Wait for TWINT flag set in TWCR Register (data received is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/*Read data*/
	return TWDR;

}

/*[FUNCTION NAME]	: TWI_getStatus
 *[DESCRIPTION]		: get five bits that reflect status of the TWI logic
 *		              and two-wire Serial Bus
 *[ARGUMENTS]		: void
 *[RETURNS]			: uint8
 */
uint8 TWI_getStatus(void){
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}
