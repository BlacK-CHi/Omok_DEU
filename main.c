#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

/*
리눅스 버전의 MinGW 컴파일러에는 conio.h 헤더파일이 없어서 getch()를 사용할 수 없으므로,
인터넷을 통해 대체할 수 있는 방법을 찾았고, 코드를 깔끔하게 유지 및 빌드 플랫폼 선택을 위해 헤더파일로 포함하도록 했다.
비슷하게 gotoxy()의 경우에도 대체제를 해당 함수 안에 주석처리로 넣어두었다.
*/
//#include "linux_getch.h"

/* -------------- 선언부 ----------------- */
#define putBlack printf("○") // 돌 출력을 일일히 printf()로 처리하지 않고 키워드로 정의함.
#define putWhite printf("●")
#define BLACK 1 //현재 순서를 표시할 때 흑돌은 1, 백돌은 2를 사용하는데, BLACK/WHITE 키워드를 사용하여 코딩에서 보기 쉽게 처리하고자 했다.
#define WHITE 2

void gotoxy(int x, int y); //CLI 환경에서 커서 이동
void initBoard(); //오목판을 초기화하고 표시
void KeyPress(); //키입력(상하좌우 및 ESC/SPACE)을 받아서 처리
void GameControl(); //게임 작동 순서 및 규칙을 정의
void removeStone(); //이동 시 돌을 제거
void putStone(); //현재 커서 위치에 돌을 착수
void drawStone(); //진행중인 게임 데이터에서 정보를 읽어와 돌 위치를 화면에 표시


/* ---------------- 구현부 ----------------- */
void main(){
    system("chcp 65001"); //EUC-KR 코드페이지 (cp949)에서는 오목판 텍스트가 깨져서 보일 수 있기 때문에 UTF-8 코드페이지로 변경.
    GameControl(); //오목 게임을 시작함 (해당 함수가 호출되어야 게임이 시작됨)
}

void gotoxy(int x, int y){
	//윈도우
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	//리눅스
	//printf("\033[%d;%df", y, x);
}

void initBoard(){
	int i = 0, j = 0;

	//1번 행 그리기
	printf("┌");
	for (i = 0; i< 17; i++)
		printf("┬");
	printf("┐\n");
	
	//2번 - 19번 행 그리기 (*2~19행은 모양이 같기 때문에 2중 For문을 사용하면 됨.)
	for(i = 0; i < 17; i++){
		printf("├");
		for (j = 0; j < 17; j++)
			printf("┼");
		printf("┤\n");
	}

	//20번 행 그리기
	printf("└");
	for (i = 0; i < 17; i++)
		printf("┴");
	printf("┘");
}

void KeyPress(int Board[][20], char keycode, int kx, int ky){

/* 참고사항
    - 일반적인 윈도우 환경에서, row 1, Col 1 위치를 좌표계에 표시하면 (0,0)이고, 
      좌로 이동할 때마다 X값이 +1, 아래로 이동할 때마다 Y값이 +1씩 더해진다. 반대의 경우에는 -1을 하면 된다.
    - 우리가 가로줄을 만들기 위해 사용한 문자는 2바이트 문자열이기 때문에, X좌표는 2씩 이동시켜야 한다.
*/

    switch(keycode){ //GameControl()에서 받은 keycode 기준 (ASCII Key Code)
	case 72: //방향키 위
		if (ky-1 < 0) //맨 윗줄인 경우를 확인 (True : 무시, False : 한 칸 위로 이동(y-1))
			break;
		else
			ky -= 1;
		break;
	case 80: //방향키 아래
		if (ky+1 > 18) //맨 아랫줄인 경우를 확인 (True : 무시, False : 한 칸 아래로 이동(y+1))
			break;
		else
			ky += 1;
		break;
	case 75: //방향키 왼쪽
		if (kx-2 < 0) //맨 왼쪽인 경우를 확인 (True : 무시, False : 두 칸 (시각상으로는 한 칸) 왼쪽으로 이동(x-2))
			break;
		else
			kx -= 2;
		break;
	case 77: //방향키 오른쪽
		if(kx+2 > 36) //맨 오른쪽인 경우를 확인 (True : 무시, False : 두 칸 (시각상으로는 한 칸) 오른쪽으로 이동(x+2))
			break;
		else
			kx += 2;
		break;
	case 32: //스페이스바를 입력하면 착수함
			putStone(Board, kx, ky);
		break;
	default:
		break;
	}
}

void GameControl(){
	int omokBoard[20][20] = {0}; //돌이 놓였는지 아닌지를 확인하기 위한 이차원 배열
	int x = 0, y = 0; //첫 좌표는 무조건 (0,0)으로 initialize한다.
	char keycode; //getch()를 통해 입력을 받을 경우 

	initBoard();
	gotoxy(x, y);
}

void removeStone(){

}

void putStone(){

}

void drawStone(int Board[][20]){
	int pX, pY;
	for (pX = 0; pX < 20; pX++){ //이중 For문을 사용하여 오목판 위의 돌 정보를 읽어들인다 (1일 경우 흑돌, 2일 경우 백돌 (*선언부 참조))
		for (pY = 0; pY < 20; pY++){	
			if (Board[pX][pY] == BLACK){ //들어있는 값이 1(BLACK)인 경우 흑돌을 출력한다
				gotoxy(pX * 2, pY);
				putBlack;
            }else if(Board[pX][pY] == WHITE){ //들어있는 값이 2(WHITE)인 경우 백돌을 출력한다
				gotoxy(pX * 2, pY);
				putWhite;
            }
		}
	}
}


