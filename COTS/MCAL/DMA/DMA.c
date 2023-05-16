#include "DMA.h"


/*******Defines*******/

#define STREAM_DISABLE 0xFFFFFFFE
#define STREAM_ENABLE  0x00000001

#define CHANNEL_CLEAR  0xF1FFFFFF

#define MEMORY_BURST_CLEAR 0xFE7FFFFF

#define PERIPHERAL_BURST_CLEAR 0xFF9FFFFF

#define DOUBLE_BUFFER_MODE_CLEAR 0xFFFBFFFF

#define PRIORITY_LEVEL_CLEAR 0xFFFCFFFF

#define MEMORY_SIZE_CLEAR 0xFFFF9FFF

#define PERIPHERAL_SIZE_CLEAR 0xFFFFE7FF

#define MEMORY_AUTO_INC_CLEAR 0xFFFFFBFF

#define PERIPHERAL_AUTO_INC_CLEAR 0xFFFFFDFF

#define CIRCULAR_MODE_CLEAR 0xFFFFFEFF

#define DATA_DIRECTION_CLEAR 0xFFFFFF3F

#define TC_INTERRUPT_CLEAR 0xFFFFFFEF
#define HTC_INTERRUPT_CLEAR 0xFFFFFFF7
#define TRANSFER_ERROR_INTERRUPT_CLEAR 0xFFFFFFFB
#define DIRECT_MODE_ERROR_INTERRUPT_CLEAR 0xFFFFFFFD

#define DATA_ITEMS_CLEAR 0xFFFF0000

#define FIFO_INTERRUPT_CLEAR 0xFFFFFF7F

#define DIRECT_MODE_CLEAR 0xFFFFFFFB

#define FIFO_THRESHOLD_SELECTION_CLEAR 0xFFFFFFFC


/*******INTERRUPTS CLEAR FOR ENABLE*******/
#define STREAM0_INT_CLEAR 0x0000003D
#define STREAM1_INT_CLEAR 0x00000F40
#define STREAM2_INT_CLEAR 0x003D0000
#define STREAM3_INT_CLEAR 0x0F400000

#define STREAM4_INT_CLEAR 0x0000003D
#define STREAM5_INT_CLEAR 0x00000F40
#define STREAM6_INT_CLEAR 0x003D0000
#define STREAM7_INT_CLEAR 0x0F400000

/*********************/

typedef struct
{
	u32 LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;

	struct
	{
		u32 SxCR;
		u32 SxNDTR;
		u32 SxPAR;
		u32 SxM0AR;
		u32 SxM1AR;
		u32 SxFCR;

	}Cfg_Reg[8];

}DMA_t;


volatile DMA_t * const DMA[2] =
{
		[DMA_1] = ((volatile DMA_t *) 0x40026000),
		[DMA_2] = ((volatile DMA_t *) 0x40026400)
};

static DMA_CBF_t DMA_CBF[2][8] = {{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}}; //2 DMA, 8 Streams
static u8 DMA_NVIC_INT[2][8] = {{11,12,13,14,15,16,17,47},{56,57,58,59,60,68,69,70}};
/******************API's******************/

