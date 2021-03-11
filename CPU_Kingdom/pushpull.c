#include "pushpull.h"

// _getch() value of ESC key
#define ESC 27

void pushpull(void) {
	system("cls");

	int x = 100, y = 20;
	char key;

	do {
		gotoxy(x, y);
		printf("PUSHPULL");
		key = _getch();
	} while (key != ESC);
}