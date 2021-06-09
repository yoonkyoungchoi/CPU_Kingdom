#include "bluewhite.h"

#define MAGIC_KEY 224 //방향키
#define SPACE 32
#define ENTER 13

int check = 0;
int key;
int score_bluewhite = 0;
int RoundCnt = 1;

enum MENU
{
    GAMESTART = 0,
    INFO,
    QUIT
};

enum KEYBOARD
{
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80
};

void SetConsoleView();

void InfoGame();
void PlayGame();
void animation();
void erase();

//메인 루프
int main_bluewhtie(void)
{
    while (1)
    {
        switch (ReadyGame())    //리턴값 받아서 판단.
        {
        case GAMESTART:
            PlayGame();
            break;
        case INFO:
            InfoGame();
            break;
        case QUIT:
            if (key == ENTER) exit(0);  //exit(0) 정상종료
            return 0;
        }
    }
    return 0;
}

//메인화면
void DrawReadyGame()
{
    system("cls");          //clean screen - 화면 청소
    gotoxy(45, 7);
    printf("******************************");
    gotoxy(45, 8);
    printf("*        청 기 백 기         *");
    gotoxy(45, 9);
    printf("******************************");
    gotoxy(44, 11);
    printf("↑↓ 키와 enter키 사용하여 이동");
    gotoxy(55, 13);
    printf("GameStart");
    gotoxy(55, 14);
    printf("GameInfo");
    gotoxy(55, 15);
    printf("Quit\n");
}

//도움말
void DrawInfoGame()
{
    system("cls");
    gotoxy(40, 8);
    printf("********************************************");
    gotoxy(40, 9);
    printf("|     제한시간은 15초이며 총 3단계입니다   |");
    gotoxy(40, 10);
    printf("|                                          |");
    gotoxy(40, 11);
    printf("|                                          |");
    gotoxy(40, 12);
    printf("|                                          |");
    gotoxy(40, 13);
    printf("|         청기 올려 Q  청기 내려 A         |");
    gotoxy(40, 14);
    printf("|         백기 올려 E  백기 내려 D         |");
    gotoxy(40, 15);
    printf("|                                          |");
    gotoxy(40, 16);
    printf("********************************************");

    gotoxy(40, 19);
    printf("아무키나 누르면 다시 메뉴화면으로 돌아갑니다.");
}

enum MENU ReadyGame()
{
    int y = 0; //커서의 y위치
    int input = 0; // 키보드 입력 값 저장 변수
    while (1)            //게임 루프
    {

        DrawReadyGame();    //준비화면

        //DrawUserCursor 함수
        if (y <= 0)        //커서가 위로 더 올라가지 않게
        {
            y = 0;
        }
        else if (y >= 2) //커서가 아래로 그만 내려가게
        {
            y = 2;
        }

        gotoxy(53, 13 + y); // 커서 메뉴에 맞춰서 위치조정
        printf(">");

        input = _getch();    //키보드로 하나의 키 입력

        if (input == MAGIC_KEY) //방향키를 눌렀을 경우 -> 방향키 판별
        {
            switch (_getch())
            {
            case UP:            //방향키 위
                --y;
                break;
            case DOWN:            //방향키 아래
                ++y;
                break;
            }
        }
        else if (input == ENTER) //enter 눌렀을 경우
        {
            switch (y)            //y위치에 따라 판단
            {
            case 0:    //게임시작
                return GAMESTART;
            case 1:     //도움말
                return INFO;
            case 2:     //나가기
                return QUIT;
            }
        }
    }
}

//도움말 뷰
void InfoGame()
{
    DrawInfoGame();
    system("pause>null");
}


