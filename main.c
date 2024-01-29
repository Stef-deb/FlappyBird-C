#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define ROWS 27
#define COLS 160
#define TOWERSIZE 8
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

char textureArray[ROWS][COLS];
int GAMEOVER = 0;

void printGameIntro(void) {
    gotoxy(0,0);
    printf("\
|-----------------------------------------------------------------------------------------------------------------------------------------------------|\n\
|                                                                                                                                                     |\n\
|                                                                                                                                                     |\n\
|                                  FFFFFFFFF  LL                  A            PPPPPPP      PPPPPPP     YY      YY                                    |\n\
|                                  FF         LL                AA AA          PP     P     PP     P     YY    YY                                     |\n\
|                                  FFFFFFFF   LL               AA   AA         PPPPPPP      PPPPPPP       YY  YY                                      |\n\
|                                  FF         LL              AAAAAAAAA        PP           PP              YY                                        |\n\
|                                  FF         LL             AA       AA       PP           PP              YY                                        |\n\
|                                  FF         LLLLLLLLL     AAA       AAA      PP           PP              YY                                        |\n\
|                                                                                                                                                     |\n\
|                                                                                                                                                     |\n\
|                                                     BBBBBB     II   RRRRRR       DDDD                                                               |\n\
|                                                     BB   BB    II   RR    RR     DD   DD                                                            |\n\
|                                                     BBBBBBB    II   RR    RR     DD     D                                                           |\n\
|                                                     BB    BB   II   RR RR        DD     D                                                           |\n\
|                                                     BB     B   II   RR   RR      DD    DD                                                           |\n\
|                                                     BBBBBBB    II   RR     RR    DDDDDD                                                             |\n\
|                                                                                                                                                     |\n\
|                                                              V 1.0 By TheStef                                                                       |\n\
|                                                                                                                                                     |\n\
|                                             COMMANDS:                                                                                               |\n\
|                                                      JUMP: ARROW-UP                                                                                 |\n\
|                                                      EXIT: CTRL+C                                                                                   |\n\
|                                                      START/NEW-GAME (when game is over): ENTER                                                      |\n\
|                                                                                                                                                     |\n\
|                                                                                                                                                     |\n\
|                                                                                                                                                     |\n\
|-----------------------------------------------------------------------------------------------------------------------------------------------------|\n\
                                                                                                                                                       \n\
                                                                                                                                                       \n\
                                                                                                                                                       \n");
}

void printGameOver(void) {
    gotoxy(0, 8);
    printf("\
|                                               GGGG              A         MM          MM   EEEEEEEEEEE\n\
|                                           GGG      GG         AA AA       MMMM      MMMM   EE\n\
|                                           GG                 AA   AA      MM  MM  MM  MM   EEEEEEEEEEE\n\
|                                           GG   GGGGGGG      AAAAAAAAA     MM    MM    MM   EE\n\
|                                            GGG   GG        AA       AA    MM          MM   EE\n\
|                                               GGGGG       AAA       AAA   MM          MM   EEEEEEEEEEE\n\
|\n\
|                                               OOOO       VV           VV   EEEEEEEEEEE     RRRRRR\n\
|                                            OO      OO     VV         VV    EE              RR    RR\n\
|                                           O          O     VV       VV     EEEEEEEEEEE     RR    RR\n\
|                                           O          O      VV     VV      EE              RR RR\n\
|                                            OO      OO         VV VV        EE              RR   RR\n\
|                                               OOOO              V          EEEEEEEEEEE     RR     RR");
}

void initArray(char a[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int x = 0; x < COLS; x++){
            if (x == COLS-1) {
                a[row][x] = '\n';
            } else if (x >= COLS - TOWERSIZE -1) {
                a[row][x] = ' ';
            } else if (x == 0 || x == (COLS - TOWERSIZE -2)) {
                a[row][x] = '|';
            } else if (row == 0 || row == (ROWS-1)) {
                a[row][x] = '-';
            }  else if (row == ROWS/3|| row == ROWS/3+1){
                if (x == 8 || x == 9 || x == 10) {
                    a[row][x] = 'G';
                } else {
                    a[row][x] = ' ';
                }
            } else { 
                a[row][x] = ' ';
            }
        }
    }
}

