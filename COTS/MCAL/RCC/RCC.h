/*
 * RCC.h
 *
 *  Created on: 22 Feb 2023
 *      Author: HP
 */

#ifndef RCC_H_
#define RCC_H_

/*****************Includes*****************/

#include "Std_Types.h"


/*****************Defines*****************/

#define RCC_sysCLK_Rdy_TimeOut 10000

#define HSE_BYPASS     		1
#define HSE_OSCILLATOR 		0

#define CLK_HSI 0
#define CLK_HSE 1
#define CLK_PLL 2

#define SELECT_SYS_CLK_CLR_MASK 	0xFFFFFFFC
#define SELECT_SYS_CLK_HSI			0x00000000
#define SELECT_SYS_CLK_HSE			0x00000001
#define SELECT_SYS_CLK_PLL			0x00000002

#define GET_SYS_CLK_MASK			0x0000000C

#define PLL_CLK_SRC_HSI 0
#define PLL_CLK_SRC_HSE 1

#define PLL_CFG_P_CLR_MASK			0xFFFCFFFF
#define PLL_CFG_M_CLR_MASK			0xFFFFFFC0
#define PLL_CFG_N_CLR_MASK			0xFFFF803F

#define BUS_AHB1  0
#define BUS_AHB2  1
#define BUS_APB1  2
#define BUS_APB2  3

#define GPIO_A 	0
#define GPIO_B		1
#define GPIO_C		2
#define GPIO_D		3
#define GPIO_E		4
#define GPIO_H		7
#define CRC			12
#define DMA1		21
#define DMA2		22

#define OTGFS   	7

#define TIM2		0
#define TIM3		1
#define TIM4		2
#define TIM5		3
#define WWDG		11
#define SPI2		14
#define SPI3		15
#define USART2		17
#define I2C1		21
#define I2C2		22
#define I2C3		23
#define PWR   		28

#define TIM1		0
#define USART1		4
#define USART6		5
#define ADC1		8
#define SDIO		11
#define SPI1		12
#define SPI4		13
#define SYSCFG		14
#define TIM9		16
#define TIM10		17
#define TIM11		18

#define RTCPRE	0
#define PPRE2   1
#define PPRE1   2
#define HPRE    3

#define HPRE_CLR_MASK		0xFFFFFF0F
#define HPRE_Div_2			0x0000080
#define HPRE_Div_4			0x0000090
#define HPRE_Div_8			0x00000A0
#define HPRE_Div_16			0x00000B0
#define HPRE_Div_64			0x00000C0
#define HPRE_Div_128		0x00000D0
#define HPRE_Div_256		0x00000E0
#define HPRE_Div_512		0x00000F0

#define PPRE1_CLR_MASK		0xFFFFE3FF
#define PPRE1_Div_2			0x00001000
#define PPRE1_Div_4			0x00001400
#define PPRE1_Div_8			0x00001800
#define PPRE1_Div_16		0x00001C00

#define PPRE2_CLR_MASK		0xFFFF1FFF
#define PPRE2_Div_2			0x00008000
#define PPRE2_Div_4			0x0000A000
#define PPRE2_Div_8			0x0000C000
#define PPRE2_Div_16		0x0000E000

#define RTCPRE_CLR_MASK		0xFFE0FFFF
#define RTCPRE_Div_2		0x00020000
#define RTCPRE_Div_3		0x00030000
#define RTCPRE_Div_4		0x00040000
#define RTCPRE_Div_5		0x00050000
#define RTCPRE_Div_6		0x00060000
#define RTCPRE_Div_7		0x00070000
#define RTCPRE_Div_8		0x00080000
#define RTCPRE_Div_9		0x00090000
#define RTCPRE_Div_10		0x000A0000
#define RTCPRE_Div_11		0x000B0000
#define RTCPRE_Div_12		0x000C0000
#define RTCPRE_Div_13		0x000D0000
#define RTCPRE_Div_14		0x000E0000
#define RTCPRE_Div_15		0x000F0000
#define RTCPRE_Div_16		0x00100000
#define RTCPRE_Div_17		0x00110000
#define RTCPRE_Div_18		0x00120000
#define RTCPRE_Div_19		0x00130000
#define RTCPRE_Div_20		0x00140000
#define RTCPRE_Div_21		0x00150000
#define RTCPRE_Div_22		0x00160000
#define RTCPRE_Div_23		0x00170000
#define RTCPRE_Div_24		0x00180000
#define RTCPRE_Div_25		0x00190000
#define RTCPRE_Div_26		0x001A0000
#define RTCPRE_Div_27		0x001B0000
#define RTCPRE_Div_28		0x001C0000
#define RTCPRE_Div_29		0x001D0000
#define RTCPRE_Div_30		0x001E0000
#define RTCPRE_Div_31		0x001F0000



