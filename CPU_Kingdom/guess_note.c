#include "guess_note.h"
// _getch() value of ESC key
#define ESC 27
#define UP 72
#define DOWN 80
#define SUBMIT 4
#define ENTER 13
#define CTRL 17

/* 함수 선언 */
int keyControl(); 
int menuDraw();
void print_piano();
int pr_str_array(char** dp, int n);
int playGame();
void rule();
void guess_note(void);

char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시", "도" };


int keyControl() {
	char temp;
	while (1) {
		if (_kbhit()) {
			temp = _getch();
			if (temp == -32) {
				temp = _getch();
				switch (temp) {
				case UP:
					return UP;
					break;
				case DOWN:
					return DOWN;
					break;
				}
			}
			else if (temp == 13) {
				return ENTER;
			}
			else if (temp == 27) {
				return ESC;
			}
			else if (temp == 17) {
				return CTRL;
			}
		}
		return 0;
	}
}

int menuDraw() {	
	PlaySound(TEXT("guess_note.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");

	rectangle(114, 29, 2, 1);

	int x = 27;
	int y = 6;
	print_auto_y(&x, &y, "  d8b   d8888b   d8888    d88b   db      db    db d888888b d88888b   ");
	print_auto_y(&x, &y, "d8   8b 88   8D 88   YP  8P  Y8  88      88    88    88    88        ");
	print_auto_y(&x, &y, "88ooo88 88ooob   8bo    88    88 88      88    88    88    88ooooo   ");
	print_auto_y(&x, &y, "88   88 88   b     Y8b  88    88 88      88    88    88    88        ");
	print_auto_y(&x, &y, "88   88 88   8D db   8D  8b  d8  88booo  88b  d88    88    88        ");
	print_auto_y(&x, &y, "88   88 d8888b   8888d    d88b   888888   Y8888P     88    d88888b   ");
	print_auto_y(&x, &y, "                                                                     ");
	print_auto_y(&x, &y, "              d8888b   888888   888888    o88b   88   88             ");
	print_auto_y(&x, &y, "              88   8D    88       88    d8P  d8  88   88             ");
	print_auto_y(&x, &y, "              88oodD     88       88    8P       88ooo88             ");
	print_auto_y(&x, &y, "              88         88       88    8b       88   88             ");
	print_auto_y(&x, &y, "              88         88       88    Y8b  d8  88   88             ");
	print_auto_y(&x, &y, "              88       888888     88      Y88P   88   88             ");
	
	x = 50;
	y = 22;

	gotoxy(x-2, y); // -2한 이유는 >를 출력하기 위해서
	printf(">     게 임 시 작 \n");
	gotoxy(x, y + 2);
	printf("       종 료 \n");
	print_by_name("손지우");



	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 22) { //y는 12~14까지만 이동
				gotoxy(x - 2, y); // x-2하는 이유는 >를 두 칸 이전에 출력하기 위해서
				printf(" ");

				gotoxy(x - 2, y-=2); //새로 이동한 위치로 이동하여
				printf(">"); //다시 그리기
			}
			break;
		}
		case DOWN: {
			if (y < 24) { //최대 20
				gotoxy(x - 2, y);
				printf(" ");

				gotoxy(x - 2, y+=2);
				printf(">");
			}
			break;
		}
		case ENTER: {
			return y - 22; 
			break;
		}
		}
	}
	return 0;
}

void print_piano() {
	gotoxy(34, 11);
	puts("□□■■ ■■□□□■■ ■■ ■■□□□■■ ■■□□");
	gotoxy(34, 12);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 13);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 14);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 15);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 16);
	puts("□  ■■ ■■  □  ■■ ■■ ■■  □  ■■ ■■  □ ");
	gotoxy(34, 17);
	puts("□   □   □   □   □   □   □   □   □   □   □");
	gotoxy(34, 18);
	puts("□ 1 □ 2 □ 3 □ 4 □ 5 □ 6 □ 7 □ 8 □ 9 □ 10□");
	gotoxy(34, 19);
	puts("□□□□□□□□□□□□□□□□□□□□□□□□□□");
}

int pr_str_array(char** dp, int n) {	
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (0 << 4));
		double frequency[] = { 523.2511, 587.3295, 659.2551, 698.456, 783.9909, 880, 987.7666, 1046.502 };
		const int note_len = 600;

		srand((unsigned int)time(NULL));
		int random = (rand() % 8);

		for (int i = 0; i < 8; i++) {
			if (random == i + 1) 
				Sleep(200);			
		}
		Beep(frequency[random], note_len);

		system("cls");

		print_piano();

		int answer;
		
		gotoxy(34, 9);
		printf("무슨 음일까요?: ");
		scanf("%d", &answer);
		
		if (answer == random+1) {
			gotoxy(75, 9);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (0 << 4));
			printf("정답입니다!\n");
		}
		else {
			gotoxy(64, 9);
			printf("땡! 정답은 %d(%s)입니다.\n", random+1, *(dp + random));
			gotoxy(82, 29);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 | (0 << 4));
			printf("3초 후에 메인화면으로 돌아갑니다...");
			Sleep(3000);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | (0 << 4));
			break;
		}
	}
	return 0;
}

int playGame() {
	while (1) {
		int n = keyControl();
		switch (n) {
		case ENTER: {
			return pr_str_array(p, SIZE);
		}
		}
	}
	return 0;
}
void rule() {	
	system("cls");	

	/*for (int helper = 0; helper <= 15; helper++) {
		gotoxy(81, 29);
		textcolor(helper); 
		printf("게임을 시작하려면 엔터를 누르세요...");
		Sleep(100);
	}
	playGame();*/
}

void guess_note(void) {
	system("cls");

	int x = 100, y = 20;
	char key;	

	while (1) {
		int menuCode = menuDraw();
		switch (menuCode) {
		case 0:
			PlaySound(NULL, 0, 0);
			pr_str_array(p, SIZE);
			break;
		case 2:
			main();
			break;
		}
		system("cls");
	}
	return 0;
}