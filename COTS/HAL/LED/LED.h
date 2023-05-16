/*
 * LED.h
 *
 *  Created on: 1 Mar 2023
 *      Author: HP
 */

#ifndef LED_H_
#define LED_H_

/*****************Includes*****************/
#include "Std_Types.h"
#include "GPIO.h"
#include "LED_Cfg.h"

/*****************Defines*****************/
#define LED_PORT_A     ((void*)0x40020000)
#define LED_PORT_B     ((void*)0x40020400)
#define LED_PORT_C     ((void*)0x40020800)
#define LED_PORT_D     ((void*)0x40020C00)
#define LED_PORT_E     ((void*)0x40021000)
#define LED_PORT_H     ((void*)0x40021C00)

#define LED_PIN_0 	(0x00000001)
#define LED_PIN_1 	(0x00000002)
#define LED_PIN_2 	(0x00000004)
#define LED_PIN_3 	(0x00000008)
#define LED_PIN_4 	(0x00000010)
#define LED_PIN_5 	(0x00000020)
#define LED_PIN_6 	(0x00000040)
#define LED_PIN_7 	(0x00000080)
#define LED_PIN_8 	(0x00000100)
#define LED_PIN_9 	(0x00000200)
#define LED_PIN_10 	(0x00000400)
#define LED_PIN_11 	(0x00000800)
#define LED_PIN_12 	(0x00001000)
#define LED_PIN_13 	(0x00002000)
#define LED_PIN_14 	(0x00004000)
#define LED_PIN_15 	(0x00008000)

#define LED_SPEED_LOW			0
#define LED_SPEED_MEDIUM		1
#define LED_SPEED_HIGH			2
#define LED_SPEED_VERY_HIGH		3

#define ON 	1
#define OFF	0

#define ACTIVE_HIGH 0
#define ACTIVE_LOW  1

/******************Types******************/
typedef struct
{
	void * LED_PORT;
	u16 LED_PIN;
	u8 LED_MODE;
	u8 LED_SPEED;

}LED_Cfg_t;

typedef enum
{
	LED_enuOK = 0,
	LED_enuNOK

}LED_tenuErrorStatus;


extern const LED_Cfg_t ledcfg[LED_count];
/******************API's******************/


/*
Description:
Initializing all the LEDs

Return:
LED Error status
*/
LED_tenuErrorStatus LED_Init(void);



/*
Description:
Turning a specific LED on or off

Options:
LED_NO ==> the number of the targeted LED
LED_STATE ==> ON or OFF

Return:
LED Error status
*/
LED_tenuErrorStatus LED_Set_State(u8 LED_NO, u8 LED_STATE);

#endif /* LED_H_ */
