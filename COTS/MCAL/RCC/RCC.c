/*
 * RCC.c
 *
 *  Created on: 22 Feb 2023
 *      Author: HP
 */

#include "RCC.h"


typedef struct {
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 reserved1;
	u32 reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 reserved3;
	u32 reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 reserved5;
	u32 reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 reserved7;
	u32 reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 reserved9;
	u32 reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 reserved11;
	u32 reserved12;
	u32 BDCR;
	u32 CSR;
	u32 reserved13;
	u32 reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 reserved15;
	u32 DCKCFGR;
}RCC_t;

RCC_t * const RCC = ((RCC_t *)0x40023800);


RCC_tenuErrorStatus RCC_Set_HSI_ON(void)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuClockON;
	u16 counter = 0;
	u32 loc_temp = RCC->CR;
	loc_temp |= 1<<0;
	while((counter<RCC_sysCLK_Rdy_TimeOut) && (((loc_temp>>1) & 1)==0))
	{
		counter++;
	}

	if (counter == RCC_sysCLK_Rdy_TimeOut)
	{
		loc_Error_Status = RCC_enuClockOFF;
	}

	RCC->CR = loc_temp;

	return loc_Error_Status;

}



RCC_tenuErrorStatus RCC_SetHSI_OFF(void)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuClockOFF;
	u16 counter = 0;
	u32 loc_temp = RCC->CR;
	loc_temp &= ~(1<<0);
	while((counter<RCC_sysCLK_Rdy_TimeOut) && (((loc_temp>>1) & 1)==1))
	{
		counter++;
	}

	if (counter == RCC_sysCLK_Rdy_TimeOut)
	{
		loc_Error_Status = RCC_enuClockON;
	}

	RCC->CR = loc_temp;

	return loc_Error_Status;

}



RCC_tenuErrorStatus RCC_SetHSE_ON(u8 HSE_STATE)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuClockON;
	u16 counter = 0;
	u32 loc_temp = RCC->CR;
	loc_temp &= ~(1<<18);
	loc_temp |= (HSE_STATE<<18);
	loc_temp |= (1<<16);
	/*while((counter<RCC_sysCLK_Rdy_TimeOut) && (((loc_temp>>17) & 1)==0))
	{
		counter++;
	}*/

	/*if (counter == RCC_sysCLK_Rdy_TimeOut)
	{
		loc_Error_Status = RCC_enuClockOFF;
	}*/

	RCC->CR = loc_temp;

	return loc_Error_Status;
}


RCC_tenuErrorStatus RCC_SetHSE_OFF(void)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuClockOFF;
	u16 counter = 0;
	u32 loc_temp = RCC->CR;
	loc_temp &= ~(1<<16);
	while((counter<RCC_sysCLK_Rdy_TimeOut) && (((loc_temp>>17) & 1)==1))
	{
		counter++;
	}

	if (counter == RCC_sysCLK_Rdy_TimeOut)
	{
		loc_Error_Status = RCC_enuClockON;
	}

	RCC->CR = loc_temp;

	return loc_Error_Status;
}



RCC_tenuErrorStatus RCC_SetPLL_ON(void)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuClockON;
	u16 counter = 0;
	u32 loc_temp = RCC->CR;
	loc_temp |= 1<<24;
	/*while((counter<RCC_sysCLK_Rdy_TimeOut) && (((loc_temp>>25) & 1)==0))
	{
		counter++;
	}

	if (counter == RCC_sysCLK_Rdy_TimeOut)
	{
		loc_Error_Status = RCC_enuClockOFF;
	}
	*/

	RCC->CR = loc_temp;

	return loc_Error_Status;
}


RCC_tenuErrorStatus RCC_SetPLL_OFF(void)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuClockOFF;
	u16 counter = 0;
	u32 loc_temp = RCC->CR;
	loc_temp &= ~(1<<24);
	while((counter<RCC_sysCLK_Rdy_TimeOut) && (((loc_temp>>25) & 1)==1))
	{
		counter++;
	}

	if (counter == RCC_sysCLK_Rdy_TimeOut)
	{
		loc_Error_Status = RCC_enuClockON;
	}

	RCC->CR = loc_temp;

	return loc_Error_Status;

}


RCC_tenuErrorStatus RCC_SelectSystemClock(u8 CLK)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuClockRdy;
	u32 loc_temp = RCC->CFGR;

	switch(CLK)
	{
	case CLK_HSI:
			if(((RCC->CR >> 1) & 1) == 0)
			{
				loc_Error_Status = RCC_enuClockNotRdy;
			}
			else
			{
				loc_temp &= SELECT_SYS_CLK_CLR_MASK;
				loc_temp |= SELECT_SYS_CLK_HSI;
			}
			break;

	case CLK_HSE:
			if(((RCC->CR >> 17) & 1) == 0)
			{
				loc_Error_Status = RCC_enuClockNotRdy;
			}
			else
			{
				loc_temp &= SELECT_SYS_CLK_CLR_MASK;
				loc_temp |= SELECT_SYS_CLK_HSE;
			}
			break;

	case CLK_PLL:
			if(((RCC->CR>>25) & 1) == 0)
			{
				loc_Error_Status = RCC_enuClockNotRdy;
			}
			else
			{
				loc_temp &= SELECT_SYS_CLK_CLR_MASK;
				loc_temp |= SELECT_SYS_CLK_PLL;
			}
			break;
	default:
		loc_Error_Status = RCC_enuInvalidSysCLK;
	}

	RCC->CFGR = loc_temp;

	return loc_Error_Status;
}


