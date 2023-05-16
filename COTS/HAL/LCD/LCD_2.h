

#ifndef LCD_2_H_
#define LCD_2_H_

#include "Std_Types.h"
#include "GPIO.h"

typedef enum
{
	LCD_NotInit=0,
	LCD_Idle,
	LCD_Busy,
	LCD_PinsDelay,
	LCD_FunctionSet,
	LCD_DisplayON_OFF,
	LCD_DisplayClear,
	LCD_EntryModeSet,
	LCD_OK,
	LCD_NOK

}LCD_State_t;



typedef struct
{
	GPIO_Cfg_t RS;
	GPIO_Cfg_t RW;
	GPIO_Cfg_t E;
	GPIO_Cfg_t data[8];

}pins_t;



typedef enum
{
	Function_Set = 0b00111000, //Function Set: N=1, number of lines equal 2. F=0, 5*8 Font
	Display_On_Off = 0b00001110, //Display ON/OFF: D= 1, display is on. C=0, Cursor is OFF. B=0, Blinking is OFF.
	Display_Clear = 0b00000001, //Display Clear
	Entry_Mode_Set = 0b00000110
}LCD_Init_Sequence;


typedef enum
{
	Write,
	Clear,
	NoRequest
}req_t;



typedef struct
{
	const char* str;
	u8 len;
	u8 pos_x;
	u8 pos_y;
	u8 pos_current;
}req_data_t;


extern pins_t pins;


LCD_State_t LCD_Init(void);

LCD_State_t LCD_WriteAsync(const char * string, u8 length, u8 x, u8 y);

LCD_State_t LCD_ClearString(void);

void LCD_Task(void);




#endif /* LCD_2_H_ */
