
#ifndef SYSTICK_H_
#define SYSTICK_H_

/*****************Includes*****************/

#include "Std_Types.h"

/*****************Defines*****************/

#define TICKINT_ENABLE   	((u32)0x00000002)
#define TICKINT_DISABLE   	((u32)0x00000000)

#define CLKSOURCE_AHB_8   	((u32)0x00000000)
#define CLKSOURCE_AHB   	((u32)0x00000004)

#define CONTROL_CLEAR_MASK	((u32)0xFFFFFFF9)

#define SYSTICK_START		((u32)0x00000001)
#define SYSTICK_STOP		((u32)0xFFFFFFFE)

/******************Types******************/

typedef enum
{
	SYSTICK_enuOK = 0,
	SYSTICK_enuNOK

}SYSTICK_tenuErrorStatus;

typedef void(*SYSTICK_CBF_t)(void);


/******************API's******************/



/*
Description:
Initialise the SYSTICK with the desired configurations

Options:
check the SYSTICK_Cfg.h file

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

SYSTICK_tenuErrorStatus SYSTICK_Init(void);




/*
Description:
Start the SYSTICK

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

SYSTICK_tenuErrorStatus SYSTICK_Start(void);




/*
Description:
Stop the SYSTICK

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

SYSTICK_tenuErrorStatus SYSTICK_Stop(void);




/*
Description:
Set the desired tick time in ms

Options:
Cpy_timeMS  ==>  the desired time

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

SYSTICK_tenuErrorStatus SYSTICK_SetTickTimeMS(u32 Cpy_timeMS);




/*
Description:
Set the desired function to execute in systick handler

Options:
CBF  ==>  the desired function

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

SYSTICK_tenuErrorStatus SYSTICK_SetCBF(SYSTICK_CBF_t CBF);

#endif /* SYSTICK_H_ */
