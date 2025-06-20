/**********************************************************************************************************
 * [FILE NAME]		:			external_eeprom.c								                          *
 * [DESCRIPTION]	:			Source file for the External EEPROM Memory								  *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
/************************************Header Files used*********************************************/
#include "external_eeprom.h"
#include "twi.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*[FUNCTION NAME]	: EEPROM_writeByte
 *[DESCRIPTION]		: send the device address and location address to write Byte from Memory
 *[ARGUMENTS]		: uint16 u16addr,uint8 u8data
 *[RETURNS]			: void
 */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data){
	/*send the start Bit*/
	TWI_start();
	if(TWI_getStatus() != TWI_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)(0xA0) | ((u16addr & 0x700)>>7));
	if(TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16addr));
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* write byte to eeprom */
	TWI_writeByte(u8data);
	if(TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_stop();

	return SUCCESS;
}

/*[FUNCTION NAME]	: EEPROM_writeByte
 *[DESCRIPTION]		: send the device address and location address to Read Byte from Memory
 *[ARGUMENTS]		: uint16 u16addr,uint8 *u8data
 *[RETURNS]			: void
 */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data){
	/* Send the Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write) */
	TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
	if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
		return ERROR;

	/* Send the required memory location address */
	TWI_writeByte((uint8)(u16addr));
	if (TWI_getStatus() != TWI_MT_DATA_ACK)
		return ERROR;

	/* Send the Repeated Start Bit */
	TWI_start();
	if (TWI_getStatus() != TWI_REP_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (Read) */
	TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
	if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
		return ERROR;

	/* Read Byte from Memory without send ACK */
	*u8data = TWI_readByteWithNACK();
	if (TWI_getStatus() != TWI_MR_DATA_NACK)
		return ERROR;

	/* Send the Stop Bit */
	TWI_stop();

	return SUCCESS;
}

