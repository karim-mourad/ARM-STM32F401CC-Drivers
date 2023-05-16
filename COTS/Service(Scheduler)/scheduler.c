#include "SYSTICK.h"
#include "scheduler.h"

tasks_t tasks[NUM];
static u8 sched_flag=0;
const u32 tick = 2;

static void tick_cbf(void)
{
	if(sched_flag == 0)
	{
		sched_flag=1;
	}

	else
	{
		//CPU_LOAD>100%
	}
}



static void sched(void)
{
	u8 i;
	for(i=0;i<NUM;i++)
	{
		if(tasks[i].remain == 0)
		{
			tasks[i].App_Info->cbf();
			tasks[i].remain = tasks[i].App_Info->period_ms;
		}
		tasks[i].remain-= tick;

	}

}

void sched_init(void)
{
	u8 i;
	for(i=0;i<NUM;i++)
	{
		tasks[i].App_Info = &Apps[i];
		tasks[i].remain = Apps[i].start_delay_ms;
	}

	SYSTICK_Init();
	SYSTICK_SetTickTimeMS(tick);
	SYSTICK_SetCBF(tick_cbf);


}


void sched_start(void)
{
	SYSTICK_Start();
	while(1)
	{
		if(sched_flag == 1)
		{
			sched();
			sched_flag = 0;
		}
	}

}
