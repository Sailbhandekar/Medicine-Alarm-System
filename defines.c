#include "defines.h"
#include "lcd_defines.h"
#include "rtc_defines.h"
#include "keypad_defines.h"
#include "delay.h"
int a_hr=-1,a_min=-1;
int day,month,year,date,hour,min,sec;
int pass=1234;

///////////////////////////////////////////////////////////////
void switch_init(void)
{
	IODIR0|=(1<<SW2) | (1<<SW1);
	IOSET0|=(1<<SW2) | (1<<SW1);

}
////////////////////////////////////////////////////////////////
void edit_menu(void)
{	
	
int key;
	
				while(1)
				{
					lcd_cmd(0x01);
					SetCursor(1,0);
					lcd_str(" 1:RTC EDIT");
					SetCursor(2,0);
					lcd_str(" 2:MT UPD C:BACK");
					key=get_key();
					switch(key)
					{
						case 1:rtc_edit();
									break;
						case 2:alarm_set();
									break;
					}
					
					if(key==13)
					{
						lcd_cmd(0x01);
						break;
					}
					
					}
				
}
/////////////////////////////////////////////////////////////////
void show_clock(void)
{	
			lcd_cmd(0x0c);
			SetCursor(1,0);
			lcd_str("Time:");
			
			SetCursor(2,0);
			get_time(&hour,&min,&sec);
			show_time(hour,min,sec);	
			
			SetCursor(2,10);
			get_date(&date,&month,&year);
			show_date(date,month,year);
			
			SetCursor(1,12);
			get_day(&day);
			show_day(day);

}

/////////////////////////////////////////////////////////////
void rtc_edit(void)
{
	int key;
	lcd_cmd(0x01);
	
	while(1)
	{
		SetCursor(1,0);
		lcd_str(" 1:HR 2:MI 3:SC");
		SetCursor(2,0);
		lcd_str(" 4:DATE  C:BACK");
		key=get_key();
		if(key>=1 && key<=3)
			{
				update_time(key);
			}
		else if(key==4)
			{
					update_date();
			}		
		else if(key==13)
		{
				break;
		}
	}
}
///////////////////////////////////////////////////////////////////////
void alarm_set(void)
{
	int key,num,res=0;
	lcd_cmd(0x01);
	
	while(1)
	{		
			SetCursor(1,0);
			lcd_str(" ENTER PASSWORD");
			num = get_key();
			if((num!=15) && (num!=13))
			res=(res*10)+num;
			SetCursor(1,8);
			lcd_num(res);
			SetCursor(2,9);
			lcd_str(" =:ENTER");
			if(res==pass && num==15)
			{
				lcd_cmd(0x01);
				while(1)
				{
					SetCursor(1,0);
					lcd_str("	ENTET TIME");
					SetCursor(2,0);
					lcd_str("1:H 2:M C:BACK");
					key=get_key();
		
					if(key==1 || key==2)
						{
							Alarm_set(key);
							lcd_cmd(0x01);			
						}	
					else if(key==13) break;
				}
			}
			else if(res!=pass && num==15) 
				break;
			if(num==13 || key==13)
				break;
	}
}

//////////////////////////////////////////////////////////////////////////////
void Alarm_set(int key)
{
  int res=0,num;
		char *arr[]={" HOUR:"," MINUIT:"};
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
				else if((num==15) && (res<=24) && (key==1))
						{
							 a_hr = res;
							break;
						}
				else if((num==15) && (res<=60) && (key==2))
						{
							 a_min = res;
							break;
						}
				
						
				else if( ((res>24) && (key==1)) || ((res>60) && (key==2)))
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


//////////////////////////////////////////////////////////////
void Alarm(void)
{
	if((HOUR==a_hr)&&(MIN==a_min))
	{
		
		while(((IOPIN0>>SW2)&1)!=0)
		{
			IOCLR0=1<<BUZZER;
			delay_ms(500);
			lcd_cmd(0x01);
			lcd_str(" MEDISINE ALERT");
			IOSET0=1<<BUZZER;
			delay_ms(500);
		}
		IOSET0=1<<BUZZER;
		a_hr=-1;
		a_min=-1;
		lcd_cmd(0x01);
	}
}
