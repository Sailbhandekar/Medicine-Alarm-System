#include "lcd_defines.h"
#include "delay.h"


/////////////////////////////////////////////////////////
////**** command for lcd ****////////////////////////////
void lcd_cmd(unsigned char cmd)
{
	IOCLR0|=0XFF<<LCD_DATA; 					//CLEAR DATA PINS
	IOSET0 |= cmd <<LCD_DATA;					//Sending data 
	
	IOCLR0 |=1<<RS;										//RS=0 for command
	IOCLR0 |=1<<RW;										//RW=0 for write
	IOSET0 |=1<<EN;										//high to low to EN
	delay_ms(2);
	IOCLR0 |=1<<EN;										//low EN
	delay_ms(2);
}

////****************************************************************////



////////////////////////////////////////////////////////
////****initilazation of lcd ****////
void lcd_init(void)
{
	IODIR0|=0XFF<<LCD_DATA;							//set direction of data pins
	IODIR0|=1<<RS;											//set direction of RS pin
	IODIR0|=1<<RW;											//set direction of EN pin
	IODIR0|=1<<EN;											//set direction of EN pin
	
	delay_ms(20);												// 15 MS delay
	
	lcd_cmd(0x30);											//function set command
	delay_ms(2);												//delay of 4.5us 
	
	lcd_cmd(0x30);											//function set command
	delay_ms(1);												//delay of 100 ms 
	
	lcd_cmd(0x30);											//function set command
	lcd_cmd(0x38);											//estiblish 8 bit mode with 2 line
	lcd_cmd(0x0f);											// display on(1) cursor on(1) cursor blink on(1)
	lcd_cmd(0x01);											//clear the lcd
	lcd_cmd(0x06);											//increment cursor
}
//*****************************************************************************///////////

//**charactor printing**//
void lcd_char(unsigned char s_char)
{
	IOCLR0 |=0XFF<<LCD_DATA;						// CLEAR THE DATA PINS
	IOSET0 |= s_char<<LCD_DATA;					//Sending data 
	
	IOSET0 |=1<<RS;											//RS=1 for command
	IOCLR0 |=1<<RW;											//RW=0 for write
	IOSET0 |=1<<EN;											//high to low to EN
	delay_ms(1);
	IOCLR0 |=1<<EN;											//low EN
	delay_ms(2);
	
}


/////////////////////////////////////////////////////////////////////
void lcd_str(char *ch)
{

	while(*ch)
	{
		lcd_char(*ch);
		ch++;
	}
}


///////////////////////////////////////////////////////////////////
void lcd_num(int num)
{
	int digit,i=0;
	char arr[10];
	if(num==0)
	{
		lcd_char(0+48);
		return ;
	}
	else
	{
		while(num)
		{
			digit=num%10;
			arr[i++]=(digit+48);
			num/=10;
		}
		
		while(i>0)
		{
			lcd_char(arr[--i]);
		}
	}
}
/////////////////////////////////////////////////////////////////

void SetCursor(unsigned char lineNo,unsigned char pos)
{
	if(lineNo==1)
		lcd_cmd(GOTO_LINE1_POS0+pos);
	else if(lineNo==2)
		lcd_cmd(GOTO_LINE2_POS0+pos);
}	



