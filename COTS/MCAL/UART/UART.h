

#ifndef UART_H_
#define UART_H_

/*****************Includes*****************/

#include "Std_Types.h"
#include "GPIO.h"
#include "NVIC.h"
#include <math.h>
/*****************Defines*****************/

#define bits_CLR_MASK 0xFFFFEFFF
#define bits_8  0
#define bits_9  0x00001000

#define PARITY_CONTROL_CLR_MASK 0xFFFFFBFF
#define PARITY_ENABLE 0x00000400
#define PARITY_DISABLE 0

#define PARITY_TYPE_CLR_MASK 0xFFFFFDFF
#define PARITY_ODD	0x00000200
#define PARITY_EVEN	0

#define STOP_bits_CLR_MASK 0xFFFFCFFF
#define STOP_bits_1 0
#define STOP_bits_2 0x00002000

#define OVERSAMPLING_CLR_MASK	0xFFFF7FFF
#define OVERSAMPLING_16	0
#define OVERSAMPLING_8	0x00008000


#define F_CPU 16000000

/******************Types******************/

typedef void(*CBF_t)(void);


typedef enum
{
	UART_enuOK,
	UART_enuNOK,
	UART_enuNull,
	UART_enuBusy

}UART_tenuErrorStatus;



typedef enum
{
	UART_1,
	UART_2,
	UART_6
}UART_CHANNELS_t;



typedef struct
{
	GPIO_Cfg_t Tx;
	GPIO_Cfg_t Rx;
}UART_Pins_t;



typedef struct
{

	UART_CHANNELS_t Channel;
	u32 DataLength;
	u32 Parity_Control;
	u32 Parity_Type;
	u32 StopBits;
	u32 OverSampling;
	u32 BaudRate;
	UART_Pins_t UART_Pins;
}UART_Cfg_t;


typedef enum
{
	UART1=0,
	No_Of_UART
}UART_COUNT;





//extern UART_Cfg_t UART_Cfg [No_Of_UART];
/******************API's******************/

/*
Description:


Options:


Return:
*/
UART_tenuErrorStatus UART_Init(UART_Cfg_t * Cpy_UART);

UART_tenuErrorStatus UART_SendAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, CBF_t Cpy_CBF);

UART_tenuErrorStatus UART_ReceiveAsynchZeroCpy(UART_CHANNELS_t Cpy_Channel, u8 * buffer, u32 size, CBF_t Cpy_CBF);


/**/
#define IDLE 0
#define BUSY 1
#define NOT_INIT 2
u8 get_status(void);

#endif /* UART_H_ */
