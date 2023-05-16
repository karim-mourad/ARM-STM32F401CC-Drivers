#include <stdio.h>
#include <stdlib.h>
#include "SYSTICK.h"
#include "GPIO.h"
#include "RCC.h"
#include "LED.h"
#include "scheduler.h"

int main()
{
	RCC_Set_HSI_ON();
	RCC_SelectSystemClock(CLK_HSI);
	RCC_EnablePeri(BUS_AHB1, GPIO_A);
	RCC_EnablePeri(BUS_AHB1, GPIO_B);
	RCC_EnablePeri(BUS_AHB1, GPIO_C);
	LED_Init();
	sched_init();
	sched_start();
  while (1)
    {

    }
}
