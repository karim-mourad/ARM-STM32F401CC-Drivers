/*
 * GPIO.c
 *
 *  Created on: 18 Feb 2023
 *      Author: HP
 */

#include "Std_Types.h"
#include "GPIO.h"

typedef struct
{
	u32 GPIO_MODER;
	u32 GPIO_OTYPER;
	u32 GPIO_OSPEEDR;
	u32 GPIO_PUPDR;
	u32 GPIO_IDR;
	u32 GPIO_ODR;
	u32 GPIO_BSRR;
	u32 GPIO_LCKR;
	u32 GPIO_AFRL;
	u32 GPIO_AFRH;

}GPIO_t;



GPIO_tenuErrorStatus GPIO_Init(GPIO_Cfg_t* Add_GPIO_Cfg)
{
	GPIO_tenuErrorStatus loc_Error_Status = GPIO_enuOK;
	if(Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_A && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_B && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_C
			&& Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_D && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_E &&
			Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_H)
	{
		loc_Error_Status = GPIO_enuInvalidGPIOPort;
	}
	else
	{
		GPIO_t * loc_GPIO = (GPIO_t*)(Add_GPIO_Cfg->GPIO_PORT);
		u8 loc_iterator = 0;
		u32 loc_buffer;
		u32 loc_temp = 0;
		u16 loc_pin_buffer = Add_GPIO_Cfg->GPIO_PIN;
		for(loc_iterator=0;loc_iterator<pin_no;loc_iterator++)
		{
			if(((loc_pin_buffer>>loc_iterator)&1) == 1)
			{
				/*MODER Cfg*/
				loc_temp = loc_GPIO->GPIO_MODER;
				loc_buffer = Add_GPIO_Cfg->GPIO_MODE;
				loc_temp &= ~(GPIO_MODER_CLR_MASK<<(loc_iterator*2)); //loc_iterator*2 because each pin has two bits for configuration
				loc_temp |= ((loc_buffer>>3)<<(loc_iterator*2));
				loc_GPIO->GPIO_MODER = loc_temp;

				/*OTYPER Cfg*/
				loc_temp = loc_GPIO->GPIO_OTYPER;
				loc_buffer = Add_GPIO_Cfg->GPIO_MODE;
				loc_temp &= ~(1<<(loc_iterator));
				loc_buffer = ((loc_buffer & GPIO_MODE_OTYPER_MASK) >> 2);
				loc_temp |= loc_buffer<<loc_iterator;
				loc_GPIO->GPIO_OTYPER = loc_temp;

				/*OTYPER Cfg*/
				loc_temp = loc_GPIO->GPIO_PUPDR;
				loc_buffer = Add_GPIO_Cfg->GPIO_MODE;
				loc_temp &= ~(GPIO_PUPDR_CLR_MASK<<(loc_iterator*2));
				loc_buffer = (loc_buffer & GPIO_MODE_PUPDR_MASK);
				loc_temp |= loc_buffer<<(loc_iterator*2);
				loc_GPIO->GPIO_PUPDR = loc_temp;

				/*OSPEEDR Cfg*/
				loc_temp = loc_GPIO->GPIO_OSPEEDR;
				loc_temp &= ~(3<<(loc_iterator*2));
				loc_temp |= ((Add_GPIO_Cfg->GPIO_SPEED)<<(loc_iterator*2));
				loc_GPIO->GPIO_OSPEEDR = loc_temp;
			}
		}
	}

	return loc_Error_Status;
}




GPIO_tenuErrorStatus GPIO_SetPins(GPIO_Cfg_t* Add_GPIO_Cfg, u16 Cpy_var, u8 Pin_Value)
{
	GPIO_t * loc_GPIO = (GPIO_t*)(Add_GPIO_Cfg->GPIO_PORT);
	GPIO_tenuErrorStatus loc_Error_Status = GPIO_enuOK;
	if(Cpy_var > 15)
	{
		loc_Error_Status = GPIO_enuInvalidPinNum;
	}

	if(Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_A && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_B && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_C
			&& Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_D && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_E &&
			Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_H)
	{
		loc_Error_Status = GPIO_enuInvalidGPIOPort;
	}


	switch(Pin_Value)
	{
	case GPIO_SET_PIN_VALUE_HIGH:
		loc_GPIO->GPIO_BSRR = Cpy_var; //0 -> 15
		break;

	case GPIO_SET_PIN_VALUE_LOW:
		loc_GPIO->GPIO_BSRR = Cpy_var<<16;
		break;
	}



	return loc_Error_Status;
}


