//#include <iostream>
//#include <vector>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include <Windows.h>
//#include <conio.h>
//
//#pragma warning(disable : 4996) // warning pragma
//
//class GameUI {
//public:
//    static void gotoxy(int x, int y) {
//        COORD pos = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };
//        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//    }
//
//    static void GameTitle() {
//        const char* tetris[] = {
//            "■■■  ■■■  ■■■  ■■■    ■■■   ■■■",
//            "  ■    ■        ■     ■    ■    ■    ■",
//            "  ■    ■■■    ■     ■■■      ■     ■■■",
//            "  ■    ■        ■     ■   ■     ■          ■",
//            "  ■    ■■■    ■     ■    ■  ■■■   ■■■"
//        };
//
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0003);
//
//        for (int i = 0; i < 5; i++) {
//            gotoxy(10, 5 + i);
//            std::cout << tetris[i];
//            Sleep(200);
//        }
//
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
//
//        const char* instructions[] = {
//            "┌─<  Key Instructions  >─┐",
//            "│       HARD DROP    ↑    │",
//            "│       RIGHT        →    │",
//            "│       LEFT         ←    │",
//            "│       SOFT DROP    ↓    │",
//            "│       TURN       SPACE   │",
//            "│     YELLOW BlOCKS   0    │",
//            "│      GREEN BlOCKS   1    │",
//            "│      WHITE BlOCKS   2    │",
//            "│       BLUE BlOCKS   3    │",
//            "└─────────────┘"
//        };
//
//        for (int i = 0; i < 11; i++) {
//            gotoxy(10, 12 + i);
//            std::cout << instructions[i];
//        }
//
//        std::cout << "\n\n";
//        std::cout << "              Press any key to start...";
//        _getch();
//        system("cls");
//    }
//};
//
//typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
//
//void setcursortype(CURSOR_TYPE c) {
//    CONSOLE_CURSOR_INFO CurInfo;
//
//    switch (c) {
//    case NOCURSOR:
//        CurInfo.dwSize = 1;
//        CurInfo.bVisible = FALSE;
//        break;
//    case SOLIDCURSOR:
//        CurInfo.dwSize = 100;
//        CurInfo.bVisible = TRUE;
//        break;
//    case NORMALCURSOR:
//        CurInfo.dwSize = 20;
//        CurInfo.bVisible = TRUE;
//        break;
//    }
//    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
//}
//
//int spin(int n) {
//    return (n == 3) ? 0 : n + 1;
//}
//
//int anti_spin(int n) {
//    return (n == 0) ? 3 : n - 1;
//}
//
//void show_graphic(const std::vector<std::vector<std::string>>& p, int point) {
//    for (const auto& row : p) {
//        for (const auto& cell : row) {
//            std::cout << cell;
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "            현재점수 : " << point << std::endl;
//}
//
//int arrow(char key) {
//    switch (key) {
//    case 72: return 0;
//    case 75: return 1;
//    case 77: return 3;
//    case 80: return 2;
//    default: return -1;
//    }
//}
//
//int anti_arrow(char key) {
//    switch (key) {
//    case 72: return 0;
//    case 75: return 1;
//    case 77: return 3;
//    case 80: return 2;
//    default: return -1;
//    }
//}
//
//void nums_to_arr(std::vector<std::vector<int>>& p, int a, int b, int c, int d, int e, int f, int g, int h) {
//    p = { {a, b}, {c, d}, {e, f}, {g, h} };
//}
//
//void block_type_to_co(std::vector<std::vector<int>>& co, int type) {
//    switch (type) {
//    case 0: nums_to_arr(co, 1, 1, 1, 0, 1, 2, 0, 1); break; // ■■■
//    case 1: nums_to_arr(co, 0, 1, 1, 1, 2, 1, 3, 1); break; // ■■■■
//    case 2: nums_to_arr(co, 0, 0, 1, 0, 1, 1, 1, 2); break; // ■■
//    case 3: nums_to_arr(co, 0, 1, 1, 0, 1, 1, 2, 1); break; //   ■■■
//    default: break;
//    }
//}
//
//void rotate_block(std::vector<std::vector<int>>& co, int a, int b) {
//    for (int i = 0; i < co.size(); i++) {
//        int temp = co[i][0];
//        co[i][0] = -co[i][1] + b + a;
//        co[i][1] = temp - a + b;
//    }
//}
//
//bool collision(const std::vector<std::vector<int>>& p, int x, int y, const std::vector<std::vector<int>>& co, int type) {
//    for (int i = 0; i < 4; i++) {
//        int a = x + co[i][0];
//        int b = y + co[i][1];
//
//        if (a < 0 || a >= p.size() || b < 0 || b >= p[0].size() || p[a][b] != -1) {
//            return true;
//        }
//    }
//
//    return false;
//}
//
//void rotate_block(std::vector<std::vector<int>>& co, int a, int b) {
//    for (int i = 0; i < co.size(); i++) {
//        int temp = co[i][0];
//        co[i][0] = -co[i][1] + b + a;
//        co[i][1] = temp + co[i][1] - a + b;
//    }
//}
//
//
//void delete_line(std::vector<std::vector<int>>& p, int& point) {
//    for (int i = p.size() - 1; i >= 0; i--) {
//        bool is_full = true;
//        for (int j = 0; j < p[i].size(); j++) {
//            if (p[i][j] == -1) {
//                is_full = false;
//                break;
//            }
//        }
//
//        if (is_full) {
//            point += 100;
//
//            for (int k = i; k >= 1; k--) {
//                p[k] = p[k - 1];
//            }
//            p[0].assign(p[0].size(), -1);
//            i++;
//        }
//    }
//}
//
//void draw_block(std::vector<std::vector<int>>& p, int& x, int& y, const std::vector<std::vector<int>>& co, int type) {
//    for (int i = 0; i < 4; i++) {
//        int a = x + co[i][0];
//        int b = y + co[i][1];
//        p[a][b] = type;
//    }
//}
//
//int main() {
//    GameUI::GameTitle();
//
//    const int row = 20;
//    const int col = 10;
//
//    std::vector<std::vector<int>> board(row, std::vector<int>(col, -1));
//    int x = 0;
//    int y = col / 2 - 1;
//    int pre_arrow = 2;
//
//    srand(static_cast<unsigned int>(time(0)));
//    int type = rand() % 4;
//    int arrow;
//    int point = 0;
//
//    setcursortype(NOCURSOR);
//
//    while (true) {
//        std::vector<std::vector<int>> coordinates(4, std::vector<int>(2));
//        block_type_to_co(coordinates, type);
//
//        GameUI::gotoxy(0, 0);
//        show_graphic(board, point);
//        draw_block(board, x, y, coordinates, type);
//
//        if (_kbhit()) {
//            arrow = arrow(_getch());
//            move_block(board, x, y, coordinates, type, arrow, pre_arrow);
//        }
//        else {
//            move_block(board, x, y, coordinates, type, pre_arrow, pre_arrow);
//        }
//
//        if (!move_block(board, x, y, coordinates, type, 2, pre_arrow)) {
//            break;
//        }
//
//        delete_line(board, point);
//        type = spin(type);
//        Sleep(100);
//        board = std::vector<std::vector<int>>(row, std::vector<int>(col, -1));
//    }
//
//    GameUI::gotoxy(0, row + 5);
//    std::cout << "Game Over!";
//    GameUI::gotoxy(0, row + 6);
//    std::cout << "Your Score: " << point;
//
//    setcursortype(NORMALCURSOR);
//
//    return 0;
//}
