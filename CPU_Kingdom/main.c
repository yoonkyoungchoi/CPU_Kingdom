// use console, cursor ...
#include <Windows.h>
// use exit function
#include <stdlib.h>
// input output ...
#include <stdio.h>

// header files
#include "ciano_tiles.h"
#include "guess_note.h"
#include "maze_game.h"
#include "pushpull.h"
#include "snake_game.h"
#include "modules.h"
#include "avoidgame.h"
#include "bluewhite.h"

// _getch() value of ESC key (chohadam 21-03-11)
#define ESC 27

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

		case 6:
			// 눈피하기 게임
			//PlayGame();
			break;

		case 7:
			//청기백기 게임
			break;

		// end game
		case 8:
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
	gotoxy(60, 1);
	printf("▶");
	gotoxy(60, 2);
	printf("|");
	gotoxy(60, 3);
	printf("|");
	gotoxy(59, 4);
	printf("▲");
	gotoxy(57, 5);
	printf("▲▼▲");
	gotoxy(55, 6);
	printf("▲▼▲▼▲");
	gotoxy(52, 7);
	printf("▲▼▲▲▼▲▼▲");
	gotoxy(40, 8);
	printf("■■■■■■■■■■■■■■■■■■■■");
	gotoxy(34, 9);
	printf("■■■■■                                ■■■■■ ");
	gotoxy(30, 10);
	printf("■■■■■                                        ■■■■■");
	gotoxy(27, 11);
	printf(" ■■■■                                                ■■■■ ");
	gotoxy(26, 12);
	printf("■                                                                ■ ");
	gotoxy(26, 13);
	printf("■                                                                ■ ");
	gotoxy(26, 14);
	printf("■                                                                ■ ");
	gotoxy(26, 15);
	printf("■                                                                ■ ");
	gotoxy(26, 16);
	printf("■                                                                ■ ");
	gotoxy(26, 17); 
	printf("■                                                                ■ ");
	gotoxy(26, 18); 
	printf("■                                                                ■ ");
	gotoxy(26, 19);
	printf("■                                                                ■ ");
	gotoxy(26, 20);
	printf("■                                                                ■ ");
	gotoxy(26, 21);
	printf("■                                                                ■ ");
	gotoxy(26, 22);
	printf("■                                                                ■ ");
	gotoxy(26, 23);
	printf("■                                                                ■ ");
	gotoxy(26, 24);
	printf("■                                                                ■ ");
	gotoxy(26, 25);
	printf("■                                                                ■ ");
	gotoxy(26, 26);
	printf("■                                                                ■ ");
	gotoxy(26, 27);
	printf("■                                                                ■ ");
	gotoxy(26, 27);
	printf("■                                                                ■ ");
	gotoxy(26, 28);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(53, 10);
	printf("1. CIANO TILE");
	gotoxy(53, 12);
	printf("2. GUESS NOTE");
	gotoxy(53, 14);
	printf("3. MAZE GAME");
	gotoxy(53, 16);
	printf("4. PUSHPULL");
	gotoxy(53, 18);
	printf("5. SNAKE GAME");
	gotoxy(53, 20);
	printf("6. AVOID GAME");
	gotoxy(53, 22);
	printf("7. 청기 백기 GAME");
	gotoxy(53, 24);
	printf("8. EXIT");
	gotoxy(48, 26);
	printf("Please select a game>> ");

	int select;
	scanf_s("%d", &select);

	return select;
}