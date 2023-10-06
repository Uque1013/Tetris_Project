#include <iostream>
#include <Windows.h>
#include <vector>
#include <cstdlib> // rand
#include <ctime> // time
#include <conio.h>

using namespace std;

// Ű���尪
# define LEFT 75 // �������� �̵�
# define RIGHT 77 // ���������� �̵�
# define UP 72	// ȸ��
# define DOWN 80 // õõ�� drop
# define SPACE 32 // ������ drop
# define ESC 27 // ���� ���� 

// ��ǥ �̵� 
void gotoxy(int x, int y) { //gotoxy�Լ� 
	COORD pos = { 2 * x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ��� ����
class Blocks {
public:
	Blocks(void) {
		next_type = rand() % 7;
	}

	static const int shape[7][4][4][4]; // ��� ��� 
	int x, y; // ��ǥ
	int type; // ��� ����
	int rotation; // ��� ȸ����
	int next_type; // ���� ���
	int getColor(int num); // ��� ���� �Լ�
};

// ��Ʈ�ι̳� �迭
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

// ��� �÷� ����
int Blocks::getColor(int num) {
	if (num < 0) num *= (-1);
	return num - 9;
}

class Tetris {
public:
	Tetris(int game_x, int game_y);

	// ��ǥ ����
	int game_x;
	int game_y;


};

// ���� Ÿ��Ʋ
void GameTitle() {
	const char* tetris[] = {
		"������  �����  ������  ����   ������  ������",
		"    ��      ��            ��	   ��    ��     ��      ��",
		"    ��      �����      ��      ����       ��      ������",
		"    ��      ��            ��      ��   ��      ��              ��",
		"    ��      �����      ��      ��    ��     ��      ������"
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