void insertTower(char a[ROWS][COLS], int height) {
    if (height == 0) return;
    if (height > 0) {
        for (int row = ROWS-height; row < ROWS-1; row++) {
            for (int x = 151; x < COLS-1; x ++) {
                a[row][x] = '0';
            }
        }
    } else {
        for (int row = 1; row < -height; row++) {
            for (int x = 151; x < COLS-1; x ++) {
                a[row][x] = '0';
            }
        }
    }
}

void shiftArrayTick (char a[ROWS][COLS], int jump_size) {
    for (int row = 1; row < ROWS-1; row++) {
        for (int x = 0; x < COLS; x++) {
            if (a[row][x] == '0'){
                if (a[row][x-jump_size] == 'G') GAMEOVER = 1;
                if (x <= jump_size) {
                    a[row][x] = ' ';
                } else {
                    int check = 0;
                    for (int m = 0; m < jump_size; m++) {
                        if (a[row][x-jump_size+m] == '|') {
                            check = 1;
                        }
                    }
                    if (check) {
                        a[row][x-jump_size-1] = '0';
                        a[row][x] = ' ';
                    } else {
                        a[row][x-jump_size] = '0';
                        a[row][x] = ' ';
                    }
                }
            }
        }
    }
}

void printMat(char a[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j >= COLS-9) {
                if (j == COLS-1){ 
                    printf("\n");
                    continue;
                }
                printf(" ");
            } else {
                printf("%c", a[i][j]);
            }
        }
    }
    printf("                                                                                                                                                        \n\
                                                                                                                                                        \n\
                                                                                                                                                        \n");
}

void shiftPlayer(char a[ROWS][COLS], int y){
    if (y < 0) {
        for (int row = 1; row < ROWS; row++) {
            for (int x = 8; x < 11; x++) {
                if (a[row][x] == 'G') {
                    if (row <= 1) {
                        GAMEOVER = 1;
                        return;
                    }
                    
                    a[row+y][x] = 'G';
                    a[row][x] = ' ';
                }
            }
        }
    } else {
        for (int row = ROWS -1 ; row > 0; row--) {
            for (int x = 8; x < 11; x++) {
                if (a[row][x] == 'G') {
                    if (row + y >= ROWS) {
                        GAMEOVER = 1;
                        return;
                    }
                    a[row+y][x] = 'G';
                    a[row][x] = ' ';
                }
            }
        }
    }
}

void hideCursor(void){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void startGame(void) {
    int count = 0;
    int top = 0;
    Sleep(500);
    printGameIntro();
    while(1) {
        if(GetAsyncKeyState(VK_RETURN) & 0x8000) {
            gotoxy(0, 0);
            initArray(textureArray);
            break;
        }                
    }
    while (1) {
        for (int a = 0; a < 1; a++) {
            if (GAMEOVER) {
                printGameOver();
                while (1){
                    if(GetAsyncKeyState(VK_RETURN) & 0x8000) {
                        gotoxy(0, 0);
                        count = 0;
                        top = 0;
                        GAMEOVER = 0;
                        initArray(textureArray);
                        break;
                    }                
                }
            }
            shiftArrayTick(textureArray, 2);
            if (GetAsyncKeyState(VK_UP) & 0x8000) {
                shiftPlayer(textureArray, -1);
            } else {
                shiftPlayer(textureArray, 1);
            }
            if (count >= TOWERSIZE) {
                int r = rand()%3;
                if (r == 2) {
                    int height = 10 + rand()%5;
                    if (top) {
                        insertTower(textureArray, -height);
                        top = 0;
                    } else {
                        insertTower(textureArray, height);
                        top = 1;
                    }
                    count = 0;
                } 
            }
        }
        printMat(textureArray);
        gotoxy(0, 0); 
        count++;
   
    }

}

int main(void){
    initArray(textureArray);
    hideCursor();
    startGame();
    return 0;
}
