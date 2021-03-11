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

void set_console(void);
void set_cursor(int flag, int size);

int main(void) {
	set_console();

	return 0;
}

// console settings function (chohadam 21-03-11)
void set_console(void) {
	// set the console size
	system("mode con:cols=240 lines=63");
	// hide cursor
	set_cursor(0, 1);
	// set title
	system("title CPU KINGDOM");
	// clear console
	system("cls");
}

// cursor settings function (chohadam 21-03-11)
void set_cursor(int flag, int size) {
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = flag;
	cursor.dwSize = size;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}