/******************Types******************/
typedef enum{

	RCC_enuOK,
	RCC_enuNOK,

	RCC_enuClockON,
	RCC_enuClockOFF,

	RCC_enuClockRdy,
	RCC_enuClockNotRdy,

	RCC_enuInvalidSysCLK,

	RCC_enuInvalidPLLSRC,

	RCC_enuInvalidPLLCFG_M,
	RCC_enuInvalidPLLCFG_N,
	RCC_enuInvalidPLLCFG_P,

	 RCC_enuInvalidBus,
	 RCC_enuInvalidPeri,

	 RCC_enuInvalidPrescaler

}RCC_tenuErrorStatus;



typedef enum{

	RCC_enu_P_DivideBy2 = 0,
	RCC_enu_P_DivideBy4 = 1,
	RCC_enu_P_DivideBy6 = 2,
	RCC_enu_P_DivideBy8 = 3

}RCC_tenuPLLCfgP;


typedef enum{

	RCC_enu_M_DivideBy2 = 2,
	RCC_enu_M_DivideBy3 ,
	RCC_enu_M_DivideBy4 ,
	RCC_enu_M_DivideBy5 ,
	RCC_enu_M_DivideBy6 ,
	RCC_enu_M_DivideBy7 ,
	RCC_enu_M_DivideBy8 ,
	RCC_enu_M_DivideBy9 ,
	RCC_enu_M_DivideBy10,
	RCC_enu_M_DivideBy11,
	RCC_enu_M_DivideBy12,
	RCC_enu_M_DivideBy13,
	RCC_enu_M_DivideBy14,
	RCC_enu_M_DivideBy15,
	RCC_enu_M_DivideBy16,
	RCC_enu_M_DivideBy17,
	RCC_enu_M_DivideBy18,
	RCC_enu_M_DivideBy19,
	RCC_enu_M_DivideBy20,
	RCC_enu_M_DivideBy21,
	RCC_enu_M_DivideBy22,
	RCC_enu_M_DivideBy23,
	RCC_enu_M_DivideBy24,
	RCC_enu_M_DivideBy25,
	RCC_enu_M_DivideBy26,
	RCC_enu_M_DivideBy27,
	RCC_enu_M_DivideBy28,
	RCC_enu_M_DivideBy29,
	RCC_enu_M_DivideBy30,
	RCC_enu_M_DivideBy31,
	RCC_enu_M_DivideBy32,
	RCC_enu_M_DivideBy33,
	RCC_enu_M_DivideBy34,
	RCC_enu_M_DivideBy35,
	RCC_enu_M_DivideBy36,
	RCC_enu_M_DivideBy37,
	RCC_enu_M_DivideBy38,
	RCC_enu_M_DivideBy39,
	RCC_enu_M_DivideBy40,
	RCC_enu_M_DivideBy41,
	RCC_enu_M_DivideBy42,
	RCC_enu_M_DivideBy43,
	RCC_enu_M_DivideBy44,
	RCC_enu_M_DivideBy45,
	RCC_enu_M_DivideBy46,
	RCC_enu_M_DivideBy47,
	RCC_enu_M_DivideBy48,
	RCC_enu_M_DivideBy49,
	RCC_enu_M_DivideBy50,
	RCC_enu_M_DivideBy51,
	RCC_enu_M_DivideBy52,
	RCC_enu_M_DivideBy53,
	RCC_enu_M_DivideBy54,
	RCC_enu_M_DivideBy55,
	RCC_enu_M_DivideBy56,
	RCC_enu_M_DivideBy57,
	RCC_enu_M_DivideBy58,
	RCC_enu_M_DivideBy59,
	RCC_enu_M_DivideBy60,
	RCC_enu_M_DivideBy61,
	RCC_enu_M_DivideBy62,
	RCC_enu_M_DivideBy63

}RCC_tenuPLLCfgM;



