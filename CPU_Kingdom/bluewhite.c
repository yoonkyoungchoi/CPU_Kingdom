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
    gotoxy(45, 5);
    printf("              ▶");
    gotoxy(45, 6);
    printf("              |");
    gotoxy(45, 7);
    printf("******************************");
    gotoxy(45, 8);
    printf("*        청 기 백 기         *");
    gotoxy(45, 9);
    printf("******************************");
    gotoxy(38, 10);
    printf("********************************************");
    gotoxy(38, 11);
    printf("|     제한시간은 15초이며 총 3단계입니다   |");
    gotoxy(38, 12);
    printf("|                                          |");
    gotoxy(38, 13);
    printf("|                Game Start                |");
    gotoxy(38, 14);
    printf("|                   Quit                   |");
    gotoxy(38, 15);
    printf("|                                          |");
    gotoxy(38, 16);
    printf("|         청기 올려 Q  청기 내려 A         |");
    gotoxy(38, 17);
    printf("|         백기 올려 E  백기 내려 D         |");
    gotoxy(38, 18);
    printf("|                                          |");
    gotoxy(38, 19);
    printf("********************************************");
    gotoxy(38, 19);
    printf("********************************************");
    gotoxy(98, 30);
    printf("심이진 조해정 황소은");

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
            y = 1;
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
            case 1:     //나가기
                return QUIT;

            }
        }
    }
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
    gotoxy(44, 12);
    printf(" 당신의 총 점수는 %d점 입니다", score_bluewhite);
    gotoxy(37, 15);
    printf("메인화면으로 넘어갈려면 아무키나 1번 눌러주세요");
    score_bluewhite = 0;
    RoundCnt = 1;

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

    gotoxy(54, 3);
    printf("\n 현재점수 : %d", score_bluewhite);
    old_time = clock();    //시작 시간
    animation(0);

    for (int j = 1; j <= 10; j++) {  //문제 실행
        system("cls");
        gotoxy(57, 5);
        printf("%dROUND \n", RoundCnt);
        gotoxy(55, 3);
        printf("현재점수 : %d", score_bluewhite);
        gotoxy(46, 7);
        int rn = (rand() % 12) + 1;
        printf("%d. %s", j, flag[rn - 1]);

        cur_time = clock();  //현재  시간
        if (((double)(cur_time - old_time) / CLOCKS_PER_SEC) > 15) {
            GameOver(); main_bluewhtie();  break; //check = 0;
        }

        animation(0);

        if (c = _getch()) { //키를 입력받아 옳은키인지 판단하고 점수 누적
            switch (c) {
            case 27: score_bluewhite = 0; main_bluewhtie(); break;
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
                    gotoxy(59, 9);
                    printf("다시!");
                    c = _getch();
                }
                break;
            default: gotoxy(59, 9); printf("다시!"); c = _getch(); break; //Q A E D가 아니면 그냥 계속
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
            gotoxy(37, 15);
            printf("다음화면으로 넘어갈려면 아무키나 2번 눌러주세요");
            Sleep(1000);
        }
    }
    system("pause>null");
}


void basicAni() {
    gotoxy(57, 12);
    printf("▲▲▲▲");
    gotoxy(57, 13);
    printf("#⊙##⊙#");
    gotoxy(57, 14);
    printf("#######");
    gotoxy(57, 15);
    printf("#_____#");
    gotoxy(57, 16);
    printf("#######");
    gotoxy(59, 17);
    printf("##");
    gotoxy(47, 18);
    printf("──■■■■■■■■■■■──");
    gotoxy(53, 19);
    printf("■■■■■■■");
    gotoxy(53, 20);
    printf("■■■■■■■");
    gotoxy(53, 21);
    printf("■■■■■■■");
    gotoxy(53, 22);
    printf("■■■■■■■");
}


void animation(char key) {

    basicAni();
    erase();

    switch (key)
    {
    case 'q':
        basicAni();

        gotoxy(45, 16);
        printf("□");
        gotoxy(45, 17);
        printf("│");
        gotoxy(45, 18);
        printf("└");
        gotoxy(74, 18);
        printf("─");
        gotoxy(76, 18);
        printf("■");
        break;
    case 'a':
        basicAni();
        gotoxy(45, 20);
        printf("□");
        gotoxy(45, 19);
        printf("│");
        gotoxy(45, 18);
        printf("┌");
        gotoxy(74, 18);
        printf("─");
        gotoxy(76, 18);
        printf("■");
        break;
    case 'e':
        basicAni();
        gotoxy(74, 16);
        printf("■");
        gotoxy(74, 17);
        printf("│");
        gotoxy(74, 18);
        printf("┘");
        gotoxy(45, 18);
        printf("─");
        gotoxy(43, 18);
        printf("□");
        break;
    case 'd':
        basicAni();
        gotoxy(74, 20);
        printf("■");
        gotoxy(74, 19);
        printf("│");
        gotoxy(74, 18);
        printf("┐");
        gotoxy(45, 18);
        printf("─");
        gotoxy(43, 18);
        printf("□");
        break;
    default:
        basicAni();
        gotoxy(74, 18);
        printf("─");
        gotoxy(76, 18);
        printf("■");
        gotoxy(45, 18);
        printf("─");
        gotoxy(43, 18);
        printf("□");
        break;
    }
}
void erase(void)
{
    gotoxy(40, 12);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 13);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 14);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 15);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 16);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 17);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 18);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 19);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 20);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 21);
    printf("                                                                                                                                                                                                                                                                                                                           ");
    gotoxy(40, 22);
    printf("                                                                                                                                                                                                                                                                                                                           ");

}


void GameClear() {
    system("cls");
    gotoxy(45, 8);
    printf("******************************");
    gotoxy(45, 9);
    printf("*    G A M E  C L E A R      *");
    gotoxy(45, 10);
    printf("******************************");
    gotoxy(45, 11);
    printf("  당신의 총 점수는 %d점 입니다", score_bluewhite);
    gotoxy(37, 15);
    printf("메인화면으로 넘어갈려면 아무키나 2번 눌러주세요");
    score_bluewhite = 0;
    RoundCnt = 1;
    system("pause>null");

}; //3단계까지 성공하면


//1단계
void Step1() {
    int time = 20; //제한시간
    gotoxy(57, 5);
    printf("1ROUND \n");
    Sleep(1000); //1초후 시작
    //Timer20();//20초제한시간
    FlagRandom(20);
    system("pause>null");
}

//2단계
void Step2() {
    int time = 15; //제한시간
    gotoxy(57, 5);
    printf("2ROUND \n");
    Sleep(1000); //1초후 시작
    FlagRandom();
    system("pause>null");
}
void Step3() {
    int time = 15; //제한시간
    gotoxy(57, 5);
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


