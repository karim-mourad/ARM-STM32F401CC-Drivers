#include "LCD_2.h"



u8 init_flag=0;

u8 pin_init =0;
static LCD_State_t state = LCD_NotInit;

req_data_t req;
req_t request_type = NoRequest;
#define max_x_pos 15

static void LCD_pins_Init(void)
{
	GPIO_Init(&pins.RS);
	GPIO_Init(&pins.RW);
	GPIO_Init(&pins.E);

	GPIO_Init(&pins.data[0]);
	GPIO_Init(&pins.data[1]);
	GPIO_Init(&pins.data[2]);
	GPIO_Init(&pins.data[3]);
	GPIO_Init(&pins.data[4]);
	GPIO_Init(&pins.data[5]);
	GPIO_Init(&pins.data[6]);
	GPIO_Init(&pins.data[7]);

	state = LCD_PinsDelay;

	pin_init = 1;
}

static void WriteCommand(u8 command)
{
	u8 i=0;
	u8 temp;
	GPIO_SetPins(&pins.E, pins.E.GPIO_PIN, GPIO_SET_PIN_VALUE_LOW);
	GPIO_SetPins(&pins.RS, pins.RS.GPIO_PIN, GPIO_SET_PIN_VALUE_LOW);
	GPIO_SetPins(&pins.RW, pins.RW.GPIO_PIN, GPIO_SET_PIN_VALUE_LOW);
	for(i=0;i<8;i++)
	{
		temp = (command>>i) & 1;
		GPIO_SetPins(&pins.data[i], pins.data[i].GPIO_PIN, temp);
	}
	GPIO_SetPins(&pins.E, pins.E.GPIO_PIN, GPIO_SET_PIN_VALUE_HIGH);

}


static void Writedata(u8 data)
{
	u8 i=0;
	u8 temp;
	GPIO_SetPins(&pins.E, pins.E.GPIO_PIN, GPIO_SET_PIN_VALUE_LOW);
	GPIO_SetPins(&pins.RS, pins.RS.GPIO_PIN, GPIO_SET_PIN_VALUE_HIGH);
	GPIO_SetPins(&pins.RW, pins.RW.GPIO_PIN, GPIO_SET_PIN_VALUE_LOW);
	for(i=0;i<8;i++)
	{
		temp = (data>>i) & 1;
		GPIO_SetPins(&pins.data[i], pins.data[i].GPIO_PIN, temp);
	}
	GPIO_SetPins(&pins.E, pins.E.GPIO_PIN, GPIO_SET_PIN_VALUE_HIGH);
}




static void LCD_GoToXY(u8 x, u8 y)
{
	u8 loc_location=0;
	if(x == 0)
	{
		loc_location = y;
	}
	else if(x == 1)
	{
		loc_location = 0x40 + y;
	}
	WriteCommand(128+loc_location);

}




static void LCD_Clear()
{
	WriteCommand(0b00000001); //Clear display
	WriteCommand(0b00000010); //Return Home
}



static void writing_sequence(void)
{
	if(req.pos_current == req.len)
	{
		LCD_GoToXY(0,(req.pos_current+1));
		state = LCD_Idle;
		request_type = NoRequest;
	}

	else if(req.pos_current == max_x_pos)
	{
		LCD_GoToXY(1, 0);
	}

	else
	{
		Writedata(req.str[req.pos_current]);
		req.pos_current++;
	}
}



static void clearing_sequence(){
	if(req.pos_current==0)
	{
		state=LCD_Idle;
		request_type = NoRequest;
	}
	else
	{
		LCD_Clear();
	}


}


LCD_State_t LCD_Init(void)
{

	static u8 counter = 0;
	if (pin_init == 0)
	{
		LCD_pins_Init();
	}

	else
	{
		switch(state)
		{


			case LCD_PinsDelay:
			{
				if(counter<20)
				{
					counter++;
					break;
				}
				else
				{
					counter =0;
					state = LCD_FunctionSet;
					break;
				}
			}

			case LCD_FunctionSet:
			{
				WriteCommand(Function_Set);
				state = LCD_DisplayON_OFF;
				break;
			}

			case LCD_DisplayON_OFF:
			{
				WriteCommand(Display_On_Off);
				state = LCD_DisplayClear;
				break;
			}

			case LCD_DisplayClear:
			{
				WriteCommand(Display_Clear);
				/*state = LCD_Idle;
				init_flag = 1;*/
				state = LCD_EntryModeSet;
				break;
			}

			case LCD_EntryModeSet:
			{
				WriteCommand(Entry_Mode_Set);
				state = LCD_Idle;
				init_flag = 1;
				break;
			}

		}
	}


	return state;

}

LCD_State_t LCD_WriteAsync(const char * string, u8 length, u8 x, u8 y)
{

	LCD_State_t status;
	if(state == LCD_Idle)
	{
		req.str = string;
		req.len = length;
		req.pos_x = x;
		req.pos_y = y;
		req.pos_current = 0;
		LCD_GoToXY(req.pos_x, req.pos_y);
		state = LCD_Busy;
		status = LCD_OK;
		request_type = Write;
	}

	else
	{
		status = LCD_NotInit;
	}

	return status;
}


LCD_State_t LCD_ClearString(void)
{
	LCD_State_t status;
	if(state == LCD_Idle)
	{
		state = LCD_Busy;
		request_type = Clear;
		status = LCD_OK;
	}

	else
	{
		status = LCD_NotInit;
	}

	return status;
}




void LCD_Task(void)
{
	if(init_flag == 0)
	{
		LCD_Init();
	}
	else
	{

		switch(request_type)
		{
			case Write:
			{
				writing_sequence();
				break;
			}

			case Clear:
			{
				clearing_sequence();
				break;
			}
		}
	}
}

