/**********************************************************************************************************
 * [FILE NAME]		:			Control_ECU.c											                  *
 * [DESCRIPTION]	:			Source file for the Contraol_ECU main Application						  *
 * [DATE CREATED]	: 			OCT 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
/************************************Header Files used*****************************************************/
#include "timer_1.h"
#include "uart.h"
#include "dc_motor.h"
#include "external_eeprom.h"
#include "twi.h"
#include "buzzer.h"
#include <util/delay.h>
#include <avr/io.h>

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ENTER                     61    /* = */
#define OPEN_DOOR                 43   /* + */
#define CHANGE_PASS               45  /* - */
#define FIRST_PASSWORD_RECIVED    0x3F
#define SECOND_PASSWORD_RECIVED   0x4F
#define PASSWORD_SIZE             5
#define MC1_READY                 0x10
#define MC2_READY                 0x13
#define FIRST_PASSWORD_AND_SAVED  0x11
#define SECOND_PASSWORD_AND_SAVED 0x12
#define PASSWORDS_MATCH           1
#define PASSWORDS_UNMATCH         0
#define PASS_EEPROM_ADDRESS       0x20
#define DOOR_IS_UNLOCK            15
#define DOOR_IS_LOCK              15
#define HOLD_MOTOR                3
#define PASS_TRIAL                3
#define WARNING                   60
/*******************************************************************************
 *                             Global Variables                                *
 *******************************************************************************/
uint8 UART_RECEIVED = 0 , state;
uint8 saved_pass_eeprom[PASSWORD_SIZE];
uint8 recived_pass[PASSWORD_SIZE];
uint16 g_ticks = 0;
uint8 i = 0;
uint8 pass_trials = 0;
/*******************************************************************************
 *                      	Functions Prototypes                                *
 *******************************************************************************/
void Set_Password(void);
void Recieve_Passowrd(uint8 *pass,uint8 size);
void EEPROM_savepass(uint8 *pass , uint8 size);
uint8 Motor_function(void);
void Timer1_callback(void);
void Buzzer_function(void);
uint8 compare_password(uint8 *pass_1 , uint8 *pass_2, uint8 size);
/*******************************************************************************
 *                      		Main Function                                  *
 *******************************************************************************/
int main(void){
	/*Enable I-bit*/
	SREG|=(1<<7);

	/*Initialization UART*/
	UART_ConfigType UART_Config ={BIT_DATA_8_BITS,DISABLED,STOP_BIT_1,BAUD_RATE_9600};
	UART_init(&UART_Config);

	/*Initialization The timer with 1 sec for every interrupt*/
	Timer1_ConfigType Timer1_Config ={0,8000,TIMER1_PRESCALER_1024,TIMER1_COMPARE_MODE_4};
	Timer1_init(&Timer1_Config);
	Timer1_setCallBack(Timer1_callback);

	/*Initialization I2C*/
	TWI_ConfigType TWI_Config = {0b00000010,BIT_RATE_FAST_MODE};
	TWI_init(&TWI_Config);

	/*Initialization DC-motor */
	DcMotor_Init();

	/*Initialization Buzzer*/
	Buzzer_init();

	/*don't start program until first MC is ready and sent you verification*/
	while(UART_recieveByte() != MC1_READY);

	/*set password opertion for first time!*/
	Set_Password();

	while(1)
	{

		/*Receive from first MC which key is pressed*/
		UART_RECEIVED = UART_recieveByte();

		/*if received option from HMI_ECU open door then compare passwords*/
		if(UART_RECEIVED == OPEN_DOOR)
		{
			/*send verification first*/
			UART_sendByte(MC2_READY);

			/*Receive passwords*/
			Recieve_Passowrd(recived_pass,PASSWORD_SIZE);

			/*Compare with Saved one already passwords*/
			state = compare_password(recived_pass,saved_pass_eeprom,PASSWORD_SIZE);
			if(state == PASSWORDS_MATCH)
			{
				/*return trials to zero again*/
				pass_trials = 0;
				/*process the motor rotation function*/
				UART_sendByte(PASSWORDS_MATCH);
				/*to make sure motor is operating in right direction "for proteus"*/
				while(Motor_function() != 0){}

			}
			/*for passwords unmatched try again you have 3 trials*/
			else if(state == PASSWORDS_UNMATCH)
			{
				/*you have only 3 trials*/
				pass_trials++;
				if(pass_trials == PASS_TRIAL)
				{
					UART_sendByte(WARNING);
					/*process the Buzzer rotation function*/
					Buzzer_function();
					/*reset  your pass_trails to zero*/
					pass_trials = 0;
				}
				else
				{
					UART_sendByte(PASSWORDS_UNMATCH);
				}
			}

		}
		if(UART_RECEIVED == CHANGE_PASS)
		{
			/*send verification first*/
			UART_sendByte(MC2_READY);

			/*Receive passwords*/
			Recieve_Passowrd(recived_pass,PASSWORD_SIZE);

			/*Compare with Saved one already passwords*/
			state = compare_password(recived_pass,saved_pass_eeprom,PASSWORD_SIZE);
			if(state == PASSWORDS_MATCH)
			{
				/*return trials to zero again*/
				pass_trials = 0;
				/*process the motor rotation function*/
				UART_sendByte(PASSWORDS_MATCH);
				Set_Password();

			}
			/*for passwords unmatched try again you have 3 trials*/
			else if(state == PASSWORDS_UNMATCH)
			{
				/*you have only 3 trials*/
				pass_trials++;
				if(pass_trials == PASS_TRIAL)
				{
					UART_sendByte(WARNING);
					/*reset  your pass_trails to zero*/
					Buzzer_function();
					pass_trials = 0;
				}
				else
				{
					UART_sendByte(PASSWORDS_UNMATCH);
				}
			}
		}
	}
}
/*******************************************************************************
 *                      	Functions Definitions                               *
 *******************************************************************************/