void GameOver() {
    //시간초과시 게임오버 
    Sleep(2000);
    system("cls");
    gotoxy(45, 8);
    printf("******************************");
    gotoxy(45, 9);
    printf("*      G A M E  O V E R      *");
    gotoxy(45, 10);
    printf("******************************");
    gotoxy(45, 11);
    printf("    시간이 초과 되었습니다");
    gotoxy(45, 12);
    printf(" 당신의 총 점수는 %d점 입니다", score_bluewhite);
    gotoxy(42, 15);
    printf("메인화면으로 넘어갈려면 아무키나 2번 눌러주세요");
    score_bluewhite = 0;

    system("pause>null");
}

//청기백기 랜덤
void FlagRandom() {

    srand((int)time(NULL));     //문제 중복방지
    int c;

    clock_t old_time, cur_time;

    char flag[12][50] = { "청기 올려","백기 내리지 말고 청기 올려", "청기 올리고 백기 내리지마",//Q 키
                          "청기 내려","백기 올리지 말고 청기 내려","청기 내리고 백기 올리지마",//A 키
                          "백기 올려","청기 내리지 말고 백기 올려","백기 올리고 청기 내리지마", //E 키
                          "백기 내려", "청기 올리지 말고 백기 내려","백기 내리고 청기 올리지마" //D 키
    };

    gotoxy(41, 3);
    printf("\n 현재점수 : %d", score_bluewhite);
    old_time = clock();    //시작 시간
    animation(0);

    for (int j = 1; j <= 10; j++) {  //문제 실행
        system("cls");
        gotoxy(58, 5);
        printf("%dROUND \n", RoundCnt);
        gotoxy(55, 3);
        printf("현재점수 : %d", score_bluewhite);
        gotoxy(46, 7);
        int rn = (rand() % 12) + 1;
        printf("%d. %s", j, flag[rn - 1]);

        cur_time = clock();  //현재  시간
        if (((double)(cur_time - old_time) / CLOCKS_PER_SEC) > 15) {
            GameOver(); main();  break; //check = 0;
        }

        animation(0);

        if (c = _getch()) { //키를 입력받아 옳은키인지 판단하고 점수 누적
            switch (c) {
            case 27: score_bluewhite = 0; main(); break;
            case 'q':
                animation(c);

                Sleep(500);
                if (rn == 1 || rn == 2 || rn == 3)
                    score_bluewhite += 50;
                else {
                    gotoxy(59, 9);
                    printf("다시!");
                    c = _getch();
                }
                break;
            case 'a':
                animation(c);
                Sleep(500);
                if (rn == 4 || rn == 5 || rn == 6)
                    score_bluewhite += 50;
                else {
                    gotoxy(59, 9);
                    printf("다시!");
                    c = _getch();
                }
                break;
            case 'e':
                animation(c);
                Sleep(500);
                if (rn == 7 || rn == 8 || rn == 9)
                    score_bluewhite += 50;
                else {
                    gotoxy(59, 9);
                    printf("다시!");
                    c = _getch();
                }
                break;
            case 'd':
                animation(c);
                Sleep(500);
                if (rn == 10 || rn == 11 || rn == 12)
                    score_bluewhite += 50;
                else {
                    gotoxy(59,9);
                    printf("다시!");
                    c = _getch();
                }
                break;
            default:  gotoxy(40, 8); printf("다시!"); c = _getch(); break; //Q A E D가 아니면 그냥 계속
            }

        }
        if (j == 10) {
            RoundCnt++;
            check = 1;
            system("cls");
            gotoxy(45, 8);
            printf("******************************");
            gotoxy(45, 9);
            printf("*       TOTAL SCORE=%d        *", score_bluewhite);
            gotoxy(45, 10);
            printf("******************************");

            Sleep(1000);
            gotoxy(32, 15);
            printf("\n  다음단계로 넘어갈려면 아무키나 2번 눌러주세요");
            Sleep(1000);
        }
    }
    system("pause>null");
}




