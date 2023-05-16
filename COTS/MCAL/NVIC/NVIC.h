
#ifndef NVIC_H_
#define NVIC_H_


/*****************Includes*****************/

#include "Std_Types.h"

/*****************Defines*****************/

/******  STM32 specific Interrupt Numbers **********************************************************************/
#define WWDG                       0      /*!< Window WatchDog Interrupt                                         */
#define PVD                        1      /*!< PVD through EXTI Line detection Interrupt                         */
#define TAMP_STAMP                 2      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
#define RTC_WKUP                   3      /*!< RTC Wakeup interrupt through the EXTI line                        */
#define FLASH                      4      /*!< FLASH global Interrupt                                            */
#define RCC                        5      /*!< RCC global Interrupt                                              */
#define EXTI0                      6      /*!< EXTI Line0 Interrupt                                              */
#define EXTI1                      7      /*!< EXTI Line1 Interrupt                                              */
#define EXTI2                      8      /*!< EXTI Line2 Interrupt                                              */
#define EXTI3                      9      /*!< EXTI Line3 Interrupt                                              */
#define EXTI4                      10     /*!< EXTI Line4 Interrupt                                              */
#define DMA1_Stream0               11     /*!< DMA1 Stream 0 global Interrupt                                    */
#define DMA1_Stream1               12     /*!< DMA1 Stream 1 global Interrupt                                    */
#define DMA1_Stream2               13     /*!< DMA1 Stream 2 global Interrupt                                    */
#define DMA1_Stream3               14     /*!< DMA1 Stream 3 global Interrupt                                    */
#define DMA1_Stream4               15     /*!< DMA1 Stream 4 global Interrupt                                    */
#define DMA1_Stream5               16     /*!< DMA1 Stream 5 global Interrupt                                    */
#define DMA1_Stream6               17     /*!< DMA1 Stream 6 global Interrupt                                    */
#define ADC                        18     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
#define EXTI9_5                    23     /*!< External Line[9:5] Interrupts                                     */
#define TIM1_BRK_TIM9              24     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
#define TIM1_UP_TIM10              25     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
#define TIM1_TRG_COM_TIM1          26     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
#define TIM1_CC                    27     /*!< TIM1 Capture Compare Interrupt                                    */
#define TIM2                       28     /*!< TIM2 global Interrupt                                             */
#define TIM3                       29     /*!< TIM3 global Interrupt                                             */
#define TIM4                       30     /*!< TIM4 global Interrupt                                             */
#define I2C1_EV                    31     /*!< I2C1 Event Interrupt                                              */
#define I2C1_ER                    32     /*!< I2C1 Error Interrupt                                              */
#define I2C2_EV                    33     /*!< I2C2 Event Interrupt                                              */
#define I2C2_ER                    34     /*!< I2C2 Error Interrupt                                              */
#define SPI1                       35     /*!< SPI1 global Interrupt                                             */
#define SPI2                       36     /*!< SPI2 global Interrupt                                             */
#define USART1                     37     /*!< USART1 global Interrupt                                           */
#define USART2                     38     /*!< USART2 global Interrupt                                           */
#define EXTI15_10                  40     /*!< External Line[15:10] Interrupts                                   */
#define RTC_Alarm                  41     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
#define OTG_FS_WKUP                42     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
#define DMA1_Stream7               47     /*!< DMA1 Stream7 Interrupt                                            */
#define SDIO                       49     /*!< SDIO global Interrupt                                             */
#define TIM5                       50     /*!< TIM5 global Interrupt                                             */
#define SPI3                       51     /*!< SPI3 global Interrupt                                             */
#define DMA2_Stream0               56     /*!< DMA2 Stream 0 global Interrupt                                    */
#define DMA2_Stream1               57     /*!< DMA2 Stream 1 global Interrupt                                    */
#define DMA2_Stream2               58     /*!< DMA2 Stream 2 global Interrupt                                    */
#define DMA2_Stream3               59     /*!< DMA2 Stream 3 global Interrupt                                    */
#define DMA2_Stream4               60     /*!< DMA2 Stream 4 global Interrupt                                    */
#define OTG_FS                     67     /*!< USB OTG FS global Interrupt                                       */
#define DMA2_Stream5               68     /*!< DMA2 Stream 5 global interrupt                                    */
#define DMA2_Stream6               69     /*!< DMA2 Stream 6 global interrupt                                    */
#define DMA2_Stream7               70     /*!< DMA2 Stream 7 global interrupt                                    */
#define USART6                     71     /*!< USART6 global interrupt                                           */
#define I2C3_EV                    72     /*!< I2C3 event interrupt                                              */
#define I2C3_ER                    73     /*!< I2C3 error interrupt                                              */
#define FPU                        81     /*!< FPU global interrupt                                             */
#define SPI4                       84     /*!< SPI4 global Interrupt                                            */


