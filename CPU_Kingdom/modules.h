#pragma once
#include <Windows.h>
#include <conio.h>

void gotoxy(int x, int y);
int get_key(void);
void move_arrow_key(char key, int* x, int* y);