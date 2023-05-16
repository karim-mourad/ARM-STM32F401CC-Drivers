#include "UART.h"

#define TX_Enable	0x00000008
#define RX_Enable	0x00000004

#define UART_ENABLE 0x00002000

#define TX_COMPLETE_INTERRUPT_ENABLE 0x00000040
#define RX_COMPLETE_INTERRUPT_ENABLE 0x00000020

#define MANTESSA_POS  4
#define FRACTIO_MASK 0x0F
/*
#define IDLE 0
#define BUSY 1
#define NOT_INIT 2
*/

/*Global variables for sending*/
static u8 Tx_State[3] = {NOT_INIT,NOT_INIT,NOT_INIT};
static u8 * Tx_Buffer[3] = {NULL,NULL,NULL};
static u32 Tx_Size[3] = {0,0,0};
static u32 Tx_Idx[3] = {0,0,0};
static CBF_t Tx_CBF[3] = {NULL,NULL,NULL};


/*Global variables for recieveing*/
static u8 Rx_State[3] = {NOT_INIT,NOT_INIT,NOT_INIT};
static u8 * Rx_Buffer[3] = {NULL,NULL,NULL};
static u32 Rx_Size[3] = {0,0,0};
static u32 Rx_Idx[3] = {0,0,0};
static CBF_t Rx_CBF[3] = {NULL,NULL,NULL};

typedef struct
{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}UART_T;


volatile UART_T * const UART[3] =
{
		[UART_1] = ((volatile UART_T * ) 0x40011000),
		[UART_2] = ((volatile UART_T * ) 0x40004400),
		[UART_6] = ((volatile UART_T * ) 0x40011400)
};




/***********************Static Functions***********************/
static void BaudRateCalc(UART_Cfg_t * Cpy_UART)
{
	f32 UART_DIV = 0;
	u32 Mantessa_part = 0;
	u32 Fraction_part = 0;
	u8 OVER8_bit = 0;

	u32 loc_temp = Cpy_UART->OverSampling;
	if(loc_temp == OVERSAMPLING_16)
	{
		OVER8_bit = 0;
	}

	else if(loc_temp == OVERSAMPLING_8)
	{
		OVER8_bit = 1;
	}

	UART_DIV = ((f32)(F_CPU))/(f32)((8*(2-OVER8_bit)*Cpy_UART->BaudRate));

	Mantessa_part = (u32)UART_DIV;

	if(loc_temp == OVERSAMPLING_16)
	{
		Fraction_part = (UART_DIV - Mantessa_part) * 16;
	}

	else if (loc_temp == OVERSAMPLING_8)
	{
		Fraction_part = (UART_DIV - Mantessa_part) * 8;
	}


	UART[Cpy_UART->Channel]->BRR|= (Mantessa_part << MANTESSA_POS) | (Fraction_part & FRACTIO_MASK);


}




static void UART_HANDLER(UART_CHANNELS_t Cpy_Channel)
{
	if(((UART[Cpy_Channel]->SR >> 6) & 0x1) && (Tx_State[Cpy_Channel] == BUSY))
	{
		if(Tx_Idx[Cpy_Channel] < Tx_Size[Cpy_Channel])
		{
			UART[Cpy_Channel]->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];
			Tx_Idx[Cpy_Channel]++;
		}
		else
		{
			Tx_State[Cpy_Channel] = IDLE;
			UART[Cpy_Channel]->CR1 &= ~(TX_COMPLETE_INTERRUPT_ENABLE);
			if(Tx_CBF[Cpy_Channel])
			{
				Tx_CBF[Cpy_Channel]();
			}

		}

	}



	//if(((UART[Cpy_Channel]->SR >> 5) & 0x1) && )
	//else if((Rx_State[Cpy_Channel] == BUSY))
	if(((UART[Cpy_Channel]->SR >> 5) & 0x1) && (Rx_State[Cpy_Channel] == BUSY))
	{
		if(Rx_Idx[Cpy_Channel] < (Rx_Size[Cpy_Channel]))
		{
			Rx_Buffer[Cpy_Channel][Rx_Idx[Cpy_Channel]] = (u8)UART[Cpy_Channel]->DR;
			Rx_Idx[Cpy_Channel]++;
		}
		if(Rx_Idx[Cpy_Channel] == (Rx_Size[Cpy_Channel]))
		{
			Rx_State[Cpy_Channel] = IDLE;
			UART[Cpy_Channel]->CR1 &= ~(RX_COMPLETE_INTERRUPT_ENABLE);
			if(Rx_CBF[Cpy_Channel])
			{
				Rx_CBF[Cpy_Channel]();
			}

		}

	}
}

/***********************API's***********************/

