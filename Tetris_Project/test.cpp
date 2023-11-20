//#include <iostream>
//#include <vector>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include <Windows.h>
//#include <conio.h>
//#pragma warning(disable : 4996) // warning pragma
//
//using namespace std;
//
//class TetrisGame {
//private:
//	vector<vector<string>> graphic;
//	vector<string> p;
//	int point;
//
//public:
//	TetrisGame() : point(0) {
//		// 게임 초기화 로직
//		initializeGraphic();
//	}
//
//	void initializeGraphic() {
//		// 그래픽 초기화 로직
//		graphic.resize(30, vector<string>(30, "  "));
//		// 그래픽 초기 상태 설정
//	}
//
//	// 그래픽 출력 로직
//	void show_graphic() {
//		int i, j;
//		for (i = 0; i < 30; i++) {
//			for (j = 0; j < 30; j++) {
//				cout << graphic[i][j];
//			}
//			cout << endl;
//		}
//		cout << "\n			현재점수 : " << point << endl;
//	}
//
//	void is_row_full() {
//
//	}
//
//	// 행을 지우는 로직
//	void row_clear() {
//		int i, j, k, high = 4;
//		for (i = 24; i > high; i--) {
//			if (is_row_full(graphic, i)) { // i열이 꽉찼으면
//				graphic[i][10] = "▣";
//				graphic[i][11] = "▣";
//				graphic[i][12] = "▣";
//				system("cls");
//				show_graphic(graphic);
//				graphic[i][13] = "▣";
//				graphic[i][14] = "▣";
//				graphic[i][15] = "▣";
//				system("cls");
//				show_graphic(graphic);
//				graphic[i][16] = "▣";
//				graphic[i][17] = "▣";
//				system("cls");
//				show_graphic(graphic);
//				graphic[i][18] = "▣";
//				graphic[i][19] = "▣";
//				system("cls");
//				show_graphic(graphic);
//				for (k = i; k > high; k--) { // i열부터 위로 쭉
//					for (j = 10; j < 20; j++) { // 모든 열에
//						graphic[k][j] = graphic[k - 1][j];
//					}
//				}
//				i++;
//				high;
//				point += 1000; // 한 줄씩 사라질 때마다 포인트가 1000점씩 올라감
//			}
//		}
//	}
//
//	// 다른 게임 로직 함수들 추가 가능
//};
//
//// 게임 타이틀 출력
//class GameUI {
//public:
//	// gotoxy 함수 로직
//    static void gotoxy(int x, int y) {
//        COORD pos = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };
//        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//    }
//
//	// 게임 타이틀
//    static void GameTitle() {
//		const char* tetris[] = {
//		"■■■  ■■■  ■■■  ■■■    ■■■   ■■■",
//		"  ■    ■        ■	 ■    ■    ■    ■",
//		"  ■    ■■■    ■    ■■■      ■     ■■■",
//		"  ■    ■        ■    ■   ■     ■          ■",
//		"  ■    ■■■    ■    ■    ■  ■■■   ■■■"
//		};
//
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0003);
//
//		for (int i = 0; i < 5; i++) {
//			gotoxy(10, 5 + i);
//			cout << tetris[i];
//			Sleep(200);
//		}
//
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
//
//		cout << "\n";
//		cout << "\n		    Press any key to start...";
//		_getch(); // 아무 키나 입력받음
//		system("cls"); // 콘솔 창 지우기
//    }
//};
//
//int main() {
//	srand((unsigned)time(NULL));
//
//	GameUI::GameTitle();
//
//	TetrisGame tetrisGame;
//	Block currentBlock;
//	Block nextBlock;
//
//	while (1) {
//		// 게임 루프
//		tetrisGame.show_graphic();
//
//		// 키 입력 및 게임 로직 처리
//
//		// 블록 이동, 회전 등의 로직은 Block 클래스에서 처리
//		// 게임 상태 및 그래픽 갱신은 TetrisGame 클래스에서 처리
//	}
//
//	return 0;
//}