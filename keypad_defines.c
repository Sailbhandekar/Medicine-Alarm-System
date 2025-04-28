#include "keypad_defines.h"
#include "lcd_defines.h"


int arr[4][4] = {{1, 2, 3, 4},
                 {5, 6, 7, 8},
                 {9, 10, 11, 12},
                 {13, 0, 15, 16}};


unsigned int c0,c1,c2,c3;
unsigned char r_val,c_val;								
											 
void keypad_init(void)
{
    // Configure ROWS as output (set to high initially)
    IODIR1 |= (0xF << ROWS);   // Configure pins for rows as output (P1.16 - P1.19)
    IOCLR1 |= (0xF<< ROWS);    // Set rows to high
															// Configure pins for columns as input (P1.20 - P1.23)
    //IOSET1 |= (0xF << COLS);    // Set columns to low
}



int colum_scann(void)
{
	//columns identification process
	//if col0 status is low then column value is 0
	if(((IOPIN1>>COL0)&1) == 0)
		c_val = 0;
	//else if col1 status is low then column value is 1
	else if(((IOPIN1>>COL1)&1) == 0)
		c_val = 1;
	//else if col2 status is low then column value is 2
	else if(((IOPIN1>>COL2)&1) == 0)
		c_val = 2;
	//else if col3 status is low then column value is 3
	else if(((IOPIN1>>COL3)&1) == 0)
		c_val = 3;


	//waiting for switch release
	//read the all columns status and any one of the column is 0 then switch is pressed so wait here until switch is released
	while(1)
	{
		c0 = ((IOPIN1>>COL0)&1);
		c1 = ((IOPIN1>>COL1)&1);
		c2 = ((IOPIN1>>COL2)&1);
		c3 = ((IOPIN1>>COL3)&1);
		if((c0&c1&c2&c3) != 0)
			break;
	}
return c_val;
}
////////////////////////////////////////////////////////////////////////////////////////////



int row_scann(void)
{
	IOCLR1 = ((1<<ROW0)|(1<<ROW1)|(1<<ROW2)|(1<<ROW3));
	while(1)
		{
			c0=((IOPIN1>>COL0)&1);
			c1=((IOPIN1>>COL1)&1);
			c2=((IOPIN1>>COL2)&1);
			c3=((IOPIN1>>COL3)&1);
		if((c0&c1&c2&c3)==0)
			break;
		}
	//////////////////////////////////////////////////////
	while(1)
	{
		IOCLR1|=1<<ROW0;
		IOSET1|= ((1<<ROW1) | (1<<ROW2) |(1<<ROW3));
		
		c0=((IOPIN1>>COL0)&1);
		c1=((IOPIN1>>COL1)&1);
		c2=((IOPIN1>>COL2)&1);
		c3=((IOPIN1>>COL3)&1);
		
		if((c0&c1&c2&c3)==0)
		{	
			r_val=0;
			break;
		}
		////////////////////////////////////////////////////
		IOCLR1|=1<<ROW1;
		IOSET1|= ((1<<ROW0) | (1<<ROW2) |(1<<ROW3));
		
		c0=((IOPIN1>>COL0)&1);
		c1=((IOPIN1>>COL1)&1);
		c2=((IOPIN1>>COL2)&1);
		c3=((IOPIN1>>COL3)&1);
		
		if((c0&c1&c2&c3)==0)
		{	
			r_val=1;
			break;
		}
		////////////////////////////////////////////////////////
		IOCLR1|=1<<ROW2;
		IOSET1|= ((1<<ROW1) | (1<<ROW0) |(1<<ROW3));
		
		c0=((IOPIN1>>COL0)&1);
		c1=((IOPIN1>>COL1)&1);
		c2=((IOPIN1>>COL2)&1);
		c3=((IOPIN1>>COL3)&1);
		
		if((c0&c1&c2&c3)==0)
		{	
			r_val=2;
			break;
		}
		////////////////////////////////////////////////////////////////////
		IOCLR1|=1<<ROW3;
		IOSET1|= ((1<<ROW1) | (1<<ROW2) |(1<<ROW0));
		
		c0=((IOPIN1>>COL0)&1);
		c1=((IOPIN1>>COL1)&1);
		c2=((IOPIN1>>COL2)&1);
		c3=((IOPIN1>>COL3)&1);
		
		if((c0&c1&c2&c3)==0)
		{	
			r_val=3;
			break;
		}
		////////////////////////////////////////////////////////////////////
	
	}
	return r_val;
}



void display(int r_val,int c_val)
{
	lcd_num(arr[r_val][c_val]);
}


int  get_key(void)
{			
			int r,c;
			//lcd_cmd(0xc0);
			r=row_scann();
			c=colum_scann();
			//display(r,c);
return arr[r][c];
}

