/**********************************************************************************************************
 * [FILE NAME]		:			external_eeprom.h								                          *
 * [DESCRIPTION]	:			Header file for the External EEPROM Memory								  *
 * [DATE CREATED]	: 			Oct 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/************************************Header Files used*********************************************/
#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR    0
#define SUCCESS  1
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*[FUNCTION NAME]	: EEPROM_writeByte
 *[DESCRIPTION]		: send the device address and location address to write Byte from Memory
 *[ARGUMENTS]		: uint16 u16addr,uint8 u8data
 *[RETURNS]			: void
 */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);

/*[FUNCTION NAME]	: EEPROM_writeByte
 *[DESCRIPTION]		: send the device address and location address to Read Byte from Memory
 *[ARGUMENTS]		: uint16 u16addr,uint8 *u8data
 *[RETURNS]			: void
 */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EXTERNAL_EEPROM_H_ */