DMA_tenuErrorStatus DMA_Init(const DMA_Cfg_t * Cpy_Ptr)
{

	DMA_tenuErrorStatus Loc_Error_Status = DMA_enuOK;
	/*Make sure DMA EN = 0*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= STREAM_DISABLE;

	/*Select the Channel of the stream*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= CHANNEL_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Channel << 25;

	/*Memory Burst*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= MEMORY_BURST_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Memory_Burst << 23;

	/*Peripheral Burst*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= PERIPHERAL_BURST_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Peripheral_Burst << 21;

	/*Double Buffer*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= DOUBLE_BUFFER_MODE_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->DoubleBuffer << 18;

	/*Priority level*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= PRIORITY_LEVEL_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Priority_Level << 16;

	/*Memory Size*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= MEMORY_SIZE_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Memory_Size << 13;

	/*Peripheral Size*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= PERIPHERAL_SIZE_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Peripheral_Size << 11;

	/*Memory Auto Increment*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= MEMORY_AUTO_INC_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Memory_Auto_Increment << 10;

	/*Peipheral Auto Increment*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= PERIPHERAL_AUTO_INC_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Peripheral_Auto_Increment << 9;

	/*Circular Mode*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= CIRCULAR_MODE_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Circular_Mode << 8;

	/*Data Direction*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= DATA_DIRECTION_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Data_Direction << 6;

	/*TC Interrupt*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= TC_INTERRUPT_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->TC_Interrupt << 4;

	/*HTC Interrupt*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= HTC_INTERRUPT_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->HTC_Interrupt << 3;

	/*Transfer Error Interrupt*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= TRANSFER_ERROR_INTERRUPT_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Transfer_Error_Interrupt << 2;

	/*Direct Mode Error Interrupt*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR &= DIRECT_MODE_ERROR_INTERRUPT_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxCR |= Cpy_Ptr->Direct_Mode_Error_Interrupt << 1;

	/*Data Items*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxNDTR &= DATA_ITEMS_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxNDTR |= Cpy_Ptr->Data_Items;

	/*Peripheral Address*/
	if(Cpy_Ptr->Peripheral_Address != NULL)
	{
		DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxPAR = 0;
		DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxPAR = Cpy_Ptr->Peripheral_Address;
	}

	/*Memory 0 Address*/
	if(Cpy_Ptr->Memory0_Address != NULL)
	{
		DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxM0AR = 0;
		DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxM0AR = Cpy_Ptr->Memory0_Address;
	}

	/*Memory 1 Address*/
	if(Cpy_Ptr->Memory1_Address != NULL)
	{
		DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxM1AR = 0;
		DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxM1AR = Cpy_Ptr->Memory1_Address;
	}

	/*FIFO Interrupt*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxFCR &= FIFO_INTERRUPT_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxFCR |= Cpy_Ptr->FIFO_Interrupt << 7;

	/*Direct Mode*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxFCR &= DIRECT_MODE_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxFCR |= Cpy_Ptr->Direct_Mode << 2;

	/*FIFO Threshold Selection*/
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxFCR &= FIFO_THRESHOLD_SELECTION_CLEAR;
	DMA[Cpy_Ptr->DMA]->Cfg_Reg[Cpy_Ptr->Stream].SxFCR |= Cpy_Ptr->FIFO_Threshold_Selection;

	/*CBF*/
	if(Cpy_Ptr->CBF != NULL)
	{
		DMA_CBF[Cpy_Ptr->DMA][Cpy_Ptr->Stream] = Cpy_Ptr->CBF;
	}

	/*NVIC Enable Interrupts*/
	NVIC_EnableInterrupt(DMA_NVIC_INT[Cpy_Ptr->DMA][Cpy_Ptr->Stream]);



	return Loc_Error_Status;
}



DMA_tenuErrorStatus DMA_Start(DMA_ID Cpy_DMA,Stream_ID Cpy_Stream)
{
	DMA_tenuErrorStatus Loc_Error_Status = DMA_enuOK;

	switch(Cpy_Stream)
	{
	case DMA_Stream0:
		DMA[Cpy_DMA]->LIFCR |= STREAM0_INT_CLEAR;
		break;

	case DMA_Stream1:
		DMA[Cpy_DMA]->LIFCR |= STREAM1_INT_CLEAR;
		break;

	case DMA_Stream2:
		DMA[Cpy_DMA]->LIFCR |= STREAM2_INT_CLEAR;
		break;

	case DMA_Stream3:
		DMA[Cpy_DMA]->LIFCR |= STREAM3_INT_CLEAR;
		break;

	case DMA_Stream4:
		DMA[Cpy_DMA]->HIFCR |= STREAM4_INT_CLEAR;
		break;

	case DMA_Stream5:
		DMA[Cpy_DMA]->HIFCR |= STREAM5_INT_CLEAR;
		break;

	case DMA_Stream6:
		DMA[Cpy_DMA]->HIFCR |= STREAM6_INT_CLEAR;
		break;

	case DMA_Stream7:
		DMA[Cpy_DMA]->HIFCR |= STREAM7_INT_CLEAR;
		break;
	}

	DMA[Cpy_DMA]->Cfg_Reg[Cpy_Stream].SxCR |= 1 << 0;




	return Loc_Error_Status;
}


DMA_tenuErrorStatus DMA_Stop(DMA_ID Cpy_DMA,Stream_ID Cpy_Stream)
{

	DMA_tenuErrorStatus Loc_Error_Status = DMA_enuOK;


	DMA[Cpy_DMA]->Cfg_Reg[Cpy_Stream].SxCR &= ~(1 << 0);




	return Loc_Error_Status;

}


/*********Handler's*********/
void DMA2_Stream2_IRQHandler(void)
{
	if(DMA_CBF[DMA_2][DMA_Stream2])
	{
		DMA_CBF[DMA_2][DMA_Stream2]();
		DMA[DMA_2]->LIFCR |= STREAM2_INT_CLEAR;
	}
}

void DMA2_Stream5_IRQHandler(void)
{
	if(DMA_CBF[DMA_2][DMA_Stream5])
	{
		DMA_CBF[DMA_2][DMA_Stream5]();
		DMA[DMA_2]->HIFCR |= STREAM5_INT_CLEAR;
	}
}


void DMA2_Stream7_IRQHandler(void)
{
	if(DMA_CBF[DMA_2][DMA_Stream7])
	{
		DMA_CBF[DMA_2][DMA_Stream7]();
		DMA[DMA_2]->HIFCR |= STREAM7_INT_CLEAR;
	}
}


