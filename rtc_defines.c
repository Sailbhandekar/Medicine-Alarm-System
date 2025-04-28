#include "rtc_defines.h"
#include "lcd_defines.h"
#include "keypad_defines.h"
#include "delay.h"
char *ar[]={"SUN","MON","TUE","WED","THU","FRI","SAT"};

////////////////////////////////////////////////////////////////////////////////
void rtc_init(void)
{
	/*
	CCR = 1<<1;
	PREINT=(PCLK/32768)-1;
	PREFRAC = PCLK-((PREINT+1)*32768);
	CCR = 1<<0;
	*/
    CCR = 1 << 1;  																			// Reset the RTC
    PREINT = (PCLK / 32768 / 2) - 1;  									// Divide by 2 for 0.5s
    PREFRAC = PCLK - ((PREINT + 1) * 32768 * 2);
    CCR = 1 << 0;  																			// Enable RTC

}

//////////////////////////////////////////////////////////////////////////////
void get_time(int *hour,int *min,int *sec)
{
	*hour=HOUR;
	*min=MIN;
	*sec=SEC;
}

////////////////////////////////////////////////////////////////////////////////
void show_time(int hour,int min,int sec)
{
    lcd_cmd(0xC0);

    if (hour < 10) 
			lcd_char('0');
    
		lcd_num(hour);
    lcd_char(':');

   
    if (min < 10) 
			lcd_char('0');
    
		lcd_num(min);
    lcd_char(':');

   
    if (sec < 10) 
			lcd_char('0');
    
		lcd_num(sec);

}
////////////////////////////////////////////////////////////////////////////
void get_date(int *date,int *month,int *year)
{
	
	*date=DOM;
	*month=MONTH;
	*year=YEAR;
}
/////////////////////////////////////////////////////////////////////////////
void show_date(int date,int month,int year)
{

				lcd_cmd(0xC0 |10);			// Move cursor back to second line
				
				lcd_num(date);
        lcd_char('/');
				
				
        lcd_num(month);
			
				if (year < 10) 
				lcd_char('0');
        lcd_char('/');      			
				lcd_num(year);
}
//////////////////////////////////////////////////////////////////////////////////
void update_date_time(void)
{

	HOUR=12;
	MIN=34;
	SEC=00;

	DOM=07;
	MONTH=02;
	YEAR=25;
	
	DOW=5;
	
}
/////////////////////////////////////////////////////////////////////////////
void get_day(int *day)
{
	*day=DOW;
}

////////////////////////////////////////////////////////////////////////////////
void show_day(int day)
{
	lcd_str(ar[day]);
}
//////////////////////////////////////////////////////////////////////////////////
void buzzer_init(void)
{
	IODIR0|=1<<BUZZER;
	IOSET0|=1<<BUZZER;
}

//////////////////////////////////////////////////////////////////////////////////////

void update_time(int key)
{
    int res=0,num;
		char *arr[]={" HR:"," MIN:"," SEC:"};
		lcd_cmd(0x01);
		lcd_cmd(0x02);
		lcd_str(arr[key-1]);
		SetCursor(2,0);
		lcd_str(" C:BACK");
			
		while(1)
		{
			num = get_key();
			if((num!=15) && (num!=13))
			res=(res*10)+num;
			SetCursor(1,5);
			lcd_num(res);
			SetCursor(2,9);
			lcd_str(" =:SAVE");
			
			if(num==13)
						{		
							lcd_cmd(0x01);					
							break;
						}
				else if((num==15) && (res<=12) && (key==1))
						{
							 HOUR = res;
							break;
						}
				
				 else if((num==15) && (res<=60) && ((key==2) || (key==3)))
						{
							if (key==2)
							MIN = res;
							if (key==3)
							SEC = res;
							break;
						}
						
				else if(((res>12) && (key==1)) || (res>60 && ((key==2) || (key==3))))
					{	
						res=0;
						SetCursor(2,9);
						lcd_str(" =:ERROR");
						delay_s(1);
						lcd_cmd(0x01);
						lcd_str(arr[key-1]);
						SetCursor(2, 0);
						lcd_str(" C:BACK");								
					}

				}												
}

//////////////////////////////////////////////////////////////////////
void update_date(void)
{
int key;
	lcd_cmd(0x01);
while(1)
	{
		SetCursor(1,0);
		lcd_str(" 1:DT 2:MON 3:YR");
		SetCursor(2,0);
		lcd_str(" 4:DOW  C:BACK");
		key=get_key();
		switch(key)
		{
		
			case 1:
			case 2:
			case 3:
			case 4:update_dmy(key);
						lcd_cmd(0x01);
						break;
		
		}
		if(key==13)
		{
				lcd_cmd(0x01);
				break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////

void update_dmy(int key)
{
    int res=0,num;
		char *arr[]={" DATE:"," MONTH:"," YEAR:"," DAY"};
		lcd_cmd(0x01);
		lcd_cmd(0x02);
		lcd_str(arr[key-1]);
		SetCursor(2,0);
		lcd_str(" C:BACK");
			
		while(1)
		{
			num = get_key();
			if((num!=15) && (num!=13))
			res=(res*10)+num;
			SetCursor(1,8);
			lcd_num(res);
			SetCursor(2,9);
			lcd_str(" =:SAVE");
			
			if(num==13)
						{		
							lcd_cmd(0x01);					
							break;
						}
				else if(num==15)
						{
							if ((res<=31) && (key==1))
							{
							 DOM = res;
							}
							else if((res<=12) && (key==2))
							{
								MONTH = res;
							}
							else if((res<=99) && (key==3))
							{
								YEAR = res;
							}
							else if((res<=7) && (key==4))
							{
								DOW = res;
							}
							break;
						}	
				else if( ((res>31) && (key==1)) || ((res>12) && (key==2)) || ((res>99) && (key==3)) || ((res>7) && (key==4)))
					{	
						res=0;
						SetCursor(2,9);
						lcd_str(" =:ERROR");
						delay_s(1);
						lcd_cmd(0x01);
						lcd_str(arr[key-1]);
						SetCursor(2, 0);
						lcd_str(" C:BACK");								
					}
				
				
					
				}		
				
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

