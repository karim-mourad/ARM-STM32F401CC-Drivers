#include "LED.h"
#include "LED_Cfg.h"

LED_tenuErrorStatus LED_Init(void)
{
	LED_tenuErrorStatus loc_Error_Status = LED_enuOK;

	GPIO_Cfg_t GPIO_Cfg;
	u8 loc_iterartor = 0;
	for(loc_iterartor=0;loc_iterartor<LED_count;loc_iterartor++)
	{
		GPIO_Cfg.GPIO_PORT = ledcfg[loc_iterartor].LED_PORT;
		GPIO_Cfg.GPIO_PIN = ledcfg[loc_iterartor].LED_PIN;
		GPIO_Cfg.GPIO_SPEED = ledcfg[loc_iterartor].LED_SPEED;
		GPIO_Cfg.GPIO_MODE = GPIO_OUTPUT_PP;
		GPIO_Init(&GPIO_Cfg);
	}

	return loc_Error_Status;
}

LED_tenuErrorStatus LED_Set_State(u8 LED_NO, u8 LED_STATE)
{
	LED_tenuErrorStatus loc_Error_Status = LED_enuOK;
	GPIO_Cfg_t GPIO_Cfg;

	GPIO_Cfg.GPIO_PORT = ledcfg[LED_NO].LED_PORT;
	GPIO_Cfg.GPIO_PIN = ledcfg[LED_NO].LED_PIN;
	GPIO_Cfg.GPIO_SPEED = ledcfg[LED_NO].LED_SPEED;
    GPIO_Cfg.GPIO_MODE = GPIO_OUTPUT_PP;


	GPIO_SetPins(&GPIO_Cfg,GPIO_Cfg.GPIO_PIN,LED_STATE^ledcfg[LED_NO].LED_MODE);


	return loc_Error_Status;
}



