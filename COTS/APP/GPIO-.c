
#include <stdio.h>
#include <stdlib.h>
#include "GPIO.H"
#include "RCC.h"
#include "LED.h"
#include "SWITCH.h"

int main(void)
{
u16 p = 0;
/*GPIO_Cfg_t LED_1;
RCC_EnablePeri(BUS_AHB1, GPIO_A);
LED_1.GPIO_PORT = GPIO_PORT_A;
LED_1.GPIO_PIN = GPIO_PIN_0;
LED_1.GPIO_MODE = GPIO_OUTPUT_PP;
LED_1.GPIO_SPEED = GPIO_SPEED_VERY_HIGH;
GPIO_Init(&LED_1);
//GPIO_SetPins(&LED_1, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6, GPIO_SET_PIN_VALUE_HIGH);
GPIO_SetPort(&LED_1, GPIO_SET_PIN_VALUE_HIGH);
*/
	RCC_EnablePeri(BUS_AHB1, GPIO_A);
	LED_Init();
	SWITCH_Init();


  while (1)
    {
		SWITCH_Get_State(0, &p);
		if(p == 0)
		{
			LED_Set_State(0, ON);
		}
		else if(p == 1)
		{
			LED_Set_State(0, OFF);
		}
    }
}
