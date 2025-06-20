/**********************************************************************************************************
 * [FILE NAME]		:			dc_motor.c											                      *
 * [DESCRIPTION]	:			Source file for the AVR dc_motor driver									  *
 * [DATE CREATED]	: 			Sep 9, 2023																  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/

/************************************Header Files used*********************************************/
#include "dc_motor.h"
#include "pwm.h"
#include "gpio.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*[FUNCTION NAME]	: DcMotor_Init
 *[DESCRIPTION]		: The Function responsible for setup the direction for the two
 *                    motor pins through the GPIO driver.
 *                    Stop at the DC-Motor at the beginning through the GPIO driver.
 *[ARGUMENTS]		: void
 *[RETURNS]			: void
 */
void DcMotor_Init(void){

	/*Set PB0 and PB1 as output pins*/
	GPIO_setupPinDirection(DC_MOTOR_OUTPUT0_PORTID,DC_MOTOR_OUTPUT0_PINID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_OUTPUT1_PORTID,DC_MOTOR_OUTPUT1_PINID,PIN_OUTPUT);

	/*Set intial value for output pins as motor off*/
	GPIO_writePin(DC_MOTOR_OUTPUT0_PORTID,DC_MOTOR_OUTPUT0_PINID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_OUTPUT1_PORTID,DC_MOTOR_OUTPUT1_PINID,LOGIC_LOW);
}

/*[FUNCTION NAME]	: DcMotor_Rotate
 *[DESCRIPTION]		: The function responsible for rotate the DC Motor CW/ or A-CW or
 *                    stop the motor based on the state input state value.
 *                    Send the required duty cycle to the PWM driver based on the  required speed value.
 *                    Stop at the DC-Motor at the beginning through the GPIO driver.
 *[ARGUMENTS]		: The required DC Motor state and required motor speed
 *[RETURNS]			: void
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	if(state == STOP){
		GPIO_writePin(DC_MOTOR_OUTPUT0_PORTID,DC_MOTOR_OUTPUT0_PINID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OUTPUT1_PORTID,DC_MOTOR_OUTPUT1_PINID,LOGIC_LOW);
	}
	else if(state == CW){
		GPIO_writePin(DC_MOTOR_OUTPUT0_PORTID,DC_MOTOR_OUTPUT0_PINID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_OUTPUT1_PORTID,DC_MOTOR_OUTPUT1_PINID,LOGIC_HIGH);
	}
	else if(state == ACW){
		GPIO_writePin(DC_MOTOR_OUTPUT0_PORTID,DC_MOTOR_OUTPUT0_PINID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_OUTPUT1_PORTID,DC_MOTOR_OUTPUT1_PINID,LOGIC_LOW);
	}

	PWM_Timer0_Start(speed);
}

