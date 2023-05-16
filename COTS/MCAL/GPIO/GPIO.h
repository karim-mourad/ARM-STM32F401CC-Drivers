/*
 * GPIO.h
 *
 *  Created on: 18 Feb 2023
 *      Author: HP
 */

#ifndef GPIO_H_
#define GPIO_H_

/*****************Includes*****************/
#include "Std_Types.h"


/*****************Defines*****************/

#define pin_no 16


/*The GPIO_PORT Cfg in the GPIO_Cfg_t struct*/
/*don't forget to cast it with the register struct in the implementation*/
#define GPIO_PORT_A     ((void*)0x40020000)
#define GPIO_PORT_B     ((void*)0x40020400)
#define GPIO_PORT_C     ((void*)0x40020800)
#define GPIO_PORT_D     ((void*)0x40020C00)
#define GPIO_PORT_E     ((void*)0x40021000)
#define GPIO_PORT_H     ((void*)0x40021C00)


/*The GPIO_PIN Cfg in the GPIO_Cfg_t struct*/
#define GPIO_PIN_0 		(0x00000001)
#define GPIO_PIN_1 		(0x00000002)
#define GPIO_PIN_2 		(0x00000004)
#define GPIO_PIN_3 		(0x00000008)
#define GPIO_PIN_4 		(0x00000010)
#define GPIO_PIN_5 		(0x00000020)
#define GPIO_PIN_6 		(0x00000040)
#define GPIO_PIN_7 		(0x00000080)
#define GPIO_PIN_8 		(0x00000100)
#define GPIO_PIN_9 		(0x00000200)
#define GPIO_PIN_10 	(0x00000400)
#define GPIO_PIN_11 	(0x00000800)
#define GPIO_PIN_12 	(0x00001000)
#define GPIO_PIN_13 	(0x00002000)
#define GPIO_PIN_14 	(0x00004000)
#define GPIO_PIN_15 	(0x00008000)


/*The GPIO_MODE Cfg in the GPIO_Cfg_t struct*/
/*OUTPUT's cfg*/
#define GPIO_OUTPUT_PP			(0b001000)
#define GPIO_OUTPUT_PP_PU		(0b001001)
#define GPIO_OUTPUT_PP_PD		(0b001010)
#define GPIO_OUTPUT_OD			(0b001100)
#define GPIO_OUTPUT_OD_PU		(0b001101)
#define GPIO_OUTPUT_OD_PD		(0b001110)

/*AF's cfg*/
#define GPIO_AF_PP				(0b010000)
#define GPIO_AF_PP_PU			(0b010001)
#define GPIO_AF_PP_PD			(0b010010)
#define GPIO_AF_OD				(0b010100)
#define GPIO_AF_OD_PU			(0b010101)
#define GPIO_AF_OD_PD 			(0b010110)

/*INPUT's cfg*/
#define GPIO_INPUT_FLOATING		(0b000000)
#define GPIO_INPUT_PU			(0b000001)
#define GPIO_INPUT_PD			(0b000010)


/*The GPIO_SPEED Cfg in the GPIO_Cfg_t struct*/
#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MEDIUM		1
#define GPIO_SPEED_HIGH			2
#define GPIO_SPEED_VERY_HIGH	3


#define GPIO_MODE_OTYPER_MASK		(0b000100)
#define GPIO_MODE_PUPDR_MASK		(0b000011)

#define GPIO_MODER_CLR_MASK			(0x3)
#define GPIO_OSPEEDR_CLR_MASK		(0x3)
#define GPIO_PUPDR_CLR_MASK			(0x3)

#define GPIO_SET_PIN_VALUE_LOW		0
#define GPIO_SET_PIN_VALUE_HIGH		1


/******************Types******************/

typedef enum
{
	GPIO_enuOK,
	GPIO_enuNOK,
	GPIO_enuInvalidGPIOPort,
	GPIO_enuInvalidPinNum,
	GPIO_enuInvalidAFNum

}GPIO_tenuErrorStatus;


typedef struct
{
	void * GPIO_PORT;
	u16 GPIO_PIN;
	u8 GPIO_MODE;
	u8 GPIO_SPEED;
}GPIO_Cfg_t;

/******************API's******************/


/*
Description:
Initializing the GPIO pin connected to the module with
the speed and the mode selected

Options:
Address of the object created from GPIO_Cfg_t struct

Return:
GPIO Error status
*/

GPIO_tenuErrorStatus GPIO_Init(GPIO_Cfg_t* Add_GPIO_Cfg);


/*
Description:
Set the GPIO Pins either LOW or HIGH

Options:
Add_GPIO_Cfg ==> Address of the object created from GPIO_Cfg_t struct
Cpy_var ==> GPIO_PIN_0
			GPIO_PIN_1
				||
				||
				\/
			GPIO_PIN_15
Pin_Value ==> GPIO_SET_PIN_VALUE_LOW or GPIO_SET_PIN_VALUE_HIGH

Return:
GPIO Error status
*/
GPIO_tenuErrorStatus GPIO_SetPins(GPIO_Cfg_t* Add_GPIO_Cfg, u16 Cpy_var, u8 Pin_Value);


/*
Description:
Set the GPIO Port either LOW or HIGH

Options:
Add_GPIO_Cfg ==> Address of the object created from GPIO_Cfg_t struct
Pin_Value ==> GPIO_SET_PIN_VALUE_LOW or GPIO_SET_PIN_VALUE_HIGH

Return:
GPIO Error status
*/

GPIO_tenuErrorStatus GPIO_SetPort(GPIO_Cfg_t* Add_GPIO_Cfg, u8 Pin_Value);

/*
Description:
Get the value of a GPIO Pin

Options:
Add_GPIO_Cfg ==> Address of the object created from GPIO_Cfg_t struct
Pin_No ==> 0-15
Cpy_var ==> address of a variable to carry the result

Return:
GPIO Error status
*/
GPIO_tenuErrorStatus GPIO_GetPin(GPIO_Cfg_t* Add_GPIO_Cfg, u8 Pin_No, u16 * Cpy_var);



/*
Description:
Get the value of a GPIO Port

Options:
Add_GPIO_Cfg ==> Address of the object created from GPIO_Cfg_t struct
Cpy_var ==> address of a variable to carry the result

Return:
GPIO Error status
*/
GPIO_tenuErrorStatus GPIO_GetPort(GPIO_Cfg_t* Add_GPIO_Cfg, u16 * Cpy_var);


/*
Description:
Set the specific AF of a GPIO

Options:
Add_GPIO_Cfg ==> Address of the object created from GPIO_Cfg_t struct
AF_no ==> the number of the required AF

Return:
GPIO Error status
*/
GPIO_tenuErrorStatus GPIO_SetAF(GPIO_Cfg_t* Add_GPIO_Cfg, u8 AF_no);


#endif /* GPIO_H_ */
