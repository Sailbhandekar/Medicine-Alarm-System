#ifndef _RTC_DEFINES_H
#define _RTC_DEFINES_H
#include <lpc21xx.h>

#define BUZZER 13     

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

void rtc_init(void);
void get_time(int *,int *,int*);
void show_time(int,int,int);
void get_date(int *,int *,int*);
void show_date(int,int,int);
void update_date_time(void);
void get_day(int*);
void show_day(int);
void buzzer_init(void);




void update_time(int);
void update_date(void);
void update_dmy(int);



//void update_hour(void);
#endif
