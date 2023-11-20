//#include <iostream>
//#include <vector>
//#include <string>
//#include <cstdlib> // rand
//#include <ctime> // time
//#include <Windows.h>
//#include <time.h>
//#include <conio.h>
//#pragma warning(disable : 4996) warning pragma
//
//using namespace std;
//
//// 게임 타이틀 출력
//class GameUI {
//public:
//	// gotoxy 함수 로직
//	static void gotoxy(int x, int y) {
//		COORD pos = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };
//		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//	}
//
//	// 게임 타이틀
//	static void GameTitle() {
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
//	}
//};
//
//class Block {
//
//};
//
//// 커서 안 보이게 하는 함수
//typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
//void setcursortype(CURSOR_TYPE c) {
//	CONSOLE_CURSOR_INFO CurInfo;
//
//	switch (c) {
//	case NOCURSOR:
//		CurInfo.dwSize = 1;
//		CurInfo.bVisible = FALSE;
//		break;
//	case SOLIDCURSOR:
//		CurInfo.dwSize = 100;
//		CurInfo.bVisible = TRUE;
//		break;
//	case NORMALCURSOR:
//		CurInfo.dwSize = 20;
//		CurInfo.bVisible = TRUE;
//		break;
//	}
//	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
//}
//
//// 경계선 : ▩
//// 테트리스 블록 : ■
//// 테트리스 줄 완성 블록 : ▣
//// 테트리스 화면 크기 구상 : 대부분 10*20 사용
//int main() {
//	srand((unsigned)time(NULL));
//	GameUI::GameTitle(); // 게임 타이틀
//	setcursortype(NOCURSOR); //커서 없앰
//
//	return 0;
//}