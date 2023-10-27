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

// 테트로미노 배열 (배열 차원 한 단계씩 줄여갈 예정)
const int Blocks::shape[7][4][4][4] = {
	{ // I-Piece
		{1,1,1,1,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0},
		{1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0},
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
		"■■■  ■■■  ■■■  ■■■    ■■■   ■■■",
		"  ■    ■        ■	 ■    ■    ■    ■",
		"  ■    ■■■    ■    ■■■      ■     ■■■",
		"  ■    ■        ■    ■   ■     ■          ■",
		"  ■    ■■■    ■    ■    ■  ■■■   ■■■"
	};

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0003);

	for (int i = 0; i < 5; i++) {
		gotoxy(10, 5 + i);
		cout << tetris[i];
		Sleep(200);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
}

void show_graphic(std::string*** p) {
	int i, j;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) { std::cout << p[i][j]->c_str(); }
		std::cout << std::endl;
	}

	return;
}
int array(char key) {
	switch (key) {
	case 72: return 0;
	case 75: return 1;
	case 77: return 3;
	case 80: return 2;
	default: return -1;
	}
}
void move_block(char*** p, int blocktype, int key, int x, int y) {

}
void show_blockpoints(char** p) {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 2; j++) {
			printf(" %d", p[i][j]);
		}
		printf("\n");
	}
	return;
}


// 테트리스 화면 크기 구상 : 대부분 10*20 사용
int main() {
	srand((unsigned)time(NULL));
	// GameTitle();

	// ▩□■
	int i = 0, j = 0;
	std::string*** graphic; // 문자열을 원소로 갖는 2차원 배열
	int** block_points;

	// graphic 동적할당
	graphic = new std::string **[30]; // 30개의 행
	for (i = 0; i < 30; i++) {
		graphic[i] = new std::string * [30]; // 30개의 열
	}

	block_points = (int**)malloc(sizeof(int*) * 4);
	for (i = 0; i < 4; i++) block_points[i] = (int*)malloc(sizeof(int) * 2);

	//show_blockpoints(block_points);

	// 기본세팅
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			if (i == 4 && j > 8 && j < 21) {
				graphic[i][j] = new std::string("▩");
			}
			else if (i == 25 && j > 8 && j < 21) {
				graphic[i][j] = new std::string("▩");
			}
			else if (j == 9 && i > 3 && i < 26) {
				graphic[i][j] = new std::string("▩");
			}
			else if (j == 20 && i > 3 && i < 26) {
				graphic[i][j] = new std::string("▩");
			}
			else graphic[i][j] = new std::string("  ");

		}
	}

	show_graphic(graphic);

	// 할당된 메모리 해제
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			delete graphic[i][j];
		}
		delete[] graphic[i];
	}
	delete[] graphic;

	return 0;
}