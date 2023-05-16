
#include "SWITCH.h"
#include "SWITCH_Cfg.h"


const SWITCH_Cfg_t switchcfg[SWITCH_count] =
{
		[SWITCH_0] = {.SWITCH_PORT= SWITCH_PORT_A,
		.SWITCH_PIN= SWITCH_PIN_3,
		.SWITCH_MODE= PULL_UP,
		.SWITCH_SPEED = SWITCH_SPEED_VERY_HIGH,
		.SWITCH_PIN_No = 3}
};
