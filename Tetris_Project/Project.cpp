#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#pragma warning(disable : 4996) warning pragma

using namespace std;

// 게임 타이틀 출력
class GameUI {
public:
	// gotoxy 함수 로직
	static void gotoxy(int x, int y) {
		COORD pos = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	// 게임 타이틀
	static void GameTitle() {
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
			Sleep(200); // 0.2초에 한 줄씩 타이틀이 뜨게함
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);

		gotoxy(10, 12); cout << ("┌─<  Key Instructions    |    Block Colors >─┐");
		gotoxy(10, 13); cout << ("│       HARD DROP    ↑   |   YELLOW BLOCKS  0 │");
		gotoxy(10, 14); cout << ("│       RIGHT        →   |    GRENN BLOCKS  1 │");
		gotoxy(10, 15); cout << ("│       LEFT         ←   |    WHITE BLOCKS  2 │");
		gotoxy(10, 16); cout << ("│       SOFT DROP    ↓   |     BLUE BLOCKS  3 │");
		gotoxy(10, 17); cout << ("│       TURN       SPACE  |      RED BLOCKS  4 │");
		gotoxy(10, 18); cout << ("│       RESTART      R    |   PURPLE BLOCKS  5 │");
		gotoxy(10, 19); cout << ("│       EXIT        ESC   |     MINT BLOCKS  6 │");
		gotoxy(10, 20); cout << ("└───────────────────────┘");

		cout << "\n\n";
		cout << "		      Press any key to start...";
		_getch(); // 아무 키나 입력받음
		system("cls"); // 콘솔 창 지우기
	}
};

// 커서 안 보이게 하는 함수
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void setcursortype(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// 점수
int point = 0;

// 2차원 벡터 초기화 및 주어진 8개의 정수를 해당 벡터에 할당 (블록의 상대좌표를 구현할 때 편의하게 사용하기 위해 작성함)
void nums_to_arr(vector<vector<int>>& p, int a, int b, int c, int d, int e, int f, int g, int h) {
	p = { {a, b}, {c, d}, {e, f}, {g, h} };
}
// 시계 방향으로 회전
int spin(int n) {
	return (n == 3) ? 0 : n + 1;
}
// 반 시계 방향으로 회전 (벽면에 닿거나 다른 블록들과 닿았을 때 발현)
int anti_spin(int n) {
	return (n == 0) ? 3 : n - 1;
}

// 블록 띄우는 함수
void show_graphic(const vector<vector<string>>& p) {
	for (const auto& row : p) {
		for (const auto& cell : row) {
			cout << cell;
		}
		cout << endl;
	}
	cout << "			현재점수 : " << point << endl;
}
// 방향키 입력
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

/* ------------블록관련-------------- */
// 블록 정보를 받으면 중심기준 점들의 위치를 반환
// 블록의 종류는 총 6개로, 블록의 상태를 입력받으면 상대좌표를 리턴함
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
// 좌표, 블록점좌표배열, 기준점, 색상을 받으면 블록을 그래픽에 찍음
void put_block(vector<vector<string>>& p, vector<vector<int>>& q, int a, int b, int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++) {
		int tenpi = a + q[i][0];
		int tenpj = b + q[i][1];
		if (color == 0) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else if (color == 1) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}
		else if (color == 2) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		else if (color == 3) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		else if (color == 4) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		else if (color == 5) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		else if (color == 6) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		p[tenpi][tenpj] = "■"; // 블록 크기만큼 색상 변경
	}
}
// 좌표, 블록점좌표배열, 기준점을 받으면 블록을 그래픽에서 지움
void del_block(vector<vector<string>>& p, vector<vector<int>>& q, int a, int b) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 4; i++) {
		int tenpi = a + q[i][0];
		int tenpj = b + q[i][1];
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // 기본 텍스트 속성
		p[tenpi][tenpj] = "  ";
	}
}
// 기준점, 방향키를 입력받으면 기준점을 변환
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
// 블록상대좌표, 기준점을 입력받으면 그래픽에 찍을 수 있는지를 판단
int can_put(std::vector<std::vector<std::string>>& graphic, std::vector<std::vector<int>>& block_coors, std::vector<int>& location) {
	int a, b, i;
	for (i = 0; i < 4; i++) {
		a = location[0] + block_coors[i][0];
		b = location[1] + block_coors[i][1]; // a, b가 각각의 사각형 좌표에 대응
		if ((b < 10) || (b > 19)) return 0;
		if (graphic[a][b] != "  ") return 0;
	}
	return 1;
}


