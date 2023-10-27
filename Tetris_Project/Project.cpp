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

// ��Ʈ�ι̳� �迭 (�迭 ���� �� �ܰ辿 �ٿ��� ����)
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
		"����  ����  ����  ����    ����   ����",
		"  ��    ��        ��	 ��    ��    ��    ��",
		"  ��    ����    ��    ����      ��     ����",
		"  ��    ��        ��    ��   ��     ��          ��",
		"  ��    ����    ��    ��    ��  ����   ����"
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


// ��Ʈ���� ȭ�� ũ�� ���� : ��κ� 10*20 ���
int main() {
	srand((unsigned)time(NULL));
	// GameTitle();

	// �̡��
	int i = 0, j = 0;
	std::string*** graphic; // ���ڿ��� ���ҷ� ���� 2���� �迭
	int** block_points;

	// graphic �����Ҵ�
	graphic = new std::string **[30]; // 30���� ��
	for (i = 0; i < 30; i++) {
		graphic[i] = new std::string * [30]; // 30���� ��
	}

	block_points = (int**)malloc(sizeof(int*) * 4);
	for (i = 0; i < 4; i++) block_points[i] = (int*)malloc(sizeof(int) * 2);

	//show_blockpoints(block_points);

	// �⺻����
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			if (i == 4 && j > 8 && j < 21) {
				graphic[i][j] = new std::string("��");
			}
			else if (i == 25 && j > 8 && j < 21) {
				graphic[i][j] = new std::string("��");
			}
			else if (j == 9 && i > 3 && i < 26) {
				graphic[i][j] = new std::string("��");
			}
			else if (j == 20 && i > 3 && i < 26) {
				graphic[i][j] = new std::string("��");
			}
			else graphic[i][j] = new std::string("  ");

		}
	}

	show_graphic(graphic);

	// �Ҵ�� �޸� ����
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			delete graphic[i][j];
		}
		delete[] graphic[i];
	}
	delete[] graphic;

	return 0;
}