GPIO_tenuErrorStatus GPIO_SetPort(GPIO_Cfg_t* Add_GPIO_Cfg, u8 Pin_Value)
{
	GPIO_t * loc_GPIO = (GPIO_t*)(Add_GPIO_Cfg->GPIO_PORT);
	GPIO_tenuErrorStatus loc_Error_Status = GPIO_enuOK;

	if(Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_A && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_B && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_C
			&& Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_D && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_E &&
			Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_H)
	{
		loc_Error_Status = GPIO_enuInvalidGPIOPort;
	}

	switch(Pin_Value)
	{
	case GPIO_SET_PIN_VALUE_HIGH:
		loc_GPIO->GPIO_BSRR = (0xFFFF);
		break;

	case GPIO_SET_PIN_VALUE_LOW:
		loc_GPIO->GPIO_BSRR = (0xFFFF)<<16;
		break;
	}



	return loc_Error_Status;
}


GPIO_tenuErrorStatus GPIO_GetPin(GPIO_Cfg_t* Add_GPIO_Cfg, u8 Pin_No, u16 * Cpy_var)
{
	GPIO_t * loc_GPIO = (GPIO_t*)(Add_GPIO_Cfg->GPIO_PORT);
	GPIO_tenuErrorStatus loc_Error_Status = GPIO_enuOK;
	if( Pin_No > 15)
	{
		loc_Error_Status = GPIO_enuInvalidPinNum;
	}

	if(Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_A && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_B && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_C
			&& Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_D && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_E &&
			Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_H)
	{
		loc_Error_Status = GPIO_enuInvalidGPIOPort;
	}

	* Cpy_var = ((loc_GPIO->GPIO_IDR >> Pin_No) & (0x00000001));

	return loc_Error_Status;
}


GPIO_tenuErrorStatus GPIO_GetPort(GPIO_Cfg_t* Add_GPIO_Cfg, u16 * Cpy_var)
{
	GPIO_t * loc_GPIO = (GPIO_t*)(Add_GPIO_Cfg->GPIO_PORT);
	GPIO_tenuErrorStatus loc_Error_Status = GPIO_enuOK;

	if(Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_A && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_B && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_C
			&& Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_D && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_E &&
			Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_H)
	{
		loc_Error_Status = GPIO_enuInvalidGPIOPort;
	}

	* Cpy_var = loc_GPIO->GPIO_IDR;

	return loc_Error_Status;
}

GPIO_tenuErrorStatus GPIO_SetAF(GPIO_Cfg_t* Add_GPIO_Cfg, u8 AF_no)
{
	GPIO_t * loc_GPIO = (GPIO_t*)(Add_GPIO_Cfg->GPIO_PORT);
	GPIO_tenuErrorStatus loc_Error_Status = GPIO_enuOK;
	u32 loc_temp;

	if(Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_A && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_B && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_C
			&& Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_D && Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_E &&
			Add_GPIO_Cfg->GPIO_PORT != GPIO_PORT_H)
	{
		loc_Error_Status = GPIO_enuInvalidGPIOPort;
	}

	if(AF_no > 15)
	{
		loc_Error_Status = GPIO_enuInvalidAFNum;
	}


	if(AF_no < 8)
	{
		loc_temp = loc_GPIO->GPIO_AFRL;
		loc_temp  &= ~(15<<4*AF_no);
		loc_temp  |= (AF_no<<(4*AF_no));
		loc_GPIO->GPIO_AFRL = loc_temp;
	}

	else if(AF_no >= 8  && AF_no<=15)
	{
		loc_temp = loc_GPIO->GPIO_AFRH;
		loc_temp  &= ~(15<<4*(AF_no-8));
		loc_temp  |= (AF_no<<(4*(AF_no-8)));
		loc_GPIO->GPIO_AFRH = loc_temp;
	}


	return loc_Error_Status;
}







