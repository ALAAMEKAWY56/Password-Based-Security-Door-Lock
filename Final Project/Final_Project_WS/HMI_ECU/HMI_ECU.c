/**********************************************************************************************************
 * [FILE NAME]		:			HMI_ECU.c											                      *
 * [DESCRIPTION]	:			Source file for the HMI_ECU.c main Application						      *
 * [DATE CREATED]	: 			OCT 26, 2023															  *
 * [AURTHOR]		: 			Alaa Mekawi															      *
 *********************************************************************************************************/
/************************************Header Files used*********************************************/
#include "lcd.h"
#include "keypad.h"
#include "timer_1.h"
#include "uart.h"
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
#define DOOR_IS_UNLOCK            15
#define DOOR_IS_LOCK              15
#define HOLD_MOTOR                3
#define PASS_TRIAL                3
#define WARNING                   60
/*******************************************************************************
 *                             Global Variables                                *
 *******************************************************************************/
uint8 UART_Received_Byte=0;
uint16 g_ticks = 0;
uint8 i=0;
uint8 current_key;
uint8 User_Current_Password[PASSWORD_SIZE];
/*******************************************************************************
 *                      	Functions Prototypes                                *
 *******************************************************************************/
void Timer1_callback(void);
void Set_Password(void);
void Send_Password(uint8 *password,uint8 size);
void Enter_Pass_Message(void);
void RePassword_Message(void);
void change_Pass_Message(void);
void Get_Password(uint8* pass,uint8 size);
void Display_Main_Options(void);
void open_Door(void);
void change_Pass(void);
void Motor_function(void);
void Warning_Message(void);
void Wrong_Message(void);
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

	/*Initialization The LCD*/
	LCD_init();

	/*lcd initialization ended ready to communicate!*/
	UART_sendByte(MC1_READY);

	LCD_displayStringRowColumn(0,0,"Door Locker");
	LCD_displayStringRowColumn(1,0,"System :)");
	_delay_ms(1000);

	/*Setting the password for the first time*/
	Set_Password();

	/*Our main is quite simple after setting password you have two options either to opendoor
	 * or to close door each with separete function
	 */
	while(1)
	{
		/*get current pressed key from keypad*/
		current_key = KEYPAD_getPressedKey();

		/*The LCD will always display the main system options*/
		Display_Main_Options();

		/*based on which key you have entered function will be called*/
		if(current_key == OPEN_DOOR)
		{
			/*call open door function*/
			open_Door();
		}
		else if(current_key == CHANGE_PASS)
		{
			/*call change pass function*/
			change_Pass();
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
	/*initialize two arries each for password*/
	uint8 arr_pass_first[PASSWORD_SIZE] , arr_pass_second[PASSWORD_SIZE];

	/*Initial value two pass doesn't match*/
	uint8 pass_state = PASSWORDS_UNMATCH;

	/*as long as two passwords doesn't match you are stuck in this while loop*/
	while(pass_state == PASSWORDS_UNMATCH){

		/*message to enter password*/
		Enter_Pass_Message();

		/*Enter a password consists of 5 numbers, Display * in the screen for each number.*/
		Get_Password(arr_pass_first,PASSWORD_SIZE);

		LCD_clearScreen();

		/*second password message*/
		RePassword_Message();

		/*set second password verification*/
		Get_Password(arr_pass_second,PASSWORD_SIZE);

		/*send verification to second MC to start communication!*/
		UART_sendByte(MC1_READY);

		/*send first password*/
		Send_Password(arr_pass_first,PASSWORD_SIZE);

		/*Don't send second pass until you get verification from first*/
		while(UART_recieveByte() != FIRST_PASSWORD_RECIVED);

		/*send second password*/
		Send_Password(arr_pass_second,PASSWORD_SIZE);

		while(UART_recieveByte() != SECOND_PASSWORD_RECIVED);

		/*save the check in pass_state*/
		pass_state = UART_recieveByte();
		if(pass_state == PASSWORDS_UNMATCH)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Pass Unmatch");
			LCD_displayStringRowColumn(1,1,"Try again!");
			_delay_ms(1000);
		}

	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"New Pass is Set!");
	_delay_ms(1000);
	LCD_clearScreen();
	/*If Password MATCHED display main menu one time before while*/
	Display_Main_Options();
}

