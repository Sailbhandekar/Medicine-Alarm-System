#ifndef _KEYPAD_DEFINES_H
#define _KEYPAD_DEFINES_H
#include <lpc21xx.h>

#define ROWS 16    // Define number of rows (4x4 keypad)
#define COLS 20    // Define number of columns (4x4 keypad)

#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19

#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23

void keypad_init(void);
int colum_scann(void);
int row_scann(void);
void display(int,int);
int  get_key(void);







#endif
