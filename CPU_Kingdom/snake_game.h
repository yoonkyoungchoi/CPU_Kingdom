#pragma once
#include <stdio.h>
#include "modules.h"
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void snake_game(void);
void title(void);
void reset(void);
void draw_map(void);
void move(int dir);
void over(void);
void target(void);
void print(void);
void snake_start(void);
int choose_mode();