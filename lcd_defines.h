#ifndef _LCD_DEFINES_H
#define _LCD_DEFINES_H
#include <lpc21xx.h>

#define CLEAR_LCD 	     		 0x01           
#define RET_CUR_HOME         0x02
#define SHIFT_CUR_RIGHT      0x06
#define SHIFT_CUR_LEFT       0x10
#define DSP_OFF              0x08
#define DSP_ON_CUR_OFF       0x0C
#define DSP_ON_CUR_ON        0x0E
#define DSP_ON_CUR_BLINK     0x0F
#define SHIFT_DISP_LEFT      0x10
#define SHIFT_DISP_RIGHT     0x14
#define MODE_8BIT_1LINE      0x30
#define MODE_4BIT_1LINE      0x20
#define MODE_8BIT_2LINE      0x38
#define MODE_4BIT_2LINE      0x28
#define GOTO_LINE1_POS0      0x80
#define GOTO_LINE2_POS0      0xC0
#define GOTO_LINE3_POS0      0x94
#define GOTO_LINE4_POS0      0xD4
#define GOTO_CGRAM_START     0x40






#define RS	8										//resistor select pin p0.8
#define RW	9										//read write pin p0.9
#define EN	10									//enable pin p0.10

#define LCD_DATA 0 							//P0.0 TO P0.7

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_char(unsigned char);
void lcd_str(char *);

void lcd_num(int );
void SetCursor(unsigned char ,unsigned char );




#endif
