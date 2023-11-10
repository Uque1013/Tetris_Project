#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <cstdlib> // rand
#include <ctime> // time
#include <conio.h>
#pragma warning(disable : 4996) warning pragma

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

// 편의상 구현
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

// 블록관련
void block_type_to_coors(std::vector<std::vector<int>>& p, int blocktype, int spinvalue) {
	p.resize(4, std::vector<int>(2));
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
			nums_to_arr(p, 0, 0, 0, 1, 1, -1, 1, 0);
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
void put_block(std::vector<std::vector<std::string>>& p, std::vector<std::vector<int>>& q, int a, int b) {
	for (int i = 0; i < 4; i++) {
		int tenpi = a + q[i][0];
		int tenpj = b + q[i][1];
		p[tenpi][tenpj] = "■";
	}
}
void del_block(std::vector<std::vector<std::string>>& p, std::vector<std::vector<int>>& q, int a, int b) {
	for (int i = 0; i < 4; i++) {
		int tenpi = a + q[i][0];
		int tenpj = b + q[i][1];
		p[tenpi][tenpj] = "■";
	}
}
void move_coors(std::vector<int> location, int key) {
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



// 테트리스 화면 크기 구상 : 대부분 10*20 사용
int main() {
	srand((unsigned)time(NULL));
	// GameTitle();

	// ▩□■
	int i = 0, j = 0, key, a, b;
	int testi, testj;
	std::vector<std::vector<std::string>> graphic(30, std::vector<std::string>(30)); // 문자열을 원소로 갖는 2차원 배열
	std::vector<std::vector<int>> block_coors(4, std::vector<int>(2)); // 블럭의 상대좌표틀
	std::vector<int> location(2); // 블럭 중심의 위치


	// 기본 설정
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			if (i == 4 && j > 8 && j < 21) graphic[i][j] = "▩";
			else if (i == 25 && j > 8 && j < 21) graphic[i][j] = "▩";
			else if (j == 9 && i > 3 && i < 26) graphic[i][j] = "▩";
			else if (j == 20 && i > 3 && i < 26) graphic[i][j] = "▩";
			else graphic[i][j] = "  ";
		}
	}

	location[0] = 15;
	location[1] = 15; // test용 좌표
	printf("블럭 타입을 입력해 주십시오: ");
	scanf_s("%d", &testi);
	testj = 0;
	block_type_to_coors(block_coors, testi, testj);
	put_block(graphic, block_coors, location[0], location[1]);
	show_graphic(graphic);

	while (1) {
		if (kbhit()) {
			key = getch();
			if (key == 224) { // 방향키가 입력된 경우
				key = getch();
				del_block(graphic, block_coors, location[0], location[1]);
				move_coors(location, arrow(key));
				put_block(graphic, block_coors, location[0], location[1]);
				system("cls");
				show_graphic(graphic);
				printf("\n%d %d\n", location[0], location[1]);
			}
			else { // 블럭을 반 시계 방향으로 회전시키는 함수
				del_block(graphic, block_coors, location[0], location[1]);
				testj = spin(testj);
				block_type_to_coors(block_coors, testi, testj);
				put_block(graphic, block_coors, location[0], location[1]);
				system("cls");
				show_graphic(graphic);
			}
		}
	}

	// 할당된 메모리 해제 (std::vector는 자동으로 관리)
	return 0;
}