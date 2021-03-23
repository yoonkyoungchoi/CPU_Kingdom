#include "guess_note.h"

// _getch() value of ESC key
#define ESC 27

void guess_note(void) {
	system("cls");

	int x = 100, y = 20;
	char key;

	do {
		gotoxy(x, y);
		printf("guess note");
		key = _getch();
	} while (key != ESC);
}