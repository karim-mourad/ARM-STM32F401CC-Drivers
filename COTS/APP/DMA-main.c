#include <stdio.h>
#include <stdlib.h>
#include "SYSTICK.h"
#include "GPIO.h"
#include "RCC.h"
#include "LED.h"
#include "scheduler.h"
#include "UART.h"
#include "DMA.h"


u8 arr[2] = "AK";


u8 arr2[3];


void Tx_Finish(void)
{
	LED_Set_State(1, ON);
}


void Rx_Finish(void)
{
	//UART_SendAsynchZeroCpy(UART_1, arr2, 2,Tx_Finish);
	static u8 flag = 0;
	flag^=1;
	LED_Set_State(2, flag);
	UART_SendAsynchZeroCpy(UART_1, arr2, 3,Tx_Finish);
}

void UART_TAsk(void)
{

	if(get_status() == IDLE)
	{
		UART_ReceiveAsynchZeroCpy(UART_1, arr2, 2,Rx_Finish);
	}
}


UART_Cfg_t UART_Cfg =
{


			.Channel = UART_1,
			.DataLength = bits_8,
			.Parity_Control = PARITY_DISABLE,
			.Parity_Type = PARITY_ODD,
			.StopBits = STOP_bits_1,
			.OverSampling = OVERSAMPLING_16,
			.BaudRate = 9600,
			.UART_Pins =
			{
					.Tx =
					{
							.GPIO_PORT = GPIO_PORT_A,
							.GPIO_PIN = GPIO_PIN_9,
							.GPIO_MODE = GPIO_AF_PP,
							.GPIO_SPEED = GPIO_SPEED_VERY_HIGH
					},

					.Rx =
					{
							.GPIO_PORT = GPIO_PORT_A,
							.GPIO_PIN = GPIO_PIN_10,
							.GPIO_MODE = GPIO_AF_PP_PU,
							.GPIO_SPEED = GPIO_SPEED_VERY_HIGH
					}
			}


};


u8 source[4] = "Kimz";
u8 destination [4] = "Kimo";
u32 mem_add_1;

u8 x = 5;

u8 test_DMA_RX[4];


void DMA_RECEIVE_CBF(void)
{
	DMA_Start(DMA_2,DMA_Stream7);
}

void DMA_TRANSMIT_CBF(void)
{
	//DMA_Stop(DMA_2,DMA_Stream7);
}

DMA_Cfg_t DMA_UART1_TX_Cfg =
{
		.DMA = DMA_2,
		.Stream = DMA_Stream7,
		.Channel = DMA_Channel4,
		.Memory_Burst = single,
		.Peripheral_Burst = single,
		.DoubleBuffer = Disable,
		.Priority_Level = Very_High,
		.Memory_Size = byte,
		.Peripheral_Size = byte,
		.Memory_Auto_Increment = Enable,
		.Peripheral_Auto_Increment = Disable,
		.Circular_Mode = Disable,
		.Data_Direction = Mem_to_Per,
		.TC_Interrupt = Enable,
		.HTC_Interrupt = Disable,
		.Transfer_Error_Interrupt = Disable,
		.Direct_Mode_Error_Interrupt = Disable,
		.Data_Items = 4,
		.Peripheral_Address = 0x40011004,
		.Memory0_Address = &source,
		.Memory1_Address = NULL,
		.FIFO_Interrupt = Disable,
		.Direct_Mode = Direct_Enable,
		.FIFO_Threshold_Selection = Quarter_FIFO_Full,
		.CBF = DMA_TRANSMIT_CBF,
};


DMA_Cfg_t DMA_UART1_RX_Cfg =
{
		.DMA = DMA_2,
		.Stream = DMA_Stream5,
		.Channel = DMA_Channel4,
		.Memory_Burst = single,
		.Peripheral_Burst = single,
		.DoubleBuffer = Disable,
		.Priority_Level = Very_High,
		.Memory_Size = byte,
		.Peripheral_Size = byte,
		.Memory_Auto_Increment = Enable,
		.Peripheral_Auto_Increment = Disable,
		.Circular_Mode = Disable,
		.Data_Direction = Per_to_Mem,
		.TC_Interrupt = Enable,
		.HTC_Interrupt = Disable,
		.Transfer_Error_Interrupt = Disable,
		.Direct_Mode_Error_Interrupt = Disable,
		.Data_Items = 4,
		.Peripheral_Address = 0x40011004,
		.Memory0_Address = &test_DMA_RX,
		.Memory1_Address = NULL,
		.FIFO_Interrupt = Disable,
		.Direct_Mode = Direct_Enable,
		.FIFO_Threshold_Selection = Quarter_FIFO_Full,
		.CBF = DMA_RECEIVE_CBF,
};


int main()
{
	RCC_Set_HSI_ON();
	RCC_SelectSystemClock(CLK_HSI);
	RCC_EnablePeri(BUS_APB2,USART_1);
	RCC_EnablePeri(BUS_AHB1, GPIO_A);
	RCC_EnablePeri(BUS_AHB1, GPIO_C);
	RCC_EnablePeri(BUS_AHB1, DMA1);
	RCC_EnablePeri(BUS_AHB1, DMA2);
	LED_Init();
	UART_Init(&UART_Cfg);
	UART_DMA_MODE_ENABLE(UART_1);
	DMA_Init(&DMA_UART1_TX_Cfg);
	DMA_Init(&DMA_UART1_RX_Cfg);
	DMA_Start(DMA_2,DMA_Stream7);
//	UART_SendAsynchZeroCpy(UART_1, arr, 2,Tx_Finish);
//	UART_ReceiveAsynchZeroCpy(UART_1, arr2, 2,Rx_Finish);


	/*sched_init();
	sched_start();
*/

 while (1)
    {
		//UART_SendAsynchZeroCpy(UART_1, arr, 3,Tx_Finish);
		//UART_ReceiveAsynchZeroCpy(UART_1, arr2, 1,Rx_Finish);
	  //UART_ReceiveAsynchZeroCpy(UART_1, arr2, 3,Rx_Finish);
//	 DMA_Start(DMA_2,DMA_Stream5);

    }

}
