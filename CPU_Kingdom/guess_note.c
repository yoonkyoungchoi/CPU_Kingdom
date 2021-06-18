#include "guess_note.h"

// _getch() value of ESC key
#define ESC 27
#define UP 72
#define DOWN 80
#define SUBMIT 4
#define ENTER 13

/* 함수 선언 */
int keyControl(); 
int menuDraw();
void print_piano();
int pr_str_array(char** dp, int n);
int playGame();
void rule();
void guess_note(void);

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
		}
		return 0;
	}
}

int menuDraw() {	
	system("cls");
	int x = 50;
	int y = 17;

	gotoxy(30, 5);
	printf("■ ■ ■ ■ ■ ■ ■ ■ ■ 절대 음감 ■ ■ ■ ■ ■ ■ ■ ■ ■");
	gotoxy(30, 7);
	printf("■               들리는 음을 듣고 맞춰보세요!                 ■");
	gotoxy(30, 9);
	printf("■    게임 시작 전 한글로 설정되어 있는지 확인해주세요:)   ■");
	gotoxy(30, 11);
	printf("■            중간중간 점수(♥) 꼭 잊지 말고 얻기~           ■");
	gotoxy(30, 13);
	printf("■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ■ ");

	gotoxy(x-2, y); // -2한 이유는 >를 출력하기 위해서
	printf(">     게 임 시 작 \n");
	gotoxy(x, y + 2);
	printf("       종 료 \n");
	print_by_name("손지우");



	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 17) { //y는 12~14까지만 이동
				gotoxy(x - 2, y); // x-2하는 이유는 >를 두 칸 이전에 출력하기 위해서
				printf(" ");

				gotoxy(x - 2, y-=2); //새로 이동한 위치로 이동하여
				printf(">"); //다시 그리기
			}
			break;
		}
		case DOWN: {
			if (y < 19) { //최대 17
				gotoxy(x - 2, y);
				printf(" ");

				gotoxy(x - 2, y+=2);
				printf(">");
			}
			break;
		}
		case ENTER: {
			return y - 17; 
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
	puts("□   □   □   □   □   □   □   □   □   □   □");
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
			if (random == i + 1) {
				Sleep(200);
			}
		}
		Beep(frequency[random], note_len);


		system("cls");

		char answer[10];

		print_piano();

		gotoxy(34, 9);
		printf("무슨 음일까요?: ");
		scanf("%s", answer);

		if (!strcmp(answer, *(dp + random))) {
			gotoxy(75, 9);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | (0 << 4));
			printf("정답입니다!\n");
		}
		else {
			gotoxy(67, 9);
			printf("땡! 정답은 %s입니다.\n", *(dp + random));
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
	char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시", "도" };
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
	PlaySound(TEXT("guess_note.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시", "도" };
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