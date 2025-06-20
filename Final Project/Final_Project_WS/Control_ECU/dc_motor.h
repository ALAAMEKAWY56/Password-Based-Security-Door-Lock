/**********************************************************************************************************
 * [FILE NAME]		:			dc_motor.h												                  *
 * [DESCRIPTION]	:			Header file for the AVR dc_motor driver									  *
 * [DATE CREATED]	: 			Sep 9, 2023																  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

/************************************Header Files used*********************************************/
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define  DC_MOTOR_OUTPUT0_PORTID     PORTB_ID
#define  DC_MOTOR_OUTPUT0_PINID      PIN0_ID

#define  DC_MOTOR_OUTPUT1_PORTID     PORTB_ID
#define  DC_MOTOR_OUTPUT1_PINID      PIN1_ID
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	STOP , CW , ACW
}DcMotor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*[FUNCTION NAME]	: DcMotor_Init
 *[DESCRIPTION]		: The Function responsible for setup the direction for the two
 *                    motor pins through the GPIO driver.
 *                    Stop at the DC-Motor at the beginning through the GPIO driver.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void DcMotor_Init(void);

/*[FUNCTION NAME]	: DcMotor_Rotate
 *[DESCRIPTION]		: The function responsible for rotate the DC Motor CW/ or A-CW or
 *                    stop the motor based on the state input state value.
 *                    Send the required duty cycle to the PWM driver based on the  required speed value.
 *                    Stop at the DC-Motor at the beginning through the GPIO driver.
 *[ARGUMENTS]		: The required DC Motor state and required motor speed
 *[RETURNS]			: void
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* DC_MOTOR_H_ */
