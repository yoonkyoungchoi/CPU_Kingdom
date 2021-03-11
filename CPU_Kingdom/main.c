#include <Windows.h>

#include "ciano_tile.h"
#include "snake_game.h"
#include "maze_game.h"
#include "pushpull.h"
#include "modules.h"

// _getch() value of ESC key (chohadam 21-03-11)
#define ESC 27

// C++ function
void guess_note();

void setConsole(void);
void setCursor(int flag, int size);

int main(void) {
	setConsole();

	return 0;
}

// console settings function (chohadam 21-03-11)
void setConsole(void) {
	// set the console size
	system("mode con:cols=240 lines=63");
	// hide cursor
	setCursor(0, 1);
	// set title
	system("title CPU KINGDOM");
	// clear console
	system("cls");
}

// cursor settings function (chohadam 21-03-11)
void setCursor(int flag, int size) {
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = flag;
	cursor.dwSize = size;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}