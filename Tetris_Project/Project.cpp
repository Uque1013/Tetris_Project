#include <iostream>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <string>
#include <cstdlib> // rand
#include <ctime> // time
#include <conio.h>
#pragma warning(disable : 4996) warning pragma

using namespace std;

//// Ű���尪
//# define LEFT 75 // �������� �̵�
//# define RIGHT 77 // ���������� �̵�
//# define UP 72	// ȸ��
//# define DOWN 80 // õõ�� drop
//# define SPACE 32 // ������ drop
//# define ESC 27 // ���� ���� 

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

	int x, y; // ��ǥ
	int type; // ��� ����
	int rotation; // ��� ȸ����
	int next_type; // ���� ���
	int getColor(int num); // ��� ���� �Լ�
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

// ���ǻ� ����
void nums_to_arr(std::vector<std::vector<int>>& p, int a, int b, int c, int d, int e, int f, int g, int h) {
	p[0][0] = a;
	p[0][1] = b;
	p[1][0] = c;
	p[1][1] = d;
	p[2][0] = e;
	p[2][1] = f;
	p[3][0] = g;
	p[3][1] = h;
}
int spin(int n) {
	if (n == 3) return 0;
	else return n + 1;
}
int anti_spin(int n) {
	if (n == 0) return 3;
	else return n - 1;
}

// ��� ���� �Լ�
void show_graphic(std::vector<std::vector<std::string>>& p) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			std::cout << p[i][j];
		}
		std::cout << std::endl;
	}
}
int arrow(char key) {
	switch (key) {
	case 72: return 0;
	case 75: return 1;
	case 77: return 3;
	case 80: return 2;
	default: return -1;
	}
}
int anti_arrow(char key) {
	switch (key) {
	case 72: return 0;
	case 75: return 1;
	case 77: return 3;
	case 80: return 2;
	default: return -1;
	}
}

void show_coords(std::vector<std::vector<int>>& block_coors, std::vector<int>& location) {
	int i;
	for (i = 0; i < 4; i++) {
		printf("%3d%3d", location[0] + block_coors[i][0], location[1] + block_coors[i][1]);
	}
}

/* ------------��ϰ���-------------- */
// ��� ������ ������ �߽ɱ��� ������ ��ġ�� ��ȯ
void block_type_to_coors(std::vector<std::vector<int>>& p, int blocktype, int spinvalue) {
	switch (blocktype) {
	case 0:
		switch (spinvalue) {
		case 0:
			nums_to_arr(p, -1, 0, 0, 0, 1, 0, 2, 0);
			return;
		case 1:
			nums_to_arr(p, 0, -1, 0, 0, 0, 1, 0, 2);
			return;
		case 2:
			nums_to_arr(p, -1, 0, 0, 0, 1, 0, 2, 0);
			return;
		case 3:
			nums_to_arr(p, 0, -1, 0, 0, 0, 1, 0, 2);
			return;
		}
	case 1:
		switch (spinvalue) {
		case 0:
			nums_to_arr(p, -1, -1, 0, -1, 0, 0, 0, 1);
			return;
		case 1:
			nums_to_arr(p, -1, 0, 0, 0, 1, 0, 1, -1);
			return;
		case 2:
			nums_to_arr(p, 0, -1, 0, 0, 0, 1, 1, 1);
			return;
		case 3:
			nums_to_arr(p, -1, 0, -1, 1, 0, 0, 1, 0);
			return;
		}
	case 2:
		switch (spinvalue) {
		case 0:
			nums_to_arr(p, 0, -1, 0, 0, 0, 1, -1, 1);
			return;
		case 1:
			nums_to_arr(p, -1, -1, -1, 0, 0, 0, 1, 0);
			return;
		case 2:
			nums_to_arr(p, 1, -1, 0, -1, 0, 0, 0, 1);
			return;
		case 3:
			nums_to_arr(p, -1, 0, 0, 0, 1, 0, 1, 1);
			return;
		}
	case 3:
		switch (spinvalue) {
		case 0:
			nums_to_arr(p, -1, 0, 0, 0, 0, 1, 1, 1);
			return;
		case 1:
			nums_to_arr(p, 0, -1, 0, 0, -1, 0, -1, 1);
			return;
		case 2:
			nums_to_arr(p, -1, 0, 0, 0, 0, 1, 1, 1);
			return;
		case 3:
			nums_to_arr(p, 0, 0, 0, 1, 1, -1, 1, 0);
			return;
		}
	case 4:
		switch (spinvalue) {
		case 0:
			nums_to_arr(p, 0, 0, 0, 1, -1, 1, 1, 0);
			return;
		case 1:
			nums_to_arr(p, -1, -1, -1, 0, 0, 0, 0, 1);
			return;
		case 2:
			nums_to_arr(p, 0, 0, 0, 1, -1, 1, 1, 0);
			return;
		case 3:
			nums_to_arr(p, -1, -1, -1, 0, 0, 0, 0, 1);
			return;
		}
	case 5:
		switch (spinvalue) {
		case 0:
			nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		case 1:
			nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		case 2:
			nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		case 3:
			nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
			return;
		}
	}
}
// ��ǥ, �������ǥ�迭, �������� ������ ����� �׷��ȿ� ����
void put_block(std::vector<std::vector<std::string>>& p, std::vector<std::vector<int>>& q, int a, int b) {
	for (int i = 0; i < 4; i++) {
		int tenpi = a + q[i][0];
		int tenpj = b + q[i][1];
		p[tenpi][tenpj] = "��";
	}
}
// ��ǥ, �������ǥ�迭, �������� ������ ����� �׷��ȿ��� ����
void del_block(std::vector<std::vector<std::string>>& p, std::vector<std::vector<int>>& q, int a, int b) {
	for (int i = 0; i < 4; i++) {
		int tenpi = a + q[i][0];
		int tenpj = b + q[i][1];
		p[tenpi][tenpj] = "  ";
	}
}
// ������, ����Ű�� �Է¹����� �������� ��ȯ
void move_coors(std::vector<int>& location, int key) {
	int i;

	switch (key) {
	case 0:
		location[0] -= 1;
		return;
	case 1:
		location[1] -= 1;
		return;
	case 2:
		location[0] += 1;
		return;
	case 3:
		location[1] += 1;
		return;
	}
}
// ��ϻ����ǥ, �������� �Է¹����� �׷��ȿ� ���� �� �ִ����� �Ǵ�
int can_put(std::vector<std::vector<std::string>>& graphic, std::vector<std::vector<int>>& block_coors, std::vector<int>& location) {
	int a, b, i;
	for (i = 0; i < 4; i++) {
		a = location[0] + block_coors[i][0];
		b = location[1] + block_coors[i][1]; // a, b�� ������ �簢�� ��ǥ�� ����
		if (graphic[a][b] != "  ") return 0;
	}
	return 1;
}



