#include "delay.h"
void delay_us(unsigned int dlyus)
{
	for(dlyus*=12;dlyus>0;dlyus--);
}

void delay_ms(unsigned int dlyms)
{
	for(dlyms*=1200;dlyms>0;dlyms--);
}

void delay_s(unsigned int dlys)
{
	for(dlys*=12000000;dlys>0;dlys--);
}

