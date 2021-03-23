#include "pushpull.h"

// _getch() value of ESC key
#define ESC 27

// 주석 
/*
double rule(char name[][10]);
int result(char name[][10], int* result1, int* result2);
void gotoxy(int x, int y);

int main(void) {
	char name[2][10];
	double time;

	time = rule(name);
}
*/
void pushpull(void) {
	system("cls");

	int x = 100, y = 20;
	char key;

	do {
		gotoxy(x, y);
		printf("★★★★ 줄다리기 ★★★★");
		printf("★ 스페이스바와 엔터를 활용하여 ★");
		printf("★ 줄을 가장 빨리 자기쪽으로 당기는 게임입니다!★");
		printf("★ 단판 승부! ★");
		printf("PUSHPULL");
		key = _getch();
	} while (key != ESC);
}

/*
double rule(char name[][10]) { 
	double time = 20; //제한시간 20초
	int i;
	for (i = 0; i < 3; i++) {
		print("%d번 팀 이름을 입력해주세요! -> "); //팀 이름 입력받음
		scanf("%s", &name[i]); // for문으로 2번 반복
	}

	printf("\n\n\n");
	printf("☆ 제한시간 : ", time);
	sleep(1000);
	time--; //시간 감소

	//중앙점 표시
	gotoxy(38, 6); 
	printf("▼");
	gotoxy(40, 7);
	printf("▲");

	return time;
	
}

int result(char name[][10], int* result1, int* result2) { //결과값 출력
	gotoxy(1, 14);
	if (*result1 == 2) {
		printf("☆☆☆ %s 승리! ☆☆☆");
		return 1;
	}
	else if (*result2 == 2) {
		printf("☆☆☆ %s 승리! ☆☆☆");
		return 2;
	}
	return 0;
}

void rope(int a){ //줄다리기 줄 설정
	int i, line[21] = { 0 }; // 21칸
	line[10] = 1; //선 범위 지정
	line[4] = 2;
	line[16] = 2;
	gotoxy(1, 8);
	for (i = 0; i < 78; i++) {
		printf(" ");
	}
	gotoxy(a, 8);

	for (i = 0; i < 21; i++) { 
		if (line[i] == 0) {
			printf("□");
		}else if (line[i] == 1) { //중심점
			printf("■");
		}else
			printf("◆");
	}
} */
