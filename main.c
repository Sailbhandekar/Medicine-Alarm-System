#include "defines.h"
#include "lcd_defines.h"
#include "keypad_defines.h"
#include "defines.h"
#include "rtc_defines.h"
#include "delay.h"


int r,c;
int main()
{
	
	lcd_init();									//lcd initilazation
	
	rtc_init();									//rtc initilazation
	
	keypad_init();							//keypad initilazation
	
	switch_init();							//switch initilazation
	
	update_date_time(); 				//get time and date
	
	buzzer_init();							//buzzer initilazation

	while (1)
  {
		
		
			show_clock();						//to show the clock timing on lcd
			if(((IOPIN0>>SW1)&1)==0)
			{
				edit_menu();					//to edit the time as will as MT time
			}
			
			Alarm();							//to check the alarm ststus
			
				
			
  }
}
