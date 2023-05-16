

#ifndef SWITCH_H_
#define SWITCH_H_


/*****************Includes*****************/
#include "Std_Types.h"
#include "GPIO.h"
#include "SWITCH_Cfg.h"

/*****************Defines*****************/
#define SWITCH_PORT_A     ((void*)0x40020000)
#define SWITCH_PORT_B     ((void*)0x40020400)
#define SWITCH_PORT_C     ((void*)0x40020800)
#define SWITCH_PORT_D     ((void*)0x40020C00)
#define SWITCH_PORT_E     ((void*)0x40021000)
#define SWITCH_PORT_H     ((void*)0x40021C00)

#define SWITCH_PIN_0 	(0x00000001)
#define SWITCH_PIN_1 	(0x00000002)
#define SWITCH_PIN_2 	(0x00000004)
#define SWITCH_PIN_3 	(0x00000008)
#define SWITCH_PIN_4 	(0x00000010)
#define SWITCH_PIN_5 	(0x00000020)
#define SWITCH_PIN_6 	(0x00000040)
#define SWITCH_PIN_7 	(0x00000080)
#define SWITCH_PIN_8 	(0x00000100)
#define SWITCH_PIN_9 	(0x00000200)
#define SWITCH_PIN_10 	(0x00000400)
#define SWITCH_PIN_11 	(0x00000800)
#define SWITCH_PIN_12 	(0x00001000)
#define SWITCH_PIN_13 	(0x00002000)
#define SWITCH_PIN_14 	(0x00004000)
#define SWITCH_PIN_15 	(0x00008000)

#define SWITCH_SPEED_LOW			0
#define SWITCH_SPEED_MEDIUM			1
#define SWITCH_SPEED_HIGH			2
#define SWITCH_SPEED_VERY_HIGH		3

#define ON 	1
#define OFF	0

#define PULL_UP		 (0b000001)
#define PULL_DOWN    (0b000010)

/******************Types******************/
typedef struct
{
	void * SWITCH_PORT;
	u16 SWITCH_PIN;
	u8 SWITCH_MODE;
	u8 SWITCH_SPEED;
	u8 SWITCH_PIN_No;

}SWITCH_Cfg_t;

typedef enum
{
	SWITCH_enuOK = 0,
	SWITCH_enuNOK

}SWITCH_tenuErrorStatus;


extern const SWITCH_Cfg_t switchcfg[SWITCH_count];
/******************API's******************/


/*
Description:
Initializing all the SWITCHs

Return:
SWITCH Error status
*/
SWITCH_tenuErrorStatus SWITCH_Init(void);



/*
Description:
Get the status of a specific SWITCH

Options:
SWITCH_NO ==> the number of the targeted SWITCH
SWITCH_STATE ==> Address of a variable to store the state

Return:
SWITCH Error status
*/
SWITCH_tenuErrorStatus SWITCH_Get_State(u8 SWITCH_NO, u16* SWITCH_STATE);



/*Scheduler part*/
//void SWITCH_Task(void);

u8 SWITCH_Return_State(u8 SWITCH_No);


#endif /* SWITCH_H_ */