// ��Ʈ���� ȭ�� ũ�� ���� : ��κ� 10*20 ���
int main() {
	srand((unsigned)time(NULL));
	// GameTitle();

	// �̡��
	int i = 0, j = 0, key, a, b;
	int testi, testj;
	std::vector<std::vector<std::string>> graphic(30, std::vector<std::string>(30)); // ���ڿ��� ���ҷ� ���� 2���� �迭
	std::vector<std::vector<int>> block_coors(4, std::vector<int>(2)); // ���� �����ǥƲ
	std::vector<int> location(2); // �� �߽��� ��ġ
	clock_t start;

	// �⺻ ����
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			if (i == 4 && j > 8 && j < 21) graphic[i][j] = "��";
			else if (i == 25 && j > 8 && j < 21) graphic[i][j] = "��";
			else if (j == 9 && i > 3 && i < 26) graphic[i][j] = "��";
			else if (j == 20 && i > 3 && i < 26) graphic[i][j] = "��";
			else graphic[i][j] = "  ";
		}
	}

	location[0] = 15;
	location[1] = 15; // test�� ��ǥ
	printf("�� Ÿ���� �Է��� �ֽʽÿ�: ");
	scanf_s("%d", &testi);
	testj = 0;
	block_type_to_coors(block_coors, testi, testj);
	put_block(graphic, block_coors, location[0], location[1]);
	system("cls"); // �ܼ�â�� ����� �ٽ� �׸�
	show_graphic(graphic);
	start = clock();

	while (1) {
		if (kbhit()) {
			key = getch();
			if (key == 224) { // ����Ű�� �Էµ� ���
				key = getch();
				del_block(graphic, block_coors, location[0], location[1]); // �� �����
				move_coors(location, arrow(key)); // �������� ������
				if (can_put(graphic, block_coors, location)) { // ����� �������� ���� �� �ִٸ�
					put_block(graphic, block_coors, location[0], location[1]);
					system("cls"); // �ܼ�â�� ����� �ٽ� �׸�
					show_graphic(graphic);
					
				}
				else { // ����� �������� ���� �� ���ٸ�
					move_coors(location, anti_arrow(key)); // ������ ���󺹱�
					put_block(graphic, block_coors, location[0], location[1]);
					system("cls"); // �ܼ�â�� ����� �ٽ� �׸�
					show_graphic(graphic); // �ٽ� ��� ������
				}
				
			}
			else { // ȸ��Ű�� �Էµ� ���
				del_block(graphic, block_coors, location[0], location[1]); // ��� �����
				testj = spin(testj); // ���ȸ������� Ű��
				block_type_to_coors(block_coors, testi, testj); // �װſ� ���缭 �����ǥ���� ��ȯ�ϰ�
				if (can_put(graphic, block_coors, location)) { // ���� �� ������
					put_block(graphic, block_coors, location[0], location[1]);
					system("cls"); // �ܼ�â�� ����� �ٽ� �׸�
					show_graphic(graphic); // ��� �����ֱ�
					show_coords(block_coors, location); // test�� ��ǥȮ��
				}
				else { // ���� �� ���ٸ�
					testj = anti_spin(testj); // ���ȸ������� 1���̰�(���󺹱�)
					put_block(graphic, block_coors, location[0], location[1]); // ��� ���� ������
					system("cls"); // �ܼ�â�� ����� �ٽ� �׸�
					show_graphic(graphic); // ��� �����ֱ�
					show_coords(block_coors, location); // test�� ��ǥȮ��
				}
				
			}
		}
		if (0/*(clock() - start) > 999*/) { // �����ð����� ����� ����
			start = clock();
			del_block(graphic, block_coors, location[0], location[1]);
			move_coors(location, 2);
			put_block(graphic, block_coors, location[0], location[1]);
			system("cls"); // �ܼ�â�� ����� �ٽ� �׸�
			show_graphic(graphic);
		}
	}

	// �Ҵ�� �޸� ���� (std::vector�� �ڵ����� ����)
	return 0;
}