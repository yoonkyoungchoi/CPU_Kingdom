#include "guess_note.h"

// _getch() value of ESC key
#define ESC 27
#define UP 72
#define DOWN 80
#define SUBMIT 4

/* 함수 선언 */
int keyControl(); 

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
			if (temp == ' ') {
				return SUBMIT;
			}
		}
		return 0;
	}
}

int menuDraw() {	
	system("cls");
	int x = 50;
	int y = 13;

	gotoxy(x-2, y); // -2한 이유는 >를 출력하기 위해서
	printf(">     게 임 시 작 \n");
	gotoxy(x, y + 2);
	printf("    게 임 방 법  \n");
	gotoxy(x, y + 4);
	printf("       종 료 \n");


	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 13) { //y는 12~14까지만 이동
				gotoxy(x - 2, y); // x-2하는 이유는 >를 두 칸 이전에 출력하기 위해서
				printf(" ");

				gotoxy(x - 2, y-=2); //새로 이동한 위치로 이동하여
				printf(">"); //다시 그리기
			}
			break;
		}
		case DOWN: {
			if (y < 17) { //최대 17
				gotoxy(x - 2, y);
				printf(" ");

				gotoxy(x - 2, y+=2);
				printf(">");
			}
			break;
		}
		case SUBMIT: {
			return y - 13; 
		}
		}
	}
	return 0;
}

void print_piano() {
	puts("　　　　　　┃ ┃┃┃┃ ┃  ┃ ┃┃┃┃┃┃ ┃  ┃ ┃┃┃┃ ┃  ┃");
	puts("　　　　　　┃ ┃┃┃┃ ┃  ┃ ┃┃┃┃┃┃ ┃  ┃ ┃┃┃┃ ┃  ┃");
	puts("　　　　　　┃ ┃┃┃┃ ┃  ┃ ┃┃┃┃┃┃ ┃  ┃ ┃┃┃┃ ┃  ┃");
	puts("　　　　　　┃ ┃┃┃┃ ┃  ┃ ┃┃┃┃┃┃ ┃  ┃ ┃┃┃┃ ┃  ┃");
	puts("　　　　　　┃ ┃┃┃┃ ┃  ┃ ┃┃┃┃┃┃ ┃  ┃ ┃┃┃┃ ┃  ┃");
	puts("　　　　　　┃ ┗┛┗┛ ┃  ┃ ┗┛┗┛┗┛ ┃  ┃ ┗┛┗┛ ┃  ┃");
	puts("　　　　　　┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
	puts("　　　　　　┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
	puts("　　　　　　┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃  ┃");
	puts("　　　　　　┗━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┻━┛");

}

int pr_str_array(char** dp, int n) {
	while (1) {
		double frequency[] = { 523.2511, 587.3295, 659.2551, 698.456, 783.9909, 880, 987.7666 };
		const int note_len = 600;

		srand((unsigned int)time(NULL));
		int random = (rand() % 7);

		for (int i = 0; i < 7; i++) {
			if (random == i + 1) {
				Sleep(200);
			}
		}
		Beep(frequency[random], note_len);


		system("cls");

		char answer[10];

		print_piano();

		gotoxy(29, 17);
		printf("무슨 음일까요?: ");
		scanf("%s", answer);

		if (!strcmp(answer, *(dp + random))) {
			printf("정답입니다.\n");
		}
		else {
			printf("틀렸습니다. 정답은 %s입니다.\n", *(dp + random));
			//2초 후에 꺼지게
			break;
		}
	}
	return 0;
}

int playGame() {
	char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시" };
	while (1) {
		if (keyControl() == SUBMIT)
			break;
		int n = keyControl();
		switch (n) {
		case SUBMIT: {
			return pr_str_array(p, SIZE);
		}
		}
	}
	return 0;
}
void rule() {
	system("cls");
	gotoxy(26, 14);
	printf("그냥 듣고 맞추세여");
	gotoxy(75, 29);
	printf("게임을 시작하려면 스페이스바를 누르세요...");
	playGame();
}

void guess_note(void) {
	system("cls");

	char* p[SIZE] = { "도", "레", "미", "파", "솔" , "라", "시" };
	int x = 100, y = 20;
	char key;	


	while (1) {
		int menuCode = menuDraw();
		switch (menuCode) {
		case 0:
			pr_str_array(p, SIZE);
			break;
		case 2:
			rule();
			break;
		case 4:
			main();
			break;
		}
		system("cls");
	}

	do {
		gotoxy(x, y);
		printf("guess note");
		key = _getch();
	} while (key != ESC);

	return 0;
}