typedef enum{

	RCC_enu_N_DivideBy192 = 192,
	RCC_enu_N_DivideBy193,
	RCC_enu_N_DivideBy194,
	RCC_enu_N_DivideBy195,
	RCC_enu_N_DivideBy196,
	RCC_enu_N_DivideBy197,
	RCC_enu_N_DivideBy198,
	RCC_enu_N_DivideBy199,
	RCC_enu_N_DivideBy200,
	RCC_enu_N_DivideBy201,
	RCC_enu_N_DivideBy202,
	RCC_enu_N_DivideBy203,
	RCC_enu_N_DivideBy204,
	RCC_enu_N_DivideBy205,
	RCC_enu_N_DivideBy206,
	RCC_enu_N_DivideBy207,
	RCC_enu_N_DivideBy208,
	RCC_enu_N_DivideBy209,
	RCC_enu_N_DivideBy210,
	RCC_enu_N_DivideBy211,
	RCC_enu_N_DivideBy212,
	RCC_enu_N_DivideBy213,
	RCC_enu_N_DivideBy214,
	RCC_enu_N_DivideBy215,
	RCC_enu_N_DivideBy216,
	RCC_enu_N_DivideBy217,
	RCC_enu_N_DivideBy218,
	RCC_enu_N_DivideBy219,
	RCC_enu_N_DivideBy220,
	RCC_enu_N_DivideBy221,
	RCC_enu_N_DivideBy222,
	RCC_enu_N_DivideBy223,
	RCC_enu_N_DivideBy224,
	RCC_enu_N_DivideBy225,
	RCC_enu_N_DivideBy226,
	RCC_enu_N_DivideBy227,
	RCC_enu_N_DivideBy228,
	RCC_enu_N_DivideBy229,
	RCC_enu_N_DivideBy230,
	RCC_enu_N_DivideBy231,
	RCC_enu_N_DivideBy232,
	RCC_enu_N_DivideBy233,
	RCC_enu_N_DivideBy234,
	RCC_enu_N_DivideBy235,
	RCC_enu_N_DivideBy236,
	RCC_enu_N_DivideBy237,
	RCC_enu_N_DivideBy238,
	RCC_enu_N_DivideBy239,
	RCC_enu_N_DivideBy240,
	RCC_enu_N_DivideBy241,
	RCC_enu_N_DivideBy242,
	RCC_enu_N_DivideBy243,
	RCC_enu_N_DivideBy244,
	RCC_enu_N_DivideBy245,
	RCC_enu_N_DivideBy246,
	RCC_enu_N_DivideBy247,
	RCC_enu_N_DivideBy248,
	RCC_enu_N_DivideBy249,
	RCC_enu_N_DivideBy250,
	RCC_enu_N_DivideBy251,
	RCC_enu_N_DivideBy252,
	RCC_enu_N_DivideBy253,
	RCC_enu_N_DivideBy254,
	RCC_enu_N_DivideBy255,
	RCC_enu_N_DivideBy256,
	RCC_enu_N_DivideBy257,
	RCC_enu_N_DivideBy258,
	RCC_enu_N_DivideBy259,
	RCC_enu_N_DivideBy260,
	RCC_enu_N_DivideBy261,
	RCC_enu_N_DivideBy262,
	RCC_enu_N_DivideBy263,
	RCC_enu_N_DivideBy264,
	RCC_enu_N_DivideBy265,
	RCC_enu_N_DivideBy266,
	RCC_enu_N_DivideBy267,
	RCC_enu_N_DivideBy268,
	RCC_enu_N_DivideBy269,
	RCC_enu_N_DivideBy270,
	RCC_enu_N_DivideBy271,
	RCC_enu_N_DivideBy272,
	RCC_enu_N_DivideBy273,
	RCC_enu_N_DivideBy274,
	RCC_enu_N_DivideBy275,
	RCC_enu_N_DivideBy276,
	RCC_enu_N_DivideBy277,
	RCC_enu_N_DivideBy278,
	RCC_enu_N_DivideBy279,
	RCC_enu_N_DivideBy280,
	RCC_enu_N_DivideBy281,
	RCC_enu_N_DivideBy282,
	RCC_enu_N_DivideBy283,
	RCC_enu_N_DivideBy284,
	RCC_enu_N_DivideBy285,
	RCC_enu_N_DivideBy286,
	RCC_enu_N_DivideBy287,
	RCC_enu_N_DivideBy288,
	RCC_enu_N_DivideBy289,
	RCC_enu_N_DivideBy290,
	RCC_enu_N_DivideBy291,
	RCC_enu_N_DivideBy292,
	RCC_enu_N_DivideBy293,
	RCC_enu_N_DivideBy294,
	RCC_enu_N_DivideBy295,
	RCC_enu_N_DivideBy296,
	RCC_enu_N_DivideBy297,
	RCC_enu_N_DivideBy298,
	RCC_enu_N_DivideBy299,
	RCC_enu_N_DivideBy300,
	RCC_enu_N_DivideBy301,
	RCC_enu_N_DivideBy302,
	RCC_enu_N_DivideBy303,
	RCC_enu_N_DivideBy304,
	RCC_enu_N_DivideBy305,
	RCC_enu_N_DivideBy306,
	RCC_enu_N_DivideBy307,
	RCC_enu_N_DivideBy308,
	RCC_enu_N_DivideBy309,
	RCC_enu_N_DivideBy310,
	RCC_enu_N_DivideBy311,
	RCC_enu_N_DivideBy312,
	RCC_enu_N_DivideBy313,
	RCC_enu_N_DivideBy314,
	RCC_enu_N_DivideBy315,
	RCC_enu_N_DivideBy316,
	RCC_enu_N_DivideBy317,
	RCC_enu_N_DivideBy318,
	RCC_enu_N_DivideBy319,
	RCC_enu_N_DivideBy320,
	RCC_enu_N_DivideBy321,
	RCC_enu_N_DivideBy322,
	RCC_enu_N_DivideBy323,
	RCC_enu_N_DivideBy324,
	RCC_enu_N_DivideBy325,
	RCC_enu_N_DivideBy326,
	RCC_enu_N_DivideBy327,
	RCC_enu_N_DivideBy328,
	RCC_enu_N_DivideBy329,
	RCC_enu_N_DivideBy330,
	RCC_enu_N_DivideBy331,
	RCC_enu_N_DivideBy332,
	RCC_enu_N_DivideBy333,
	RCC_enu_N_DivideBy334,
	RCC_enu_N_DivideBy335,
	RCC_enu_N_DivideBy336,
	RCC_enu_N_DivideBy337,
	RCC_enu_N_DivideBy338,
	RCC_enu_N_DivideBy339,
	RCC_enu_N_DivideBy340,
	RCC_enu_N_DivideBy341,
	RCC_enu_N_DivideBy342,
	RCC_enu_N_DivideBy343,
	RCC_enu_N_DivideBy344,
	RCC_enu_N_DivideBy345,
	RCC_enu_N_DivideBy346,
	RCC_enu_N_DivideBy347,
	RCC_enu_N_DivideBy348,
	RCC_enu_N_DivideBy349,
	RCC_enu_N_DivideBy350,
	RCC_enu_N_DivideBy351,
	RCC_enu_N_DivideBy352,
	RCC_enu_N_DivideBy353,
	RCC_enu_N_DivideBy354,
	RCC_enu_N_DivideBy355,
	RCC_enu_N_DivideBy356,
	RCC_enu_N_DivideBy357,
	RCC_enu_N_DivideBy358,
	RCC_enu_N_DivideBy359,
	RCC_enu_N_DivideBy360,
	RCC_enu_N_DivideBy361,
	RCC_enu_N_DivideBy362,
	RCC_enu_N_DivideBy363,
	RCC_enu_N_DivideBy364,
	RCC_enu_N_DivideBy365,
	RCC_enu_N_DivideBy366,
	RCC_enu_N_DivideBy367,
	RCC_enu_N_DivideBy368,
	RCC_enu_N_DivideBy369,
	RCC_enu_N_DivideBy370,
	RCC_enu_N_DivideBy371,
	RCC_enu_N_DivideBy372,
	RCC_enu_N_DivideBy373,
	RCC_enu_N_DivideBy374,
	RCC_enu_N_DivideBy375,
	RCC_enu_N_DivideBy376,
	RCC_enu_N_DivideBy377,
	RCC_enu_N_DivideBy378,
	RCC_enu_N_DivideBy379,
	RCC_enu_N_DivideBy380,
	RCC_enu_N_DivideBy381,
	RCC_enu_N_DivideBy382,
	RCC_enu_N_DivideBy383,
	RCC_enu_N_DivideBy384,
	RCC_enu_N_DivideBy385,
	RCC_enu_N_DivideBy386,
	RCC_enu_N_DivideBy387,
	RCC_enu_N_DivideBy388,
	RCC_enu_N_DivideBy389,
	RCC_enu_N_DivideBy390,
	RCC_enu_N_DivideBy391,
	RCC_enu_N_DivideBy392,
	RCC_enu_N_DivideBy393,
	RCC_enu_N_DivideBy394,
	RCC_enu_N_DivideBy395,
	RCC_enu_N_DivideBy396,
	RCC_enu_N_DivideBy397,
	RCC_enu_N_DivideBy398,
	RCC_enu_N_DivideBy399,
	RCC_enu_N_DivideBy400,
	RCC_enu_N_DivideBy401,
	RCC_enu_N_DivideBy402,
	RCC_enu_N_DivideBy403,
	RCC_enu_N_DivideBy404,
	RCC_enu_N_DivideBy405,
	RCC_enu_N_DivideBy406,
	RCC_enu_N_DivideBy407,
	RCC_enu_N_DivideBy408,
	RCC_enu_N_DivideBy409,
	RCC_enu_N_DivideBy410,
	RCC_enu_N_DivideBy411,
	RCC_enu_N_DivideBy412,
	RCC_enu_N_DivideBy413,
	RCC_enu_N_DivideBy414,
	RCC_enu_N_DivideBy415,
	RCC_enu_N_DivideBy416,
	RCC_enu_N_DivideBy417,
	RCC_enu_N_DivideBy418,
	RCC_enu_N_DivideBy419,
	RCC_enu_N_DivideBy420,
	RCC_enu_N_DivideBy421,
	RCC_enu_N_DivideBy422,
	RCC_enu_N_DivideBy423,
	RCC_enu_N_DivideBy424,
	RCC_enu_N_DivideBy425,
	RCC_enu_N_DivideBy426,
	RCC_enu_N_DivideBy427,
	RCC_enu_N_DivideBy428,
	RCC_enu_N_DivideBy429,
	RCC_enu_N_DivideBy430,
	RCC_enu_N_DivideBy431,
	RCC_enu_N_DivideBy432

}RCC_tenuPLLCfgN;

