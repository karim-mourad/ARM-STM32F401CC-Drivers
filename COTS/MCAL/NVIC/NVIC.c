#include "NVIC.h"

#define SCB_AIRCR   *((volatile u32*)0xE000ED0C)


typedef struct
{
	u32 ISER[8];
	u32 reserved1[24];
	u32 ICER[8];
	u32 reserved2[24];
	u32 ISPR[8];
	u32 reserved3[24];
	u32 ICPR[8];
	u32 reserved4[24];
	u32 IABR[8];
	u32 reserved5[56];
	u8  IPR[240];
	u32 reserved6[580];
	u32 STIR;

}NVIC_t;

NVIC_t * const volatile NVIC = ((NVIC_t *)0xE000E100);


NVIC_tenuErrorStatus NVIC_EnableInterrupt(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;
	if(Cpy_InterruptNO > 240)
	{
		Loc_Error_Status = NVIC_enuInvalidInterruptNo;
	}

	else
	{
		/*Clear any previous pending before enabling the interrupt*/
		NVIC->ICPR[Cpy_InterruptNO/32] |= 1<<(Cpy_InterruptNO % 32);

		/*Enabling the required interrupt*/
		NVIC->ISER[Cpy_InterruptNO/32] |= 1<<(Cpy_InterruptNO % 32);
	}



	return Loc_Error_Status;
}


NVIC_tenuErrorStatus NVIC_DisableInterrupt(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;
	if(Cpy_InterruptNO > 240)
	{
		Loc_Error_Status = NVIC_enuInvalidInterruptNo;
	}

	else
	{
		/*Disabling the required interrupt*/
		NVIC->ICER[Cpy_InterruptNO/32] |= 1<<(Cpy_InterruptNO % 32);
	}



	return Loc_Error_Status;
}



NVIC_tenuErrorStatus NVIC_SetPendingFlag(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;
	if(Cpy_InterruptNO > 240)
	{
		Loc_Error_Status = NVIC_enuInvalidInterruptNo;
	}

	else
	{
		/*Setting the specified interrupt pending flag*/
		NVIC->ISPR[Cpy_InterruptNO/32] |= 1<<(Cpy_InterruptNO % 32);
	}



	return Loc_Error_Status;
}




NVIC_tenuErrorStatus NVIC_ClearPendingFlag(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;
	if(Cpy_InterruptNO > 240)
	{
		Loc_Error_Status = NVIC_enuInvalidInterruptNo;
	}

	else
	{
		/*Setting the specified interrupt pending flag*/
		NVIC->ICPR[Cpy_InterruptNO/32] |= 1<<(Cpy_InterruptNO % 32);
	}



	return Loc_Error_Status;
}





NVIC_tenuErrorStatus NVIC_GetPendingFlag(u8 Cpy_InterruptNO, u8 * Cpy_Val)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;
	if(Cpy_InterruptNO > 240)
	{
		Loc_Error_Status = NVIC_enuInvalidInterruptNo;
	}

	else
	{
		/*Getting the specified interrupt pending flag status*/
		*Cpy_Val = ((NVIC->ISPR[Cpy_InterruptNO/32] >> Cpy_InterruptNO%32) & 1);
	}

	return Loc_Error_Status;
}


NVIC_tenuErrorStatus NVIC_GetActiveInterrupt(u8 Cpy_InterruptNO, u8 * Cpy_Val)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;
	if(Cpy_InterruptNO > 240)
	{
		Loc_Error_Status = NVIC_enuInvalidInterruptNo;
	}

	else
	{
		/*Getting the specified interrupt Active status*/
		*Cpy_Val = ((NVIC->IABR[Cpy_InterruptNO/32] >> Cpy_InterruptNO%32) & 1);
	}

	return Loc_Error_Status;
}




NVIC_tenuErrorStatus NVIC_TriggerSWInterrupt(u8 Cpy_InterruptNO)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;
	if(Cpy_InterruptNO > 240)
	{
		Loc_Error_Status = NVIC_enuInvalidInterruptNo;
	}

	else
	{
		/*Generating the specified SW interrupt*/
		NVIC->STIR = Cpy_InterruptNO;

	}

	return Loc_Error_Status;
}






NVIC_tenuErrorStatus NVIC_SetSysSubGroup(u32 Cpy_SubGroupBits)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;

	if(Cpy_SubGroupBits == NVIC_ALL_PREEMPTION  ||  Cpy_SubGroupBits == NVIC_THREE_PREEMPTION_ONE_SUBGROUP  ||
	   Cpy_SubGroupBits == NVIC_TWO_PREEMPTION_TWO_SUBGROUP  ||  Cpy_SubGroupBits == NVIC_ONE_PREEMPTION_THREE_SUBGROUP  ||
	   Cpy_SubGroupBits == NVIC_ALL_SUBGROUP)
	{
		SCB_AIRCR = Cpy_SubGroupBits;
	}

	else
	{
		Loc_Error_Status = NVIC_enuNOK;
	}



	return Loc_Error_Status;
}







NVIC_tenuErrorStatus NVIC_SetPriority(u8 Cpy_InterruptNo, u8 CpyPreemptionNo, u8 Cpy_SubgroupNo)
{
	NVIC_tenuErrorStatus Loc_Error_Status = NVIC_enuOK;

	u8 Loc_IPRbuffer = NVIC->IPR[Cpy_InterruptNo];

	Loc_IPRbuffer=(Cpy_SubgroupNo|(CpyPreemptionNo<<((SCB_AIRCR - NVIC_ALL_PREEMPTION)/256)))<<4;


	NVIC->IPR[Cpy_InterruptNo]=Loc_IPRbuffer;


	return Loc_Error_Status;
}
