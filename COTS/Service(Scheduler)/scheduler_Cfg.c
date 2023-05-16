#include "scheduler.h"
#include "APP1.h"
#include "APP2.h"
#include "APP3.h"


App_Info_t Apps[NUM] =
{

	[0] = {
			.name = "App1",
			.cbf = APP1_runnable,
			.period_ms = 1000,
			.start_delay_ms = 0
	},


	[1] = {
			.name = "App2",
			.cbf = APP2_runnable,
			.period_ms = 10000,
			.start_delay_ms = 0
	},

	[2] = {
			.name = "App3",
			.cbf = APP3_runnable,
			.period_ms = 15000,
			.start_delay_ms = 0
	}



};