/******************API's******************/

/*
Description:
Set HSI ON

Return: Error status to make sure it is ON
*/

RCC_tenuErrorStatus RCC_SetHSI_ON(void);


/*
Description:
Set HSI OFF

Return: Error status to make sure it is OFF
*/

RCC_tenuErrorStatus RCC_SetHSI_OFF(void);




/*
Description:
Set HSE ON

Options:
HSE_BYPASS
HSE_OSCILLATOR

Return: Error status to make sure it is ON
*/

RCC_tenuErrorStatus RCC_SetHSE_ON(u8 HSE_STATE);



/*
Description:
Set HSE OFF

Return: Error status to make sure it is OFF
*/

RCC_tenuErrorStatus RCC_SetHSE_OFF(void);



/*
Description:
Set PLL ON

Return: Error status to make sure it is ON
*/

RCC_tenuErrorStatus RCC_SetPLL_ON(void);


/*
Description:
Set PLL OFF

Return: Error status to make sure it is OFF
*/

RCC_tenuErrorStatus RCC_SetPLL_OFF(void);


/*
Description:
Select which clock as the system clock

Options:
CLK_HSI
CLK_HSE
CLK_PLL

Return: Error status to make sure it is Ready
*/

RCC_tenuErrorStatus RCC_SelectSystemClock(u8 CLK);

