
#include "SWITCH.h"
#include "SWITCH_Cfg.h"


u8 STATE[SWITCH_count];

/********SCHEDULER PART*********/
void SWITCH_Task(void)
{
	static u8 counter[SWITCH_count];
	static u8 prev[SWITCH_count];
	u16 current;

	GPIO_Cfg_t GPIO_Cfg;
	u8 loc_iterartor = 0;
	for(loc_iterartor=0;loc_iterartor<SWITCH_count;loc_iterartor++)
	{
		GPIO_Cfg.GPIO_PORT = switchcfg[loc_iterartor].SWITCH_PORT;
		GPIO_Cfg.GPIO_PIN = switchcfg[loc_iterartor].SWITCH_PIN;
		GPIO_Cfg.GPIO_SPEED = switchcfg[loc_iterartor].SWITCH_SPEED;
		GPIO_Cfg.GPIO_MODE =  switchcfg[loc_iterartor].SWITCH_MODE;

		GPIO_GetPin(&GPIO_Cfg,switchcfg[loc_iterartor].SWITCH_PIN_No , &current);

		if(current == prev[loc_iterartor])
		{
			counter[loc_iterartor]++;
		}

		else
		{
			//prev[loc_iterartor] = current;
			counter[loc_iterartor]=0;
		}

		if(counter[loc_iterartor] == 5)
		{
			STATE[loc_iterartor] = current;
			counter[loc_iterartor] = 0;
		}

		prev[loc_iterartor] = current;
	}

}


u8 SWITCH_Return_State(u8 SWITCH_No)
{
	return STATE[SWITCH_No];
}

/********SCHEDULER PART*********/

SWITCH_tenuErrorStatus SWITCH_Init(void)
{
	SWITCH_tenuErrorStatus loc_Error_Status = SWITCH_enuOK;

	GPIO_Cfg_t GPIO_Cfg;
	u8 loc_iterartor = 0;
	for(loc_iterartor=0;loc_iterartor<SWITCH_count;loc_iterartor++)
	{
		GPIO_Cfg.GPIO_PORT = switchcfg[loc_iterartor].SWITCH_PORT;
		GPIO_Cfg.GPIO_PIN = switchcfg[loc_iterartor].SWITCH_PIN;
		GPIO_Cfg.GPIO_SPEED = switchcfg[loc_iterartor].SWITCH_SPEED;
		GPIO_Cfg.GPIO_MODE = switchcfg[loc_iterartor].SWITCH_MODE;
		GPIO_Init(&GPIO_Cfg);
	}

	return loc_Error_Status;
}


SWITCH_tenuErrorStatus SWITCH_Get_State(u8 SWITCH_NO, u16* SWITCH_STATE)
{
	SWITCH_tenuErrorStatus loc_Error_Status = SWITCH_enuOK;
	GPIO_Cfg_t GPIO_Cfg;

	GPIO_Cfg.GPIO_PORT = switchcfg[SWITCH_NO].SWITCH_PORT;
	GPIO_Cfg.GPIO_PIN = switchcfg[SWITCH_NO].SWITCH_PIN;
	GPIO_Cfg.GPIO_SPEED = switchcfg[SWITCH_NO].SWITCH_SPEED;
	GPIO_Cfg.GPIO_MODE =  switchcfg[SWITCH_NO].SWITCH_MODE;

	GPIO_GetPin(&GPIO_Cfg, switchcfg[SWITCH_NO].SWITCH_PIN_No, SWITCH_STATE);


	return loc_Error_Status;
}