void Timer1_callback(void){
	g_ticks++;
}
/*******************************************************************************/
void Set_Password(void){
	uint8 arr_pass_first[PASSWORD_SIZE] , arr_pass_second[PASSWORD_SIZE];
	/*Initial value two pass doesn't match*/
	uint8 pass_state = PASSWORDS_UNMATCH;

	while(pass_state == PASSWORDS_UNMATCH)
	{
		while(UART_recieveByte() != MC1_READY);

		/*receive first password*/
		Recieve_Passowrd(arr_pass_first,PASSWORD_SIZE);

		/*send verification you have received first password*/
		UART_sendByte(FIRST_PASSWORD_RECIVED);
		_delay_ms(50);

		/*receive second password*/
		Recieve_Passowrd(arr_pass_second,PASSWORD_SIZE);

		/*send verification you have received second password*/
		UART_sendByte(SECOND_PASSWORD_RECIVED);

		/*always update your pass state and send it to first MC to display messages on LCD*/
		pass_state = compare_password(arr_pass_first,arr_pass_second,PASSWORD_SIZE);
		UART_sendByte(pass_state);
		/*if two pass matched save in EEPROM*/
		if(pass_state == PASSWORDS_MATCH)
		{
			EEPROM_savepass(arr_pass_first,PASSWORD_SIZE);
			/*Terminate function and end while loop*/
			return;
		}
	}
}
/*******************************************************************************/
void Recieve_Passowrd(uint8 *pass,uint8 size){
	for (uint8 i=0;i<size;i++)
	{
		pass[i]=UART_recieveByte();
		_delay_ms(50);
	}
}
/*******************************************************************************/
uint8 compare_password(uint8 *pass_1 , uint8 *pass_2, uint8 size){
	/*compare two password and return matched or not*/
	uint8 i;
	for(i =0 ;i<size ; i++){
		if(pass_1[i] != pass_2[i]){
			return PASSWORDS_UNMATCH;
		}
	}
	return PASSWORDS_MATCH;
}
/*******************************************************************************/
void EEPROM_savepass(uint8 *pass , uint8 size){
	uint8 i;
	for(i=0 ;i<size; i++){
		EEPROM_writeByte(PASS_EEPROM_ADDRESS+i,pass[i]);
		saved_pass_eeprom[i] = pass[i];
		_delay_ms(10);
	}
}
/*******************************************************************************/
uint8 Motor_function(void){
	/*Opening the door in 15sec*/
	g_ticks=0;
	DcMotor_Rotate(CW,100);
	while (g_ticks < DOOR_IS_UNLOCK);


	/*Holding the door in 3sec*/
	g_ticks=0;
	DcMotor_Rotate(STOP,0);
	while (g_ticks < HOLD_MOTOR);


	/*Closing the door in 15sec*/
	g_ticks=0;
	DcMotor_Rotate(ACW,100);
	while (g_ticks < DOOR_IS_LOCK);


	/*Stop the Motor*/
	DcMotor_Rotate(STOP,0);
	return 0;

}
/*******************************************************************************/
void Buzzer_function(void){
	g_ticks=0;
	/*operate buzzer for 60 sec*/
	Buzzer_on();
	while (g_ticks < WARNING);
	Buzzer_off();
}
/*******************************************************************************/

