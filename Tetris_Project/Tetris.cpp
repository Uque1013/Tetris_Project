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
//// ���� Ÿ��Ʋ ���
//class GameUI {
//public:
//	// gotoxy �Լ� ����
//	static void gotoxy(int x, int y) {
//		COORD pos = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };
//		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//	}
//
//	// ���� Ÿ��Ʋ
//	static void GameTitle() {
//		const char* tetris[] = {
//		"����  ����  ����  ����    ����   ����",
//		"  ��    ��        ��	 ��    ��    ��    ��",
//		"  ��    ����    ��    ����      ��     ����",
//		"  ��    ��        ��    ��   ��     ��          ��",
//		"  ��    ����    ��    ��    ��  ����   ����"
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
//		_getch(); // �ƹ� Ű�� �Է¹���
//		system("cls"); // �ܼ� â �����
//	}
//};
//
//class Block {
//
//};
//
//// Ŀ�� �� ���̰� �ϴ� �Լ�
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
//// ��輱 : ��
//// ��Ʈ���� ��� : ��
//// ��Ʈ���� �� �ϼ� ��� : ��
//// ��Ʈ���� ȭ�� ũ�� ���� : ��κ� 10*20 ���
//int main() {
//	srand((unsigned)time(NULL));
//	GameUI::GameTitle(); // ���� Ÿ��Ʋ
//	setcursortype(NOCURSOR); //Ŀ�� ����
//
//	return 0;
//}