

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Std_Types.h"


#define NUM 3


typedef void(*runnable_cbf_t)(void);



typedef struct
{
	char * name;
	runnable_cbf_t cbf;
	u32 period_ms;
	u32 start_delay_ms;

}App_Info_t;


typedef struct
{
	App_Info_t* App_Info;
	u32 remain;

}tasks_t;






void sched_init(void);

void sched_start(void);

extern App_Info_t Apps[NUM];














#endif /* SCHEDULER_H_ */