/*******************************************************************************/
void Enter_Pass_Message(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Enter Pass:");
	LCD_moveCursor(1,0);
}
/*******************************************************************************/
void RePassword_Message(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz re-enter the");
	LCD_displayStringRowColumn(1,0,"same pass: ");
}
/*******************************************************************************/
void Display_Main_Options(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0," + : Open door");
	LCD_displayStringRowColumn(1,0," - : Change Pass");
}
/*******************************************************************************/
void change_Pass_Message(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz enter your");
	LCD_displayStringRowColumn(1,0,"old pass: ");
}
/*******************************************************************************/
void Warning_Message(void){
	g_ticks=0;
	LCD_clearScreen();
	while(g_ticks < WARNING){
		LCD_displayStringRowColumn(0,2,"!!!Warning!!!");
	}
	LCD_clearScreen();
	/*The LCD will always display the main system options*/
	Display_Main_Options();

}
/*******************************************************************************/
void Wrong_Message(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,4,"Wrong Pass");
	LCD_displayStringRowColumn(1,4,"Try again!");
	_delay_ms(1000);
}
/*******************************************************************************/
void Get_Password(uint8* pass,uint8 size){
	uint8 key;
	for(i=0 ; i<size ; i++){
		_delay_ms(400);
		key =  KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		pass[i] =  key;
		_delay_ms(200);
	}

	while(KEYPAD_getPressedKey() != ENTER);
}
/*******************************************************************************/
void Send_Password(uint8 *pass ,uint8 size){

	for (i=0;i<size;i++)
	{
		UART_sendByte(pass[i]);
		_delay_ms(50);
	}
}
/*******************************************************************************/
void open_Door(){
	uint8 state = PASSWORDS_UNMATCH;

	while(state == PASSWORDS_UNMATCH){
		/*enter message*/
		Enter_Pass_Message();
		/*get password*/
		Get_Password(User_Current_Password,PASSWORD_SIZE);
		/*send command to MC2*/
		UART_sendByte(OPEN_DOOR);

		while(UART_recieveByte() != MC2_READY);
		/*send password to check*/
		Send_Password(User_Current_Password,PASSWORD_SIZE);

		UART_Received_Byte = UART_recieveByte();
		/*check the states of the entered password*/
		if (UART_Received_Byte == PASSWORDS_MATCH){
			Motor_function();
			break;
		}
		else if(UART_Received_Byte  == PASSWORDS_UNMATCH){
			Wrong_Message();
			state = PASSWORDS_UNMATCH;
		}
		else if(UART_Received_Byte  == WARNING){
			Warning_Message();
			break;
		}
	}

}
/*******************************************************************************/
void change_Pass(void){
	uint8 state = PASSWORDS_UNMATCH;
	while(state == PASSWORDS_UNMATCH){
		/*change pass message*/
		change_Pass_Message();
		/*get password*/
		Get_Password(User_Current_Password,PASSWORD_SIZE);
		/*send command to MC2*/
		UART_sendByte(CHANGE_PASS);

		while(UART_recieveByte() != MC2_READY);
		/*send password to check*/
		Send_Password(User_Current_Password,PASSWORD_SIZE);

		UART_Received_Byte = UART_recieveByte();
		/*check the states of the entered password*/
		if (UART_Received_Byte == PASSWORDS_MATCH){
			Set_Password();
			break;
		}
		else if(UART_Received_Byte  == PASSWORDS_UNMATCH){
			Wrong_Message();
			state = PASSWORDS_UNMATCH;
		}
		else if(UART_Received_Byte  == WARNING){
			Warning_Message();
			break;
		}
	}
}
/*******************************************************************************/
void Motor_function(void){
	/*Opening the door in 15sec*/
	g_ticks=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,4,"Door is");
	LCD_displayStringRowColumn(1,4,"Unlocking!");
	while (g_ticks < DOOR_IS_UNLOCK);

	/*Holding the door in 3sec*/
	g_ticks=0;
	LCD_clearScreen();
	LCD_displayString("Door is Unlock!");
	while (g_ticks < HOLD_MOTOR);

	/*Closing the door in 15sec*/
	g_ticks=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,4,"Door is");
	LCD_displayStringRowColumn(1,4,"locking!");
	while (g_ticks < DOOR_IS_LOCK);

	/*Stop the Motor*/
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,4,"Door is");
	LCD_displayStringRowColumn(1,4,"locked!");
	_delay_ms(1000);
	/*The LCD will always display the main system options*/
	LCD_clearScreen();
	Display_Main_Options();
}
/*******************************************************************************/
