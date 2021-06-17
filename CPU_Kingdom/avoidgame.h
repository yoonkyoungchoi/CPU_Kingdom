#include<stdio.h>
#include<stdbool.h>
#include<Windows.h>
#include <time.h>
#include "modules.h"

//적(피할 것)
typedef struct
{
	int x;
	int y;
	//적의 상태 (TRUE, FALSE)로 컨트롤할 것
	int con;
}Snow;
//플레이어
typedef struct
{
	int x;
}Player;