/* ------------게임진행-------------- */
// 그래픽, 행을 입력받으면 해당 행이 꽉 찼는지 판단
int is_row_full(std::vector<std::vector<std::string>>& graphic, int r) { // r = row
	int j;
	for (j = 10; j < 20; j++) if (graphic[r][j] == "  ")return 0;
	return 1;
}
// 그래픽을 받으면 줄을 지워주며 그래픽도 보여줌
void row_clear(std::vector<std::vector<std::string>>& graphic) {
	int i, j, k, high = 4;
	for (i = 24; i > high; i--) {
		if (is_row_full(graphic, i)) { // i열이 꽉찼으면
			graphic[i][10] = "▣";
			graphic[i][11] = "▣";
			graphic[i][12] = "▣";
			system("cls");
			show_graphic(graphic);
			graphic[i][13] = "▣";
			graphic[i][14] = "▣";
			graphic[i][15] = "▣";
			system("cls");
			show_graphic(graphic);
			graphic[i][16] = "▣";
			graphic[i][17] = "▣";
			system("cls");
			show_graphic(graphic);
			graphic[i][18] = "▣";
			graphic[i][19] = "▣";
			system("cls");
			show_graphic(graphic);
			for (k = i; k > high; k--) { // i열부터 위로 쭉
				for (j = 10; j < 20; j++) { // 모든 열에
					graphic[k][j] = graphic[k - 1][j];
				}
			}
			i++;
			high;
			point += 1000; // 한 줄씩 사라질 때마다 포인트가 1000점씩 올라감
		}
	}
}