/*************SubGroup & Preemption bits*************/

#define NVIC_ALL_PREEMPTION  	                  (0x05FA0300)
#define NVIC_THREE_PREEMPTION_ONE_SUBGROUP    	  (0x05FA0400)
#define NVIC_TWO_PREEMPTION_TWO_SUBGROUP    	  (0x05FA0500)
#define NVIC_ONE_PREEMPTION_THREE_SUBGROUP    	  (0x05FA0600)
#define NVIC_ALL_SUBGROUP   	                  (0x05FA0700)








/******************Types******************/

typedef enum
{
	NVIC_enuOK = 0,
	NVIC_enuNOK,
	NVIC_enuInvalidInterruptNo,


}NVIC_tenuErrorStatus;


/******************API's******************/



/*
Description:
Select the desired interrupt to enable

Options:
0 -> 240 (check the above #define's)

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_EnableInterrupt(u8 Cpy_InterruptNO);





/*
Description:
Select the desired interrupt to disable

Options:
0 -> 240 (check the above #define's)

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_DisableInterrupt(u8 Cpy_InterruptNO);





/*
Description:
Select the desired interrupt to set it's pending flag

Options:
0 -> 240 (check the above #define's)

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_SetPendingFlag(u8 Cpy_InterruptNO);




/*
Description:
Select the desired interrupt to clear it's pending flag

Options:
0 -> 240 (check the above #define's)

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_ClearPendingFlag(u8 Cpy_InterruptNO);





/*
Description:
Select the desired interrupt to get it's pending flag status

Options:
Cpy_InterruptNO ===>  0 -> 240 (check the above #define's)
Cpy_Val ===> address of a variable to store the result in it

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_GetPendingFlag(u8 Cpy_InterruptNO, u8 * Cpy_Val);






/*
Description:
Select the desired interrupt to get it's Active status

Options:
Cpy_InterruptNO ===>  0 -> 240 (check the above #define's)
Cpy_Val ===> address of a variable to store the result in it

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_GetActiveInterrupt(u8 Cpy_InterruptNO, u8 * Cpy_Val);




/*
Description:
Select the desired interrupt to generate SW interrupt

Options:
Cpy_InterruptNO ===>  0 -> 240 (check the above #define's)

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_TriggerSWInterrupt(u8 Cpy_InterruptNO);





/*
Description:
Select the no of bits required to set as subgroup priority

Options:
NVIC_ALL_PREEMPTION
NVIC_THREE_PREEMPTION_ONE_SUBGROUP
NVIC_TWO_PREEMPTION_TWO_SUBGROUP
NVIC_ONE_PREEMPTION_THREE_SUBGROUP
NVIC_ALL_SUBGROUP

Return: Error status to make sure it done it's job correctly
(OK or NOK)
*/

NVIC_tenuErrorStatus NVIC_SetSysSubGroup(u32 Cpy_SubGroupBits);






NVIC_tenuErrorStatus NVIC_SetPriority(u8 Cpy_InterruptNo, u8 CpyPreemptionNo, u8 Cpy_SubgroupNo);





#endif /* NVIC_H_ */
