#include <iostream>
#include "guess_note.h" 
using namespace std;

// _getch() value of ESC key
#define ESC 27

extern "C" void guess_note() {
	system("cls");

	cout << "guess note\n";

	int x = 100, y = 20;
	char key = 0;

	do {
		gotoxy(x, y);
		printf("njk");
		key = _getch();
	} while (key != ESC);
}