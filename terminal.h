#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Colors
{
	Black = 0,
	Red,
	Green,
	Yellow,
	Blue,
	Purple,
	Cyan,
	White,
	Default
} colors;

int mt_clearScreen();

int mt_gotoXY();

int mt_getScreenSize(int* rows, int* cols);

int mt_setForegroundColor(enum colors);

int mt_setBackgroundColor(enum colors);

