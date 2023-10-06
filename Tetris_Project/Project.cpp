#include <iostream>
#include <Windows.h>
#include <vector>
#include <cstdlib> // rand
#include <ctime> // time
#include <conio.h>

using namespace std;

// 키보드값
# define LEFT 75 // 왼쪽으로 이동
# define RIGHT 77 // 오른쪽으로 이동
# define UP 72	// 회전
# define DOWN 80 // 천천히 drop
# define SPACE 32 // 빠르게 drop
# define ESC 27 // 게임 종료 

// 좌표 이동 
void gotoxy(int x, int y) { //gotoxy함수 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 블록 구현
class Blocks {
public:
	Blocks(void) {
		next_type = rand() % 7;
	}

	static const int shape[7][4][4][4]; // 블록 모양 
	int x, y; // 좌표
	int type; // 블록 종류
	int rotation; // 블록 회전값
	int next_type; // 다음 블록
	int getColor(int num); // 블록 색깔 함수
};

// 테트로미노 배열
const int Blocks::shape[7][4][4][4] = {
	{ // I-Piece
		{0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0},
		{0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0},
		{0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0},
		{0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0}
	},

	{ // O-Piece
		{0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0}
	},

	{ // L-Piece
		{0,0,0,0,
		0,0,1,0,
		1,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		1,1,0,0,
		0,1,0,0,
		0,1,0,0},
		{0,0,0,0,
		0,0,0,0,
		1,1,1,0,
		1,0,0,0},
		{0,0,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,1,0}
	},

	{ // J-Piece
		{0,0,0,0,
		0,0,0,0,
		1,1,1,0,
		0,0,1,0},
		{0,0,0,0,
		1,0,0,0,
		1,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		0,1,0,0,
		0,1,0,0,
		1,1,0,0},
		{0,0,0,0,
		0,1,1,0,
		0,1,0,0,
		0,1,0,0}
	},

	{ // T-Piece
		{0,0,0,0,
		0,0,0,0,
		1,1,1,0,
		0,1,0,0},
		{0,0,0,0,
		0,1,0,0,
		1,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		0,1,0,0,
		0,1,1,0,
		0,1,0,0},
		{0,0,0,0,
		0,1,0,0,
		1,1,0,0,
		0,1,0,0}
	},

	{ // Z-Piece
		{0,0,0,0,
		1,1,0,0,
		0,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		0,0,1,0,
		0,1,1,0,
		0,1,0,0},
		{0,0,0,0,
		1,1,0,0,
		0,1,1,0,
		0,0,0,0},
		{0,0,0,0,
		0,0,1,0,
		0,1,1,0,
		0,1,0,0}
	},

	{ // S-Piece
		{0,0,0,0,
		0,1,1,0,
		1,1,0,0,
		0,0,0,0},
		{0,0,0,0,
		1,0,0,0,
		1,1,0,0,
		0,1,0,0},
		{0,0,0,0,
		0,1,1,0,
		1,1,0,0,
		0,0,0,0},
		{0,0,0,0,
		1,0,0,0,
		1,1,0,0,
		0,1,0,0}
	}
};

// 블록 컬러 구현
int Blocks::getColor(int num) {
	if (num < 0) num *= (-1);
	return num - 9;
}

class Tetris {
public:
	Tetris(int game_x, int game_y);

	// 좌표 변수
	int game_x;
	int game_y;


};

// 게임 타이틀
void GameTitle() {
	const char* tetris[] = {
		"■■■■■  ■■■■  ■■■■■  ■■■   ■■■■■  ■■■■■",
		"    ■      ■            ■	   ■    ■     ■      ■",
		"    ■      ■■■■      ■      ■■■       ■      ■■■■■",
		"    ■      ■            ■      ■   ■      ■              ■",
		"    ■      ■■■■      ■      ■    ■     ■      ■■■■■"
	};

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0003);

	for (int i = 0; i < 5; i++) {
		gotoxy(10, 5 + i);
		cout << tetris[i];
		Sleep(200);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
}



int main() {
	srand((unsigned)time(NULL));
	GameTitle();
}