// 경계선 : ▩
// 테트리스 블록 : ■
// 테트리스 줄 완성 블록 : ▣
// 테트리스 화면 크기 구상 : 대부분 10*20 사용
int main() {
	srand((unsigned)time(NULL));
	GameUI::GameTitle(); // 게임 타이틀
	setcursortype(NOCURSOR); //커서 없앰 

	int blockColor = 0; // 초기 블록 색상 설정 (0: 노란색, 1: 초록색)
	int i = 0, j = 0, key, a, b;
	int blocktype, spinvalue, next_blocktype, next_spinvalue;
	std::vector<std::vector<std::string>> graphic(30, std::vector<std::string>(30)); // 문자열을 원소로 갖는 2차원 배열
	std::vector<std::vector<int>> block_coors(4, std::vector<int>(2)); // 블럭의 상대좌표틀
	std::vector<std::vector<int>> next_block_coors(4, std::vector<int>(2));
	std::vector<int> location(2); // 블럭 중심의 위치
	std::vector<int> tl(2); // 블럭 중심의 위치
	tl[0] = 7;
	tl[1] = 24;

	clock_t start;

	// 테트리스 블록 가두는 벽
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			if (i == 25 && j > 8 && j < 21) graphic[i][j] = "▩";
			else if (j == 9 && i > 4 && i < 26) graphic[i][j] = "▩";
			else if (j == 20 && i > 4 && i < 26) graphic[i][j] = "▩";
			else graphic[i][j] = "  ";
		}
	}

	location[0] = 4;
	location[1] = 14; // 기준점이 생성되는 점
	blocktype = rand() % 6;
	spinvalue = rand() % 4;
	next_blocktype = rand() % 6; // 다음 블록 타입 
	next_spinvalue = rand() % 4;
	block_type_to_coors(block_coors, blocktype, spinvalue);
	block_type_to_coors(next_block_coors, next_blocktype, next_spinvalue);
	put_block(graphic, block_coors, location[0], location[1], blockColor);
	put_block(graphic, next_block_coors, 7, 24, blockColor);
	system("cls"); // 콘솔창을 지우고 다시 그림
	show_graphic(graphic);
	start = clock();

	while (1) {
		// 키가 눌린 경우
		if (kbhit()) {
			key = getch();

			// ESC 키가 눌린 경우
			if (key == 27) {
				system("cls");
				cout << "게임을 종료하시겠습니까? (Y/N): ";

				// 사용자의 응답 확인
				char response;
				cin >> response;
				if (response == 'Y' || response == 'y') {
					cout << "게임을 종료합니다." << endl;
					cout << "득점 : " << point << endl;
					break;
				}
				else {
					// 게임 계속 진행
					system("cls");
					show_graphic(graphic);
				}
			}

			if (key == '0') { // 노란색 블록
				blockColor = 0;
			}
			else if (key == '1') { // 초록색 블록
				blockColor = 1;
			}
			else if (key == '2') { // 흰색 블록
				blockColor = 2;
			}
			else if (key == '3') { // 파랑색 블록 
				blockColor = 3;
			}
			else if (key == '4') { // 빨강색 블록 
				blockColor = 4;
			}
			else if (key == '5') { // 보라색 블록 
				blockColor = 5;
			}
			else if (key == '6') { // 민트색 블록 
				blockColor = 6;
			}

			// 방향키가 입력된 경우
			if (key == 224) {
				key = getch();

				// 상 키가 눌린 경우
				if (arrow(key) == 0) {
					del_block(graphic, block_coors, location[0], location[1]); // 블록 지우기
					while (1) {
						move_coors(location, 2); // 기준점을 한칸 내림
						if (can_put(graphic, block_coors, location)) { // 변경된 기준점에 놓을 수 있다면
							continue;
						}
						else { // 변경된 기준점에 놓을 수 없다면
							move_coors(location, 0); // 기준점 원상복귀
							put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭놓기
							row_clear(graphic);
							location[0] = 4;
							location[1] = 14; // 기준점이 생성되는 점
							del_block(graphic, next_block_coors, 7, 24);
							blocktype = next_blocktype;
							spinvalue = next_spinvalue;
							next_blocktype = rand() % 6;
							next_spinvalue = rand() % 4; // 랜덤 블록정보입력
							block_type_to_coors(next_block_coors, next_blocktype, next_spinvalue); // 블록좌표 파악

							if (can_put(graphic, next_block_coors, location)) { // 새 블록을 놓을 수 있다면
								put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭 놓기
								put_block(graphic, next_block_coors, 7, 24, blockColor);
								system("cls"); // 콘솔창을 지우고 다시 그림
								show_graphic(graphic); // 다시 찍고 보여줌
							}
							else { // 새 블록 생성할 자리가 없음
								put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭 놓기
								put_block(graphic, next_block_coors, 7, 24, blockColor);
								system("cls"); // 콘솔창을 지우고 다시 그림
								show_graphic(graphic); // 다시 찍고 보여줌
								printf("			게임오버");
								return 0;
							}
							break;
						}
					}
				}
				// 좌, 우, 하 키가 눌린 경우
				else {
					del_block(graphic, block_coors, location[0], location[1]); // 블럭 지우기
					move_coors(location, arrow(key)); // 기준점을 움직임
					if (can_put(graphic, block_coors, location)) { // 변경된 기준점에 놓을 수 있다면
						put_block(graphic, block_coors, location[0], location[1], blockColor); // 블록 놓기
						system("cls");
						show_graphic(graphic); // 블록 보여줌 
					}
					else { // 변경된 기준점에 놓을 수 없다면
						if (arrow(key) == 2) { // 아래로 막힌 경우
							move_coors(location, 0); // 기준점 원상복귀
							put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭놓기
							row_clear(graphic);
							location[0] = 4;
							location[1] = 14; // 기준점이 생성되는 점
							del_block(graphic, next_block_coors, 7, 24);
							blocktype = next_blocktype;
							spinvalue = next_spinvalue;
							next_blocktype = rand() % 6;
							next_spinvalue = rand() % 4; // 랜덤 블록정보입력
							block_type_to_coors(next_block_coors, next_blocktype, next_spinvalue); // 블록좌표 파악

							if (can_put(graphic, next_block_coors, location)) { // 새 블록을 놓을 수 있다면
								put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭 놓기
								put_block(graphic, next_block_coors, 7, 24, blockColor);
								system("cls"); // 콘솔창을 지우고 다시 그림
								show_graphic(graphic); // 다시 찍고 보여줌
							}
							else { // 새 블록 생성할 자리가 없음
								put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭 놓기
								put_block(graphic, next_block_coors, 7, 24, blockColor);
								system("cls"); // 콘솔창을 지우고 다시 그림
								show_graphic(graphic); // 다시 찍고 보여줌
								printf("			게임오버");
								return 0;
							}
						}
						else { // 좌우가 막힌 경우
							move_coors(location, anti_arrow(key)); // 기준점 원상복귀
							put_block(graphic, block_coors, location[0], location[1], blockColor);
							system("cls"); // 콘솔창을 지우고 다시 그림
							show_graphic(graphic); // 다시 찍고 보여줌
						}
					}
				}
			}
			else { // 회전키가 입력된 경우
				del_block(graphic, block_coors, location[0], location[1]); // 블록 지우기
				spinvalue = spin(spinvalue); // 블록회전상수를 키움
				block_type_to_coors(block_coors, blocktype, spinvalue); // 그거에 맞춰서 블록좌표들을 변환하고
				if (can_put(graphic, block_coors, location)) { // 놓을 수 있으면
					put_block(graphic, block_coors, location[0], location[1], blockColor);
					system("cls"); // 콘솔창을 지우고 다시 그림
					show_graphic(graphic); // 블록 보여주기
				}
				else { // 놓을 수 없다면
					spinvalue = anti_spin(spinvalue); // 블록회전상수를 1줄이고(원상복귀)
					block_type_to_coors(block_coors, blocktype, spinvalue);
					put_block(graphic, block_coors, location[0], location[1], blockColor); // 블록 찍은 다음에
					system("cls"); // 콘솔창을 지우고 다시 그림
					show_graphic(graphic); // 블록 보여주기
				}
			}
		}

		// 단위시간마다 블록을 떨굼
		if ((clock() - start) > 1499) {
			start = clock();
			del_block(graphic, block_coors, location[0], location[1]); // 블록을 지우고
			move_coors(location, 2); // 기준점을 움직임
			if (can_put(graphic, block_coors, location)) { // 변경된 기준점에 놓을 수 있으면
				put_block(graphic, block_coors, location[0], location[1], blockColor);
				system("cls"); // 콘솔창을 지우고 다시 그림
				show_graphic(graphic);
			}
			else { // 변경된 기준점에 놓을 수 없다면
				move_coors(location, 0); // 기준점 원상복귀
				put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭놓기
				row_clear(graphic);
				location[0] = 4;
				location[1] = 14; // 기준점이 생성되는 점
				del_block(graphic, next_block_coors, 7, 24);
				blocktype = next_blocktype;
				spinvalue = next_spinvalue;
				next_blocktype = rand() % 6;
				next_spinvalue = rand() % 4; // 랜덤 블록정보입력
				block_type_to_coors(next_block_coors, next_blocktype, next_spinvalue); // 블록좌표 파악
				if (can_put(graphic, next_block_coors, location)) { // 새 블록을 놓을 수 있다면
					put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭 놓기
					put_block(graphic, next_block_coors, 7, 24, blockColor);
					system("cls"); // 콘솔창을 지우고 다시 그림
					show_graphic(graphic); // 다시 찍고 보여줌
				}
				else { // 새 블록 생성할 자리가 없음
					put_block(graphic, block_coors, location[0], location[1], blockColor); // 블럭 놓기
					put_block(graphic, next_block_coors, 7, 24, blockColor);
					system("cls"); // 콘솔창을 지우고 다시 그림
					show_graphic(graphic); // 다시 찍고 보여줌
					printf("			게임오버");
					return 0;
				}
			}
		}
	}

	// 할당된 메모리 해제 (std::vector는 자동으로 관리)
	return 0;
}