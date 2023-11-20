//#include <iostream>
//#include <vector>
//#include <string>
//#include <cstdlib> // rand
//#include <ctime> // time
//#include <Windows.h>
//#include <time.h>
//#include <conio.h>
//#pragma warning(disable : 4996) // warning pragma
//
//#define ESC 27 // ESC 키에 해당하는 ASCII 값
//
//using namespace std;
//
//// 게임 타이틀 출력
//class GameUI {
//public:
//    // gotoxy 함수 로직
//    static void gotoxy(int x, int y) {
//        COORD pos = { static_cast<SHORT>(2 * x), static_cast<SHORT>(y) };
//        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//    }
//
//    // 게임 타이틀
//    static void GameTitle() {
//        const char* tetris[] = {
//        "■■■  ■■■  ■■■  ■■■    ■■■   ■■■",
//        "  ■    ■        ■	 ■    ■    ■    ■",
//        "  ■    ■■■    ■    ■■■      ■     ■■■",
//        "  ■    ■        ■    ■   ■     ■          ■",
//        "  ■    ■■■    ■    ■    ■  ■■■   ■■■"
//        };
//
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0003);
//
//        for (int i = 0; i < 5; i++) {
//            gotoxy(10, 5 + i);
//            cout << tetris[i];
//            Sleep(200);
//        }
//
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
//
//        cout << "\n";
//        cout << "\n		    Press any key to start...";
//        _getch(); // 아무 키나 입력받음
//        system("cls"); // 콘솔 창 지우기
//    }
//};
//
//// 커서 안 보이게 하는 함수
//typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
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
//// 블록의 색상을 지정하는 열거형
//enum BlockColor {
//    GREY = 8,  // 회색
//    RED = 12,  // 빨강 (유저 블록)
//    GREEN = 10, // 초록 (일반 블록)
//    YELLOW = 14 // 노랑 (방해 블록)
//};
//
//// 블록 클래스
//class Block {
//public:
//    int color;
//    vector<vector<int>> shape;
//
//    Block(int c, const vector<vector<int>>& s) : color(c), shape(s) {}
//};
//
//// 게임 매니저 클래스
//class GameManager {
//public:
//    vector<vector<Block>> board;
//    int point;
//
//    GameManager() : point(0) {
//        board.resize(30, vector<Block>(30, Block(GREEN, vector<vector<int>>(4, vector<int>(2, 0)))));
//        initializeBoard();
//    }
//
//    void initializeBoard() {
//        // 초기 게임 보드 설정
//        for (int i = 0; i < 30; i++) {
//            for (int j = 0; j < 30; j++) {
//                if (i == 25 && j > 8 && j < 21) board[i][j] = Block(GREY, vector<vector<int>>(4, vector<int>(2, 0)));
//                else if (j == 9 && i > 4 && i < 26) board[i][j] = Block(GREY, vector<vector<int>>(4, vector<int>(2, 0)));
//                else if (j == 20 && i > 4 && i < 26) board[i][j] = Block(GREY, vector<vector<int>>(4, vector<int>(2, 0)));
//            }
//        }
//    }
//
//    void show_graphic() {
//        system("cls");
//        for (int i = 0; i < 30; i++) {
//            for (int j = 0; j < 30; j++) {
//                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), board[i][j].color);
//                cout << "■";
//            }
//            cout << endl;
//        }
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
//        cout << "         현재점수 : " << point << endl;
//    }
//
//    void put_block(const Block& block, int x, int y) {
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 2; j++) {
//                if (block.shape[i][j] != 0) {
//                    board[x + i][y + j] = block;
//                }
//            }
//        }
//    }
//
//    void del_block(const Block& block, int x, int y) {
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 2; j++) {
//                if (block.shape[i][j] != 0) {
//                    board[x + i][y + j] = Block(GREY, vector<vector<int>>(4, vector<int>(2, 0)));
//                }
//            }
//        }
//    }
//
//    bool can_put(const Block& block, int x, int y) {
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j < 2; j++) {
//                if (block.shape[i][j] != 0) {
//                    if (x + i < 0 || x + i >= 30 || y + j < 0 || y + j >= 30) {
//                        return false;
//                    }
//                    if (board[x + i][y + j].color != GREY) {
//                        return false;
//                    }
//                }
//            }
//        }
//        return true;
//    }
//
//    void row_clear() {
//        // 행이 꽉 찬 경우 지우고 점수 획득
//        for (int i = 29; i >= 0; i--) {
//            bool isFull = true;
//            for (int j = 0; j < 30; j++) {
//                if (board[i][j].color == GREY) {
//                    isFull = false;
//                    break;
//                }
//            }
//            if (isFull) {
//                // 한 줄 지우기
//                for (int k = i; k > 0; k--) {
//                    for (int j = 0; j < 30; j++) {
//                        board[k][j] = board[k - 1][j];
//                    }
//                }
//                // 새로운 빈 줄 생성
//                for (int j = 0; j < 30; j++) {
//                    board[0][j] = Block(GREY, vector<vector<int>>(4, vector<int>(2, 0)));
//                }
//                // 점수 획득
//                point += 1000;
//            }
//        }
//    }
//
//    void nums_to_arr(std::vector<std::vector<int>>& p, int a, int b, int c, int d, int e, int f, int g, int h) {
//        p[0][0] = a;
//        p[0][1] = b;
//        p[1][0] = c;
//        p[1][1] = d;
//        p[2][0] = e;
//        p[2][1] = f;
//        p[3][0] = g;
//        p[3][1] = h;
//    }
//
//    void block_type_to_coors(std::vector<std::vector<int>>& p, int blocktype, int spinvalue) {
//        switch (blocktype) {
//        case 0:
//            switch (spinvalue) {
//            case 0:
//                nums_to_arr(p, -1, 0, 0, 0, 1, 0, 2, 0);
//                return;
//            case 1:
//                nums_to_arr(p, 0, -1, 0, 0, 0, 1, 0, 2);
//                return;
//            case 2:
//                nums_to_arr(p, -1, 0, 0, 0, 1, 0, 2, 0);
//                return;
//            case 3:
//                nums_to_arr(p, 0, -1, 0, 0, 0, 1, 0, 2);
//                return;
//            }
//        case 1:
//            switch (spinvalue) {
//            case 0:
//                nums_to_arr(p, -1, -1, 0, -1, 0, 0, 0, 1);
//                return;
//            case 1:
//                nums_to_arr(p, -1, 0, 0, 0, 1, 0, 1, -1);
//                return;
//            case 2:
//                nums_to_arr(p, 0, -1, 0, 0, 0, 1, 1, 1);
//                return;
//            case 3:
//                nums_to_arr(p, -1, 0, -1, 1, 0, 0, 1, 0);
//                return;
//            }
//        case 2:
//            switch (spinvalue) {
//            case 0:
//                nums_to_arr(p, 0, -1, 0, 0, 0, 1, -1, 1);
//                return;
//            case 1:
//                nums_to_arr(p, -1, -1, -1, 0, 0, 0, 1, 0);
//                return;
//            case 2:
//                nums_to_arr(p, 1, -1, 0, -1, 0, 0, 0, 1);
//                return;
//            case 3:
//                nums_to_arr(p, -1, 0, 0, 0, 1, 0, 1, 1);
//                return;
//            }
//        case 3:
//            switch (spinvalue) {
//            case 0:
//                nums_to_arr(p, -1, 0, 0, 0, 0, 1, 1, 1);
//                return;
//            case 1:
//                nums_to_arr(p, 0, -1, 0, 0, -1, 0, -1, 1);
//                return;
//            case 2:
//                nums_to_arr(p, -1, 0, 0, 0, 0, 1, 1, 1);
//                return;
//            case 3:
//                nums_to_arr(p, 0, 0, 0, 1, 1, -1, 1, 0);
//                return;
//            }
//        case 4:
//            switch (spinvalue) {
//            case 0:
//                nums_to_arr(p, 0, 0, 0, 1, -1, 1, 1, 0);
//                return;
//            case 1:
//                nums_to_arr(p, -1, -1, -1, 0, 0, 0, 0, 1);
//                return;
//            case 2:
//                nums_to_arr(p, 0, 0, 0, 1, -1, 1, 1, 0);
//                return;
//            case 3:
//                nums_to_arr(p, -1, -1, -1, 0, 0, 0, 0, 1);
//                return;
//            }
//        case 5:
//            switch (spinvalue) {
//            case 0:
//                nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
//                return;
//            case 1:
//                nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
//                return;
//            case 2:
//                nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
//                return;
//            case 3:
//                nums_to_arr(p, 0, 0, 0, 1, 1, 0, 1, 1);
//                return;
//            }
//        }
//    }
//
//    // 기준점, 방향키를 입력받으면 기준점을 변환
//    void move_coors(std::vector<int>& location, int key) {
//        int i;
//
//        switch (key) {
//        case 0:
//            location[0] -= 1;
//            return;
//        case 1:
//            location[1] -= 1;
//            return;
//        case 2:
//            location[0] += 1;
//            return;
//        case 3:
//            location[1] += 1;
//            return;
//        }
//    }
//   
//
//    void generateRandomBlock() {
//        Block randomBlock(YELLOW, vector<vector<int>>(4, vector<int>(2, 0)));
//        // 랜덤한 블록 형태 생성 (예: 2x2 블록)
//        randomBlock.shape[0][0] = 1;
//        randomBlock.shape[0][1] = 1;
//        randomBlock.shape[1][0] = 1;
//        randomBlock.shape[1][1] = 1;
//
//        int startY = rand() % 30; // 랜덤한 시작 Y 좌표
//        put_block(randomBlock, 0, startY);
//    }
//};
//
//int main() {
//    srand((unsigned)time(NULL));
//    GameUI::GameTitle();
//    setcursortype(NOCURSOR);
//
//    GameManager gameManager;
//
//    int key;
//    int blocktype, spinvalue;
//    int next_blocktype, next_spinvalue;
//
//    clock_t start = clock();
//    vector<int> location = { 4, 14 };
//    vector<vector<int>> block_coors(4, vector<int>(2, 0));
//    vector<vector<int>> next_block_coors(4, vector<int>(2, 0));
//
//    next_blocktype = rand() % 6;
//    next_spinvalue = rand() % 4;
//    gameManager.block_type_to_coors(next_block_coors, next_blocktype, next_spinvalue);
//
//    while (1) {
//        if (_kbhit()) {
//            key = _getch();
//            if (key == ESC) {
//                exit(1);
//            }// 방향키가 입력된 경우
//            if (key == 224) {
//                key = getch();
//
//                // 상 키가 눌린 경우
//                if (key == 0) {
//                    gameManager.del_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블록 지우기
//                    while (1) {
//                        gameManager.move_coors(location, 2); // 기준점을 한칸 내림
//                        if (gameManager.can_put(graphic, block_coors, location)) { // 변경된 기준점에 놓을 수 있다면
//                            continue;
//                        }
//                        else { // 변경된 기준점에 놓을 수 없다면
//                            move_coors(location, 0); // 기준점 원상복귀
//                            gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블럭놓기
//                            gameManager.row_clear(graphic);
//                            location[0] = 4;
//                            location[1] = 14; // 기준점이 생성되는 점
//                            gameManager.del_block(graphic, next_block_coors, 7, 24);
//                            blocktype = next_blocktype;
//                            spinvalue = next_spinvalue;
//                            next_blocktype = rand() % 6;
//                            next_spinvalue = rand() % 4; // 랜덤 블록정보입력
//                            gameManager.block_type_to_coors(next_block_coors, next_blocktype, next_spinvalue); // 블록좌표 파악
//
//                            if (gameManager.can_put(gameManager.board[location[0]][location[1]], location[0], location[1])) { // 새 블록을 놓을 수 있다면
//                                gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블럭 놓기
//                                gameManager.put_block(graphic, next_block_coors, 7, 24);
//                                system("cls"); // 콘솔창을 지우고 다시 그림
//                                gameManager.show_graphic(); // 다시 찍고 보여줌
//                            }
//                            else { // 새 블록 생성할 자리가 없음
//                                gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블럭 놓기
//                                put_block(graphic, next_block_coors, 7, 24);
//                                system("cls"); // 콘솔창을 지우고 다시 그림
//                                gameManager.show_graphic();// 다시 찍고 보여줌
//                                printf("			게임오버");
//                                return 0;
//                            }
//                            break;
//                        }
//                    }
//                }
//                // 좌, 우, 하 키가 눌린 경우
//                else {
//                    gameManager.del_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블럭 지우기
//                    gameManager.move_coors(location, key); // 기준점을 움직임
//                    if (gameManager.can_put(gameManager.board[location[0]][location[1]], location[0], location[1])) { // 변경된 기준점에 놓을 수 있다면
//                        gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블록 놓기
//                        system("cls");
//                        gameManager.show_graphic(); // 블록 보여줌 
//                    }
//                    else { // 변경된 기준점에 놓을 수 없다면
//                        if (key == 2) { // 아래로 막힌 경우
//                            move_coors(location, 0); // 기준점 원상복귀
//                            gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블럭놓기
//                            gameManager.row_clear(graphic);
//                            location[0] = 4;
//                            location[1] = 14; // 기준점이 생성되는 점
//                            del_block(graphic, next_block_coors, 7, 24);
//                            // coor_to_coor(block_coors, next_block_coors);
//                            blocktype = next_blocktype;
//                            spinvalue = next_spinvalue;
//                            next_blocktype = rand() % 6;
//                            next_spinvalue = rand() % 4; // 랜덤 블록정보입력
//                            block_type_to_coors(next_block_coors, next_blocktype, next_spinvalue); // 블록좌표 파악
//
//                            if (can_put(graphic, next_block_coors, location)) { // 새 블록을 놓을 수 있다면
//                                gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블럭 놓기
//                                put_block(graphic, next_block_coors, 7, 24);
//                                system("cls"); // 콘솔창을 지우고 다시 그림
//                                gameManager.show_graphic(); // 다시 찍고 보여줌
//                            }
//                            else { // 새 블록 생성할 자리가 없음
//                                gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블럭 놓기
//                                put_block(graphic, next_block_coors, 7, 24);
//                                system("cls"); // 콘솔창을 지우고 다시 그림
//                                gameManager.show_graphic(); // 다시 찍고 보여줌
//                                printf("			게임오버");
//                                return 0;
//                            }
//                        }
//                        else { // 좌우가 막힌 경우
//                            move_coors(location, anti_arrow(key)); // 기준점 원상복귀
//                            gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]);
//                            system("cls"); // 콘솔창을 지우고 다시 그림
//                            gameManager.show_graphic(); // 다시 찍고 보여줌
//                        }
//                    }
//                }
//            }
//            else { // 회전키가 입력된 경우
//                gameManager.del_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블록 지우기
//                spinvalue = spin(spinvalue); // 블록회전상수를 키움
//                gameManager.block_type_to_coors(block_coors, blocktype, spinvalue); // 그거에 맞춰서 블록좌표들을 변환하고
//                if (gameManager.can_put(gameManager.board[location[0]][location[1]], location[0], location[1])) { // 놓을 수 있으면
//                    gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]);
//                    system("cls"); // 콘솔창을 지우고 다시 그림
//                    gameManager.show_graphic(); // 블록 보여주기
//                }
//                else { // 놓을 수 없다면
//                    spinvalue = anti_spin(spinvalue); // 블록회전상수를 1줄이고(원상복귀)
//                    gameManager.block_type_to_coors(block_coors, blocktype, spinvalue);
//                    gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블록 찍은 다음에
//                    system("cls"); // 콘솔창을 지우고 다시 그림
//                    gameManager.show_graphic(); // 블록 보여주기
//                }
//            
//            
//        }
//
//
//        // 단위시간마다 블록을 떨굼
//        if ((clock() - start) > 1499) {
//            start = clock();
//
//            gameManager.del_block(gameManager.board[location[0]][location[1]], location[0], location[1]); // 블록을 지우고
//
//            // 5초 이상이면 랜덤한 블록 생성
//            if ((clock() - start) > 5000) {
//                gameManager.generateRandomBlock();
//            }
//
//            gameManager.move_coors(location, 2); // 기준점을 움직임
//
//            // 충돌 확인
//            if (!gameManager.can_put(gameManager.board[location[0]][location[1]], location[0], location[1])) {
//                move_coors(location, 0); // 충돌 발생 시 원상복귀
//                gameManager.put_block(gameManager.board[location[0]][location[1]], location[0], location[1]);
//                gameManager.row_clear();
//                location[0] = 4;
//                location[1] = 14; // 기준점이 생성되는 점
//
//                // 5초 이상이면 랜덤한 블록 생성
//                if ((clock() - start) > 5000) {
//                    gameManager.generateRandomBlock();
//                }
//
//                gameManager.show_graphic(); // 다시 찍고 보여줌
//            }
//            else {
//                // 기존 코드 생략
//            }
//        }
//
//        // 기존 코드 생략
//    }
//
//    return 0;
//}