/*
Description:
Shows the current clock used as system clock

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

RCC_tenuErrorStatus RCC_GetSystemClock(u8 *Add_System_Clk_Status);



/*
Description:
Select the source for PLL

Options:
PLL_CLK_SRC_HSI
PLL_CLK_SRC_HSE

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

RCC_tenuErrorStatus RCC_SelectPllSource(u8 PLL_CLK_SRC);


/*
Description:
Configure PLL Parameters

options:

(for P variable)
RCC_enu_P_DivideBy2
RCC_enu_P_DivideBy4
RCC_enu_P_DivideBy6
RCC_enu_P_DivideBy8


(for M variable)
RCC_enu_M_DivideBy2
RCC_enu_M_DivideBy3
         ||
         ||
         ||
         \/
RCC_enu_M_DivideBy63


(for N variable)
RCC_enu_N_DivideBy192
RCC_enu_N_DivideBy193
         ||
         ||
         ||
         \/
RCC_enu_N_DivideBy432


Return: RCC_enuOK
 */
RCC_tenuErrorStatus RCC_PLL_Config(RCC_tenuPLLCfgN N, RCC_tenuPLLCfgM M, RCC_tenuPLLCfgP P);



/*
Description:
Enable the peripherals of a bus

Bus Options:
BUS_AHB1
BUS_AHB2
BUS_APB1
BUS_APB2

Peripheral Options:
(for AHB1 Bus)

GPIO_A
GPIO_B
GPIO_C
GPIO_D
GPIO_E
GPIO_H
CRC
DMA1
DMA2

(for AHB2 Bus)
OTGFS

(for APB1 Bus)
TIM2
TIM3
TIM4
TIM5
WWDG
SPI2
SPI3
USART2
I2C1
I2C2
I2C3
PWR

(for APB2 Bus)
TIM1
USART1
USART6
ADC1
SDIO
SPI1
SPI4
SYSCFG
TIM9
TIM10
TIM11


Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

RCC_tenuErrorStatus RCC_EnablePeri(u8 Bus, u8 Peri);



/*
Description:
Disable the peripherals of a bus

Bus Options:
BUS_AHB1
BUS_AHB2
BUS_APB1
BUS_APB2

Peripheral Options:
(for AHB1 Bus)

GPIO_A
GPIO_B
GPIO_C
GPIO_D
GPIO_E
GPIO_H
CRC
DMA1
DMA2

(for AHB2 Bus)
OTGFS

(for APB1 Bus)
TIM2
TIM3
TIM4
TIM5
WWDG
SPI2
SPI3
USART2
I2C1
I2C2
I2C3
PWR

(for APB2 Bus)
TIM1
USART1
USART6
ADC1
SDIO
SPI1
SPI4
SYSCFG
TIM9
TIM10
TIM11


Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

RCC_tenuErrorStatus RCC_DisablePeri(u8 Bus, u8 Peri);



/*
Description:
Choose the prescaler you want to configure and the value

PrescalerNum Options:
RTCPRE
PPRE2
PPRE1
HPRE

PresaclerVal Options :
PPRE1: APB low speed prescaler (APB1)
PPRE1_Div_2
PPRE1_Div_4
PPRE1_Div_8
PPRE1_Div_16

PPRE2: APB high speed prescaler (APB2)
PPRE2_Div_2
PPRE2_Div_4
PPRE2_Div_8
PPRE2_Div_16

HPRE: AHB prescalar
HPRE_Div_2
HPRE_Div_4
HPRE_Div_8
HPRE_Div_16
HPRE_Div_64
HPRE_Div_128
HPRE_Div_256
HPRE_Div_512

RTCPRE: HSE division factor for RTC clock
RTCPRE_Div_2
RTCPRE_Div_3
RTCPRE_Div_4
RTCPRE_Div_5
RTCPRE_Div_6
RTCPRE_Div_7
RTCPRE_Div_8
RTCPRE_Div_9
RTCPRE_Div_10
RTCPRE_Div_11
RTCPRE_Div_12
RTCPRE_Div_13
RTCPRE_Div_14
RTCPRE_Div_15
RTCPRE_Div_16
RTCPRE_Div_17
RTCPRE_Div_18
RTCPRE_Div_19
RTCPRE_Div_20
RTCPRE_Div_21
RTCPRE_Div_22
RTCPRE_Div_23
RTCPRE_Div_24
RTCPRE_Div_25
RTCPRE_Div_26
RTCPRE_Div_27
RTCPRE_Div_28
RTCPRE_Div_29
RTCPRE_Div_30
RTCPRE_Div_31

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

RCC_tenuErrorStatus RCC_PreScaler(u32 PrecsalerNum, u32 PrecsalerVal);

#endif /* RCC_H_ */
