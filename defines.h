#ifndef _DEFINES_H
#define _DEFINES_H
#include <LPC21xx.H>

#define SW1 		11
#define SW2			12


void switch_init(void);
void edit_menu(void);
void show_clock(void);
void rtc_edit(void);
void alarm_set(void);
void Alarm(void);
void Alarm_set(int key);


#endif