RCC_tenuErrorStatus RCC_GetSystemClock(u8 *Add_System_Clk_Status)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuOK;
	u32 loc_temp = RCC->CFGR;
	loc_temp &= GET_SYS_CLK_MASK;
	loc_temp = loc_temp>>2;

	if(loc_temp == CLK_HSI)
	{
		*Add_System_Clk_Status = CLK_HSI;
	}

	else if(loc_temp == CLK_HSE)
	{
		*Add_System_Clk_Status = CLK_HSI;
	}

	else if(loc_temp == CLK_PLL)
	{
		*Add_System_Clk_Status = CLK_PLL;
	}

	else
	{
		loc_Error_Status = RCC_enuNOK;
	}


	return loc_Error_Status;
}


RCC_tenuErrorStatus RCC_SelectPllSource(u8 PLL_CLK_SRC)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuOK;
	u32 loc_temp = RCC->PLLCFGR;
	loc_temp &= ~(1<<22);

	if(PLL_CLK_SRC == PLL_CLK_SRC_HSI)
	{
		if(((RCC->CR>>1) & 1) == 1)
		{
			loc_temp|= (PLL_CLK_SRC<<22);
		}

		else
		{
			loc_Error_Status = RCC_enuClockNotRdy;
		}

	}

	else if(PLL_CLK_SRC == PLL_CLK_SRC_HSE)
	{
		if(((RCC->CR>>17) & 1) == 1)
		{
			loc_temp|= (PLL_CLK_SRC<<22);
		}

		else
		{
			loc_Error_Status = RCC_enuClockNotRdy;
		}
	}

	else
	{
		loc_Error_Status = RCC_enuInvalidPLLSRC;
	}

	RCC->PLLCFGR = loc_temp ;
	return loc_Error_Status;
}


RCC_tenuErrorStatus RCC_PLL_Config(RCC_tenuPLLCfgN N, RCC_tenuPLLCfgM M, RCC_tenuPLLCfgP P)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuOK;
	u32 loc_temp = RCC->PLLCFGR;
	if(P<0 || P>3)
	{
		loc_Error_Status = RCC_enuInvalidPLLCFG_P;
	}

	else
	{
		loc_temp &= PLL_CFG_P_CLR_MASK;
		loc_temp |= (P<<16);
		RCC->PLLCFGR = loc_temp;
	}


	if( M<2 || M>63)
	{
		loc_Error_Status = RCC_enuInvalidPLLCFG_M;
	}

	else
	{
		loc_temp &= PLL_CFG_M_CLR_MASK;
		loc_temp |= M;
		RCC->PLLCFGR = loc_temp;
	}

	if( N<192 || N>432)
	{
		loc_Error_Status = RCC_enuInvalidPLLCFG_N;
	}

	else
	{
		loc_temp &= PLL_CFG_N_CLR_MASK;
		loc_temp |= (N<<6);
		RCC->PLLCFGR = loc_temp;
	}

	return loc_Error_Status;
}