void animation(char key) {

    gotoxy(50, 12);
    printf("▲▲▲▲");
    gotoxy(50, 13);
    printf("#⊙##⊙#");
    gotoxy(50, 14);
    printf("#######");
    gotoxy(50, 15);
    printf("#_____#");
    gotoxy(50, 16);
    printf("#######");
    gotoxy(52, 17);
    printf("##");
    gotoxy(48, 18);
    printf("──■■■■■■■■■■■──");
    gotoxy(54, 19);
    printf("■■■■■■■");
    gotoxy(54, 20);
    printf("■■■■■■■");
    gotoxy(54, 21);
    printf("■■■■■■■");
    gotoxy(54, 22);
    printf("■■■■■■■");

    erase();

    switch (key)
    {
    case 'q':
        gotoxy(50, 10);
        printf("▲▲▲▲");
        gotoxy(50, 11);
        printf("#⊙##⊙#");
        gotoxy(50, 12);
        printf("#######");
        gotoxy(50, 13);
        printf("#_____#");
        gotoxy(50, 14);
        printf("#######");
        gotoxy(52, 15);
        printf("##");
        gotoxy(48, 16);
        printf("──■■■■■■■■■■■──");
        gotoxy(54, 17);
        printf("■■■■■■■");
        gotoxy(54, 18);
        printf("■■■■■■■");
        gotoxy(54, 19);
        printf("■■■■■■■");
        gotoxy(54, 20);
        printf("■■■■■■■");
        gotoxy(14, 14);
        printf("□");
        gotoxy(14, 15);
        printf("│");
        gotoxy(14, 16);
        printf("└");
        gotoxy(30, 16);
        printf("─");
        gotoxy(32, 16);
        printf("■");
        break;
    case 'a':
        gotoxy(5022, 10);
        printf("▲▲▲▲");
        gotoxy(50, 11);
        printf("#⊙##⊙#");
        gotoxy(50, 12);
        printf("#######");
        gotoxy(50, 13);
        printf("#_____#");
        gotoxy(50, 14);
        printf("#######");
        gotoxy(52, 15);
        printf("##");
        gotoxy(48, 16);
        printf("──■■■■■■■■■■■──");
        gotoxy(54, 17);
        printf("■■■■■■■");
        gotoxy(54, 18);
        printf("■■■■■■■");
        gotoxy(54, 19);
        printf("■■■■■■■");
        gotoxy(54, 20);
        printf("■■■■■■■");
        gotoxy(14, 18);
        printf("□");
        gotoxy(14, 17);
        printf("│");
        gotoxy(14, 16);
        printf("┌");
        gotoxy(30, 16);
        printf("─");
        gotoxy(32, 16);
        printf("■");
        break;
    case 'e':
        gotoxy(50, 10);
        printf("▲▲▲▲");
        gotoxy(50, 11);
        printf("#⊙##⊙#");
        gotoxy(50, 12);
        printf("#######");
        gotoxy(50, 13);
        printf("#_____#");
        gotoxy(50, 14);
        printf("#######");
        gotoxy(52, 15);
        printf("##");
        gotoxy(48, 16);
        printf("──■■■■■■■■■■■──");
        gotoxy(54, 17);
        printf("■■■■■■■");
        gotoxy(54, 18);
        printf("■■■■■■■");
        gotoxy(54, 19);
        printf("■■■■■■■");
        gotoxy(54, 20);
        printf("■■■■■■■");
        gotoxy(30, 14);
        printf("■");
        gotoxy(30, 15);
        printf("│");
        gotoxy(30, 16);
        printf("┘");
        gotoxy(14, 16);
        printf("─");
        gotoxy(12, 16);
        printf("□");
        break;
    case 'd':
        gotoxy(50, 10);
        printf("▲▲▲▲");
        gotoxy(50, 11);
        printf("#⊙##⊙#");
        gotoxy(50, 12);
        printf("#######");
        gotoxy(50, 13);
        printf("#_____#");
        gotoxy(50, 14);
        printf("#######");
        gotoxy(52, 15);
        printf("##");
        gotoxy(48, 16);
        printf("──■■■■■■■■■■■──");
        gotoxy(54, 17);
        printf("■■■■■■■");
        gotoxy(54, 18);
        printf("■■■■■■■");
        gotoxy(54, 19);
        printf("■■■■■■■");
        gotoxy(54, 20);
        printf("■■■■■■■");
        gotoxy(30, 18);
        printf("■");
        gotoxy(30, 17);
        printf("│");
        gotoxy(30, 16);
        printf("┐");
        gotoxy(14, 16);
        printf("─");
        gotoxy(12, 16);
        printf("□");
        break;
    default:
        gotoxy(57, 10);
        printf("▲▲▲▲");
        gotoxy(57, 11);
        printf("#⊙##⊙#");
        gotoxy(57, 12);
        printf("########");
        gotoxy(57, 13);
        printf("#______#");
        gotoxy(57, 14);
        printf("########");
        gotoxy(60, 15);
        printf("##");
        gotoxy(48, 16);
        printf("──■■■■■■■■■■■──");
        gotoxy(54, 17);
        printf("■■■■■■■");
        gotoxy(54, 18);
        printf("■■■■■■■");
        gotoxy(54, 19);
        printf("■■■■■■■");
        gotoxy(54, 20);
        printf("■■■■■■■");
        gotoxy(44, 16);
        printf("─");
        gotoxy(42, 16);
        printf("■");
        gotoxy(70, 16);
        printf("─");
        gotoxy(72, 16);
        printf("□");
    }
}
void erase(void)
{
    gotoxy(48, 10);
    printf("                                                                                                          ");
    gotoxy(481, 11);
    printf("                                                                                                          ");
    gotoxy(48, 12);
    printf("                                                                                                          ");
    gotoxy(48, 13);
    printf("                                                                                                          ");
    gotoxy(48, 14);
    printf("                                                                                                          ");
    gotoxy(481, 15);
    printf("                                                                                                          ");
    gotoxy(48, 16);
    printf("                                                                                                          ");
    gotoxy(48, 17);
    printf("                                                                                                          ");
    gotoxy(48, 18);
    printf("                                                                                                          ");
    gotoxy(48, 19);
    printf("                                                                                                          ");
    gotoxy(48, 20);
    printf("                                                                                                          ");


}


