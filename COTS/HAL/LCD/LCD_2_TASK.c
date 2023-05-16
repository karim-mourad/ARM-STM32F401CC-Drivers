#include "LCD_2.h"


/*void LCD_Runnable(void)
{
	static u8 counter;
	if(counter%2==0)
	{
		LCD_WriteAsync("KARIM",6,0,0);

	}
	else
	{
		LCD_ClearString();
	}
	counter++;
}
*/


void LCD_Runnable(void)
{
	LCD_WriteAsync("KARIM",5,0,0);
}
