// The Game Made by Hadam Cho

#include "ciano_tiles.h"

// _getch() value of ESC key
#define ESC 27

void ciano_tiles(void) {
	system("cls");

	int x = 100, y = 20;
	char key;

	do {
		gotoxy(x, y);
		printf("CIANO TILES");
		key = _getch();
	} while (key != ESC);
}