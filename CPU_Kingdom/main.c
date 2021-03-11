// use console, cursor ...
#include <Windows.h>
// use exit function
#include <stdlib.h>
// input output ...
#include <stdio.h>

// header files
#include "ciano_tiles.h"
#include "maze_game.h"
#include "pushpull.h"
#include "snake_game.h"
#include "modules.h"

// _getch() value of ESC key (chohadam 21-03-11)
#define ESC 27

// C++ function
void guess_note();

void set_console(void);
void set_cursor(int flag, int size);

int select_game(void);

int main(void) {
	set_console();

	// input value
	int select;
	while (select = select_game()) {
		switch (select)
		{
		case 1:
			ciano_tiles();
			break;

		case 2:
			guess_note();
			break;

		case 3:
			maze_game();
			break;

		case 4:
			pushpull();
			break;

		case 5:
			snake_game();
			break;

		// end game
		case 6:
			exit(1);

		default:
			break;
		}
	}

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

// select the game function (chohadam 21-03-11)
int select_game(void) {
	system("cls");

	// temporary menu
	gotoxy(100, 20);
	printf("1. CIANO TILE");
	gotoxy(100, 22);
	printf("2. GUESS NOTE");
	gotoxy(100, 24);
	printf("3. MAZE GAME");
	gotoxy(100, 26);
	printf("4. PUSHPULL");
	gotoxy(100, 28);
	printf("5. SNAKE GAME");
	gotoxy(100, 30);
	printf("6. EXIT");
	gotoxy(100, 32);
	printf("Please select a game>> ");

	int select;
	scanf_s("%d", &select);

	return select;
}