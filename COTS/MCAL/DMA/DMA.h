

#ifndef DMA_H_
#define DMA_H_


/*****************Includes*****************/

#include "Std_Types.h"
#include "NVIC.h"

/*****************Defines*****************/


/******************Types******************/
typedef enum{

	DMA_enuOK,
	DMA_enuNOK

}DMA_tenuErrorStatus;

typedef void(*DMA_CBF_t)(void);

typedef enum{
	DMA_1 = 0,
	DMA_2

}DMA_ID;


typedef enum
{
	DMA_Stream0 = 0,
	DMA_Stream1,
	DMA_Stream2,
	DMA_Stream3,
	DMA_Stream4,
	DMA_Stream5,
	DMA_Stream6,
	DMA_Stream7

}Stream_ID;

typedef enum
{
	DMA_Channel0 = 0,
	DMA_Channel1,
	DMA_Channel2,
	DMA_Channel3,
	DMA_Channel4,
	DMA_Channel5,
	DMA_Channel6,
	DMA_Channel7

}Channel_ID;


typedef enum
{
	Disable = 0,
	Enable

}State;

typedef enum
{
	Direct_Enable = 0,
	Direct_Disable = 1

}State_Direct;




typedef enum
{
	single = 0,
	Inc_4_beats,
	Inc_8_beats,
	Inc_16_beats
}Burst_t;


typedef enum
{
	Low = 0,
	Medium,
	High,
	Very_High
}Priority_t;


typedef enum
{
	byte = 0,
	Half_word,
	Word
}Size_t;


typedef enum
{
	Per_to_Mem = 0,
	Mem_to_Per,
	Mem_to_Mem

}Direction_t;

typedef enum
{
	Quarter_FIFO_Full = 0,
	Half_FIFO_Full,
	Three_Quartera_FIFO_Full,
	Full_FIFO,
}FIFO_Threshold_t;

typedef struct
{
	DMA_ID	DMA;
	Stream_ID Stream;
	Channel_ID Channel;
	Burst_t	Memory_Burst;
	Burst_t	Peripheral_Burst;
	State DoubleBuffer;
	Priority_t Priority_Level;
	Size_t	Memory_Size;
	Size_t	Peripheral_Size;
	State	Memory_Auto_Increment;
	State	Peripheral_Auto_Increment;
	State 	Circular_Mode;
	Direction_t	Data_Direction;
	State TC_Interrupt;
	State HTC_Interrupt;
	State Transfer_Error_Interrupt;
	State Direct_Mode_Error_Interrupt;
	u16	Data_Items;
	u32 Peripheral_Address;
	u32 Memory0_Address;
	u32 Memory1_Address;
	State FIFO_Interrupt;
	State_Direct Direct_Mode;
	FIFO_Threshold_t FIFO_Threshold_Selection;
	DMA_CBF_t CBF;


}DMA_Cfg_t;


/******************API's******************/

DMA_tenuErrorStatus DMA_Init(const DMA_Cfg_t * Cpy_Ptr);

DMA_tenuErrorStatus DMA_Start(DMA_ID Cpy_DMA,Stream_ID Cpy_Stream);

DMA_tenuErrorStatus DMA_Stop(DMA_ID Cpy_DMA,Stream_ID Cpy_Stream);



#endif /* DMA_H_ */
