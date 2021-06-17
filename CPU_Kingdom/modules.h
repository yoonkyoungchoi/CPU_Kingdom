#pragma once
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>;
#pragma comment(lib, "winmm.lib")

void gotoxy(int x, int y);
int get_key(void);
void move_arrow_key(
	char key,
	int* x,
	int* y,
	int size,
	int y_min,
	int y_max,
	int x_min,
	int x_max
);
void print_auto_y(int* x, int* y, char* str);