#include "SYSTICK.h"
#include "SYSTICK_Cfg.h"



typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;

}SYSTICK_t;


SYSTICK_t * const volatile SYSTICK = ((SYSTICK_t*)0xE000E010);

static SYSTICK_CBF_t SYSTICK_CBF;

SYSTICK_tenuErrorStatus SYSTICK_Init(void)
{
	SYSTICK_tenuErrorStatus Loc_Error_Status = SYSTICK_enuOK;

	u32 loc_buffer = SYSTICK->STK_CTRL;
	loc_buffer &= CONTROL_CLEAR_MASK;
	loc_buffer |= TICK_INT;
	loc_buffer |= CLKSRC;
	SYSTICK->STK_CTRL = loc_buffer;


	return Loc_Error_Status;
}

SYSTICK_tenuErrorStatus SYSTICK_Start(void)
{
	SYSTICK_tenuErrorStatus Loc_Error_Status = SYSTICK_enuOK;
	SYSTICK->STK_VAL = 0;
	u32 loc_buffer = SYSTICK->STK_CTRL;
	loc_buffer |= SYSTICK_START;
	SYSTICK->STK_CTRL = loc_buffer;

	return Loc_Error_Status;
}


SYSTICK_tenuErrorStatus SYSTICK_Stop(void)
{
	SYSTICK_tenuErrorStatus Loc_Error_Status = SYSTICK_enuOK;
	u32 loc_buffer = SYSTICK->STK_CTRL;
	loc_buffer &= SYSTICK_STOP;
	SYSTICK->STK_CTRL = loc_buffer;

	return Loc_Error_Status;
}



SYSTICK_tenuErrorStatus SYSTICK_SetTickTimeMS(u32 Cpy_timeMS)
{
	SYSTICK_tenuErrorStatus Loc_Error_Status = SYSTICK_enuOK;

	u8 prescaler = 1;
	if(CLKSRC == CLKSOURCE_AHB/8)
	{
		prescaler = 8;
	}
	SYSTICK->STK_LOAD = (u32)(SYSCLK/(prescaler*1000)) * Cpy_timeMS ;

	return Loc_Error_Status;
}


SYSTICK_tenuErrorStatus SYSTICK_SetCBF(SYSTICK_CBF_t CBF)
{
	SYSTICK_tenuErrorStatus Loc_Error_Status = SYSTICK_enuOK;

	if(CBF)
	{
		SYSTICK_CBF = CBF;
	}

	else
	{
		Loc_Error_Status = SYSTICK_enuNOK;
	}


	return Loc_Error_Status;
}




void SysTick_Handler(void)
{
	if(SYSTICK_CBF)
	{
		SYSTICK_CBF();
	}
}

