#include <stdio.h>
#include <stdlib.h>
#include "NVIC.h"
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#pragma GCC diagnostic ignored "-Wmissing-declarations"
//#pragma GCC diagnostic ignored "-Wreturn-type"

volatile u8 x = 0;
void EXTI0_IRQHandler(void)
{
	x++;
}


int main()
{

	NVIC_EnableInterrupt(EXTI0);
	//NVIC_DisableInterrupt(EXTI0);
	NVIC_SetSysSubGroup(NVIC_ALL_PREEMPTION);
	NVIC_SetPriority(EXTI0,5,0);
	NVIC_EnableInterrupt(EXTI0);
  while (1)
    {

    }

}