RCC_tenuErrorStatus RCC_EnablePeri(u8 Bus, u8 Peri)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuOK;
	u32 loc_temp_AHB1 = RCC->AHB1ENR;
	u32 loc_temp_AHB2 = RCC->AHB2ENR;
	u32 loc_temp_APB1 = RCC->APB1ENR;
	u32 loc_temp_APB2 = RCC->APB2ENR;
	switch(Bus)
	{
	case BUS_AHB1:

		switch(Peri)
		{

		case GPIO_A:

			loc_temp_AHB1  |= (1<<Peri);

			break;

		case GPIO_B:

			loc_temp_AHB1  |= (1<<Peri);

			break;

		case GPIO_C:


			loc_temp_AHB1  |= (1<<Peri);

			break;

		case GPIO_D:

			loc_temp_AHB1 |= (1<<Peri);

			break;

		case GPIO_E:

			loc_temp_AHB1  |= (1<<Peri);

			break;

		case GPIO_H:

			loc_temp_AHB1 |= (1<<Peri);

			break;

		case CRC:

			loc_temp_AHB1 |= (1<<Peri);

			break;

		case DMA1:

			loc_temp_AHB1  |= (1<<Peri);

			break;

		case DMA2:

			loc_temp_AHB1  |= (1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;
		}
		break;

	case BUS_AHB2:
		switch(Peri)
		{
		case OTGFS:

			loc_temp_AHB2  |= (1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;

		}

		break;

	case BUS_APB1:

		switch(Peri)
		{

		case TIM2:

			loc_temp_APB1  |= (1<<Peri);

			break;

		case TIM3:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case TIM4:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case TIM5:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case WWDG:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case SPI2:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case SPI3:

			loc_temp_APB1  |= (1<<Peri);

			break;

		case USART2:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case I2C1:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case I2C2:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case I2C3:

			loc_temp_APB1   |= (1<<Peri);

			break;

		case PWR:

			loc_temp_APB1   |= (1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;
		}

		break;

	case BUS_APB2:

		switch(Peri)
		{

		case TIM1:

			loc_temp_APB2 |= (1<<Peri);

			break;

		case USART1:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case USART6:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case ADC1:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case SDIO:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case SPI1:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case SPI4:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case SYSCFG:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case TIM9:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case TIM10:

			loc_temp_APB2  |= (1<<Peri);

			break;

		case TIM11:

			loc_temp_APB2  |= (1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;
		}

		break;
	default:
		loc_Error_Status = RCC_enuInvalidBus;
		break;
	}


	RCC->AHB1ENR = loc_temp_AHB1;
	RCC->AHB2ENR = loc_temp_AHB2;
	RCC->APB1ENR = loc_temp_APB1;
	RCC->APB2ENR = loc_temp_APB2;

	return loc_Error_Status;
}


RCC_tenuErrorStatus RCC_DisablePeri(u8 Bus, u8 Peri)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuOK;
	u32 loc_temp_AHB1 = RCC->AHB1ENR;
	u32 loc_temp_AHB2 = RCC->AHB2ENR;
	u32 loc_temp_APB1 = RCC->APB1ENR;
	u32 loc_temp_APB2 = RCC->APB2ENR;
	switch(Bus)
	{
	case BUS_AHB1:

		switch(Peri)
		{

		case GPIO_A:

			loc_temp_AHB1  &= ~(1<<Peri);

			break;

		case GPIO_B:

			loc_temp_AHB1  &= ~(1<<Peri);

			break;

		case GPIO_C:


			loc_temp_AHB1  &= ~(1<<Peri);

			break;

		case GPIO_D:

			loc_temp_AHB1 &= ~(1<<Peri);

			break;

		case GPIO_E:

			loc_temp_AHB1 &= ~(1<<Peri);

			break;

		case GPIO_H:

			loc_temp_AHB1 &= ~(1<<Peri);

			break;

		case CRC:

			loc_temp_AHB1 &= ~(1<<Peri);

			break;

		case DMA1:

			loc_temp_AHB1 &= ~(1<<Peri);

			break;

		case DMA2:

			loc_temp_AHB1 &= ~(1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;
		}
		break;

	case BUS_AHB2:
		switch(Peri)
		{
		case OTGFS:

			loc_temp_AHB2  &= ~(1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;

		}

		break;

	case BUS_APB1:

		switch(Peri)
		{

		case TIM2:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case TIM3:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case TIM4:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case TIM5:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case WWDG:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case SPI2:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case SPI3:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case USART2:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case I2C1:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case I2C2:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case I2C3:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		case PWR:

			loc_temp_APB1 &= ~(1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;
		}

		break;

	case BUS_APB2:

		switch(Peri)
		{

		case TIM1:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case USART1:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case USART6:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case ADC1:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case SDIO:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case SPI1:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case SPI4:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case SYSCFG:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case TIM9:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case TIM10:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		case TIM11:

			loc_temp_APB2 &= ~(1<<Peri);

			break;

		default:

			loc_Error_Status = RCC_enuInvalidPeri;
			break;
		}

		break;
	default:
		loc_Error_Status = RCC_enuInvalidBus;
		break;
	}


	RCC->AHB1ENR = loc_temp_AHB1;
	RCC->AHB2ENR = loc_temp_AHB2;
	RCC->APB1ENR = loc_temp_APB1;
	RCC->APB2ENR = loc_temp_APB2;

	return loc_Error_Status;
}

RCC_tenuErrorStatus RCC_PreScaler(u32 PrecsalerNum, u32 PrecsalerVal)
{
	RCC_tenuErrorStatus loc_Error_Status = RCC_enuOK;
	u32 loc_temp = RCC->CFGR;
	switch(PrecsalerNum)
	{
	case RTCPRE:
		loc_temp &= RTCPRE_CLR_MASK;
		loc_temp |= PrecsalerVal;
		break;

	case PPRE2:
		loc_temp &= PPRE2_CLR_MASK;
		loc_temp |= PrecsalerVal;
		break;

	case PPRE1:
		loc_temp &= PPRE1_CLR_MASK;
		loc_temp |= PrecsalerVal;
		break;

	case HPRE:
		loc_temp &= HPRE_CLR_MASK;
		loc_temp |= PrecsalerVal;
		break;


	default:
		loc_Error_Status = RCC_enuInvalidPrescaler;
		break;
	}

	RCC->CFGR = loc_temp;
	return loc_Error_Status;
}