UART_tenuErrorStatus UART_Init(UART_Cfg_t * Cpy_UART)
{
	u8 loc_Error_Status = UART_enuOK;
	u32 loc_temp;

		/*Set AF from Channel number*/

		if(Cpy_UART->Channel == UART_1 || Cpy_UART->Channel == UART_2)
		{
			GPIO_SetAFPORT(Cpy_UART->UART_Pins.Tx.GPIO_PORT,Cpy_UART->UART_Pins.Tx.GPIO_PIN,7);
			GPIO_SetAFPORT(Cpy_UART->UART_Pins.Rx.GPIO_PORT,Cpy_UART->UART_Pins.Rx.GPIO_PIN,7);
		}


		else if(Cpy_UART->Channel == UART_6)
		{
			GPIO_SetAFPORT(Cpy_UART->UART_Pins.Tx.GPIO_PORT,Cpy_UART->UART_Pins.Tx.GPIO_PIN,8);
			GPIO_SetAFPORT(Cpy_UART->UART_Pins.Rx.GPIO_PORT,Cpy_UART->UART_Pins.Rx.GPIO_PIN,8);
		}

		//GPIO_Init(GPIO_Cfg_t* Add_GPIO_Cfg);
		GPIO_Init(&Cpy_UART->UART_Pins.Tx);
		GPIO_Init(&Cpy_UART->UART_Pins.Rx);



		/*Enbale TX*/
		UART[Cpy_UART->Channel]->CR1 |= TX_Enable;

		/*Enbale RX*/
		UART[Cpy_UART->Channel]->CR1 |= RX_Enable;

		/*User Configuration*/

		/*Data Length*/
		loc_temp = UART[Cpy_UART->Channel]->CR1;
		loc_temp &= bits_CLR_MASK;
		loc_temp |= Cpy_UART->DataLength;
		UART[Cpy_UART->Channel]->CR1 = loc_temp;

		/*Parity Control*/
		loc_temp = UART[Cpy_UART->Channel]->CR1;
		loc_temp &= PARITY_CONTROL_CLR_MASK;
		loc_temp |= Cpy_UART->Parity_Control;
		UART[Cpy_UART->Channel]->CR1 = loc_temp;

		/*Parity Type*/
		loc_temp = UART[Cpy_UART->Channel]->CR1;
		loc_temp &= PARITY_TYPE_CLR_MASK;
		loc_temp |= Cpy_UART->Parity_Type;
		UART[Cpy_UART->Channel]->CR1 = loc_temp;

		/*Stop Bits*/
		loc_temp = UART[Cpy_UART->Channel]->CR2;
		loc_temp &= STOP_bits_CLR_MASK;
		loc_temp |= Cpy_UART->StopBits;
		UART[Cpy_UART->Channel]->CR2 = loc_temp;

		/*Oversampling*/
		loc_temp = UART[Cpy_UART->Channel]->CR1;
		loc_temp &= OVERSAMPLING_CLR_MASK;
		loc_temp |= Cpy_UART->OverSampling;
		UART[Cpy_UART->Channel]->CR1 = loc_temp;

		/*Baud Rate*/
		BaudRateCalc(Cpy_UART);

		/*Enable UART*/
		UART[Cpy_UART->Channel]->CR1 |= UART_ENABLE;

		/*Enabling UART Interrupts*/
		NVIC_EnableInterrupt(USART1);
		NVIC_EnableInterrupt(USART2);
		NVIC_EnableInterrupt(USART6);


		/*State is idle at initialization*/
		Tx_State[Cpy_UART->Channel] = IDLE;
		Rx_State[Cpy_UART->Channel] = IDLE;

		/*test*/
		UART[Cpy_UART->Channel]->SR = 0;




	return loc_Error_Status;
}



UART_tenuErrorStatus UART_SendAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, CBF_t Cpy_CBF)
{
	u8 loc_Error_Status = UART_enuOK;
	if(Tx_State[Cpy_Channel] == IDLE)
	{
		Tx_State[Cpy_Channel] = BUSY;
		Tx_Buffer[Cpy_Channel] = buffer;
		Tx_Size[Cpy_Channel] = size;
		Tx_Idx[Cpy_Channel] = 0;
		Tx_CBF[Cpy_Channel] = Cpy_CBF;


		UART[Cpy_Channel]->DR = Tx_Buffer[Cpy_Channel][Tx_Idx[Cpy_Channel]];

		UART[Cpy_Channel]->CR1 |= TX_COMPLETE_INTERRUPT_ENABLE;

		Tx_Idx[Cpy_Channel]++;



	}



	return loc_Error_Status;
}



UART_tenuErrorStatus UART_ReceiveAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, CBF_t Cpy_CBF)
{
	u8 loc_Error_Status = UART_enuOK;
	if(Rx_State[Cpy_Channel] == IDLE)
	{

		Rx_Buffer[Cpy_Channel] = buffer;
		Rx_Size[Cpy_Channel] = size;
		Rx_Idx[Cpy_Channel] = 0;
		Rx_State[Cpy_Channel] = BUSY;
		Rx_CBF[Cpy_Channel] = Cpy_CBF;


		UART[Cpy_Channel]->CR1 |= RX_COMPLETE_INTERRUPT_ENABLE;


	}
	else
	{
		loc_Error_Status = UART_enuBusy;
	}



	return loc_Error_Status;
}

u8 get_status(void)
{
	return Rx_State[0];
}

/***********************Handler's***********************/
void USART1_IRQHandler(void)
{
	UART_HANDLER(UART_1);
}

void USART2_IRQHandler(void)
{
	UART_HANDLER(UART_2);
}

void USART6_IRQHandler(void)
{
	UART_HANDLER(UART_6);
}