void GameClear() {
    system("cls");
    gotoxy(15, 8);
    printf("******************************");
    gotoxy(15, 9);
    printf("*    G A M E  C L E A R      *");
    gotoxy(15, 10);
    printf("******************************");
    gotoxy(15, 11);
    printf("  당신의 총 점수는 %d점 입니다", score_bluewhite);
    gotoxy(12, 15);
    printf("메인화면으로 넘어갈려면 아무키나 2번 눌러주세요");
    score_bluewhite = 0;
    system("pause>null");

}; //3단계까지 성공하면


//1단계
void Step1() {
    int time = 20; //제한시간
    gotoxy(58, 5);
    printf("1ROUND \n");
    Sleep(1000); //1초후 시작
    //Timer20();//20초제한시간
    FlagRandom(20);
    system("pause>null");
}

//2단계
void Step2() {
    int time = 15; //제한시간
    gotoxy(58, 5);
    printf("2ROUND \n");
    Sleep(1000); //1초후 시작
    FlagRandom();
    system("pause>null");
}
void Step3() {
    int time = 15; //제한시간
    gotoxy(58, 5);
    printf("3ROUND \n");
    Sleep(1000); //1초후 시작
    FlagRandom();
    system("pause>null");
}

//2초타이머
void Timer2() {
    gotoxy(52, 1);
    printf("2초후 시작 합니다\n");
    Sleep(2000); //1000 -> 1초
    system("cls");
}

//게임 시작
void PlayGame() {

    system("cls");
    Timer2();
    Step1();
    Timer2();
    Step2();
    Timer2();
    Step3();
    GameClear();
    system("pause>null");
}


