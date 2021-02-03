#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define ESC 27

//Constant
const int MODE_3X3 = 1;
const int MODE_5X5 = 2;
const int MODE_7X7 = 3;
const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;
const int X = -1;
const int O = 0;
const int WIN = 1;
const int DRAW = -1;
const int CONTINUE = 0;
const int BOT_WIN = 10;
const int PLAYER_WIN = -10;
const int TIE = 0;
const int MEDIUM_DEPTH = 2;
const int HARD_DEPTH = 4;
const int ALPHA = -1000;
const int BETA = 1000;
const char* ACCOUNT_FILE = "data_files/account.dat";
const char* SCORE_FILE = "data_files/score.dat";

bool isTimeout = false;
int maxTime = 10000;
int startTime;

void login();
int main();
void mainMenu();
void chooseMode(int *mode);
void chooseDifficulty(int *difficulty);
void inputAmountOfSession(int *session);
void play(int difficulty, int session, int mode);

char activeUname[20] = {};

typedef struct{
    int x;
    int y;
} Position;

typedef struct {
    char uname[21];
    char password[21];
} Account;

typedef struct {
    char uname[21];
    int winEasy;
    int winMed;
    int winHard;
    int totalPoin;
} Score;


void makeOutputWhite(){
    HANDLE hconsole;
    hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, 15);
}

void makeOutputRed(){
    HANDLE hconsole;
    hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, 12);
}

void makeOutputBlue(){
    HANDLE hconsole;
    hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, 9);
}

void showProgramTitle(){
    printf("====================================\n");
    printf("             TIC TAC TOE\n");
    printf("====================================\n\n");

    if(strlen(activeUname) != 0){
        printf("User aktif : %s\n\n", activeUname);
    }
}

void daftar(){
    FILE *fAccount;
    fAccount = fopen(ACCOUNT_FILE, "rb");
    Account acc,buffer;
    bool is_open_in_wb = false, is_uname_taken = false;

    memset(acc.uname, 0, sizeof(acc.uname));
    memset(acc.password, 0, sizeof(acc.password));

    showProgramTitle();
    printf("============== Daftar ==============\n\n");

    if(fAccount == NULL){
        fAccount = fopen(ACCOUNT_FILE, "a+");
        is_open_in_wb = true;

        if(fAccount == NULL){
            printf("Error creating file");
            Sleep(2000);
            system("cls");
            main();
        }
    }

    if(fAccount != NULL){
        do{
            is_uname_taken = false;
            do{
                printf("Masukan username (Maks 20 karakter) : ");
                scanf(" %[^\n]%*c", acc.uname);

                if(strlen(acc.uname) > 20){
                    printf("Jumlah karakter melebihi batas");
                    Sleep(1500);
                    memset(acc.uname, 0, sizeof(acc.uname));
                    system("cls");
                    showProgramTitle();
                    printf("============== Daftar ==============\n\n");
                }

            } while(strlen(acc.uname) == 0);

            if(!is_open_in_wb){
                while(!feof(fAccount)){
                    fread(&buffer, sizeof(buffer), 1, fAccount);
                    if(strcmp(buffer.uname, acc.uname) == 0){
                        is_uname_taken = true;
                        break;
                    }
                }

                if(is_uname_taken){
                    printf("Username telah terpakai\n");
                    Sleep(1500);
                    system("cls");
                    rewind(fAccount);
                    showProgramTitle();
                    printf("============== Daftar ==============\n\n");
                }
            }
        }while(is_uname_taken);

        fclose(fAccount);
        fAccount = fopen(ACCOUNT_FILE, "a+");

        printf("Masukan password : ");
        scanf(" %[^\n]%*c", acc.password);

        if(fwrite(&acc, sizeof(acc), 1, fAccount)){
            system("cls");
            fclose(fAccount);
            login();
        } else {
            printf("Gagal mendaftarkan username");
            Sleep(2000);
            system("cls");
            fclose(fAccount);
            main();
        }
    }
}

void login(){
    FILE *fAccount;
    fAccount = fopen(ACCOUNT_FILE, "r");
    Account buffer;
    char uname[20] = {};
    char pass[20] = {};

    showProgramTitle();
    printf("=============== Login ==============\n\n");

    if(fAccount == NULL){
        printf("Belum ada Akun terdaftar");
        Sleep(2000);
        system("cls");
        fclose(fAccount);
        daftar();
    } else {
        do{
            do {
                printf("Masukan username : ");
                scanf(" %[^\n]%*c", uname);

                while(!feof(fAccount)){
                    fread(&buffer, sizeof(buffer), 1, fAccount);
                    if(strcmp(buffer.uname, uname) == 0)
                        break;
                }

                if(feof(fAccount)){
                    rewind(fAccount);
                    printf("Username tidak terdaftar");
                    Sleep(2000);
                } else {
                    break;
                }
                system("cls");
                showProgramTitle();
                printf("=============== Login ==============\n\n");
            }while(!feof(fAccount));

            printf("Masukan password : ");
            scanf(" %[^\n]%*c", pass);

            if(strcmp(buffer.password, pass) == 0){
                break;
            } else{
                printf("Password Salah");
                Sleep(2000);
                system("cls");
                showProgramTitle();
                rewind(fAccount);
                printf("=============== Login ==============\n\n");
            }
        }while(strcmp(buffer.password, pass) != 0);
    }

    strcpy(activeUname, buffer.uname);

    system("cls");
    fclose(fAccount);
}

void highScore(){
    FILE *f;
    Score highScore;
    f = fopen(SCORE_FILE, "rb");
    int i = 1;
    makeOutputWhite();
    printf("Tekan ESC untuk kembali ke menu utama\n\n");
    printf("======================= Highscore =========================\n");
    printf("===========================================================\n");
    printf(" No   Username\t\tEasy\tMedium\tHard\tTotal Poin\n");
    printf("===========================================================\n");
    if(f!= NULL){
        memset(highScore.uname, 0, sizeof(highScore.uname));
        fread(&highScore, sizeof(highScore), 1, f);
        while(!feof(f)){
            if(strcmp(highScore.uname, activeUname) == 0)
                makeOutputBlue();
            printf(" %d    %s\t\t%d\t%d\t%d\t%d\n", i, highScore.uname, highScore.winEasy, highScore.winMed, highScore.winHard, highScore.totalPoin);
            makeOutputWhite();
            memset(highScore.uname, 0, sizeof(highScore.uname));
            fread(&highScore, sizeof(highScore), 1, f);
            i++;
        }
    } else {
        printf("Belum ada highscore");
    }

    fclose(f);

    char ch;
    do {
        ch = getch();
        if(ch == ESC){
            system("cls");
            mainMenu();
        }
    } while(ch != ESC);
}

int countTotalPoin(int winEasy, int winMed, int winHard){
    return (winEasy * 3) + (winMed * 5) + (winHard * 7);
}

void sortScore(){
    FILE *f = fopen(SCORE_FILE, "r+b");
    Score buffer1;
    Score buffer2;
    int filePos = 0;
    int i = 1;

    memset(buffer1.uname, 0, sizeof(buffer1.uname));
    memset(buffer2.uname, 0, sizeof(buffer2.uname));

    fseek(f, filePos*sizeof(buffer1), SEEK_SET);
    fread(&buffer1, sizeof(buffer1), 1, f);
    while(!feof(f)){
        fseek(f, (filePos + i)*sizeof(buffer2), SEEK_SET);
        fread(&buffer2, sizeof(buffer2), 1, f);
        if(!feof(f)){
            if(buffer1.totalPoin < buffer2.totalPoin){
                fseek(f, filePos*sizeof(buffer1), SEEK_SET);
                fwrite(&buffer2, sizeof(buffer2), 1, f);
                fseek(f, (filePos + i)*sizeof(buffer1), SEEK_SET);
                fwrite(&buffer1, sizeof(buffer1), 1, f);
            }
        } else {
           filePos++;
           i = 0;
        }
        memset(buffer1.uname, 0, sizeof(buffer1.uname));
        memset(buffer2.uname, 0, sizeof(buffer2.uname));

        fseek(f, filePos*sizeof(buffer1), SEEK_SET);
        fread(&buffer1, sizeof(buffer1), 1, f);
        i++;
    }

    fclose(f);

}

void writeScore(int difficulty){
    FILE *f;
    f = fopen(SCORE_FILE, "r+b");
    Score buffer;
    int filePos = 0;

    if(f == NULL){
        fclose(f);
        f = fopen(SCORE_FILE, "wb+");
    }

    memset(buffer.uname, 0, sizeof(buffer.uname));
    while(!feof(f)){
        if(fread(&buffer, sizeof(buffer), 1, f)){
            if(strcmp(buffer.uname, activeUname) == 0){
                switch(difficulty){
                    case 1 :
                        buffer.winEasy++;
                        break;
                    case 2 :
                        buffer.winMed++;
                        break;
                    case 3 :
                        buffer.winHard++;
                        break;
                }
                buffer.totalPoin = countTotalPoin(buffer.winEasy, buffer.winMed, buffer.winHard);
                fseek(f, (filePos  * sizeof(buffer)), SEEK_SET);
                fwrite(&buffer, 1, sizeof(buffer), f);
                break;
            } else {
                filePos++;
                memset(buffer.uname, 0, sizeof(buffer.uname));
            }
        }
    }

    if(feof(f)){
        Sleep(1000);
        f = fopen(SCORE_FILE, "a+b");

        int easy = 0, medium = 0, hard = 0;
        switch(difficulty){
            case 1 :
                easy++;
                break;
            case 2 :
                medium++;
                break;
            case 3 :
                hard++;
                break;
        }

        Score newScore;
        memset(newScore.uname, 0, sizeof(newScore.uname));
        strcpy(newScore.uname, activeUname);
        newScore.winEasy = easy;
        newScore.winMed = medium;
        newScore.winHard = hard;
        newScore.totalPoin = countTotalPoin(newScore.winEasy, newScore.winMed, newScore.winHard);
        fwrite(&newScore, sizeof(newScore), 1, f);
    }

    fclose(f);

    sortScore();
}

void mainMenu(){
    int choice;
    int mode;
    int difficullty;
    int session;

    showProgramTitle();
    printf("(1) Play  (2) HighScore  (3) Logout\n\n");
    printf("Pilih : ");
    scanf("%d", &choice);

    if(choice != 1 && choice != 2 && choice != 3){
        printf("Pilih Mode dengan menginput angka 1, 2, atau 3 !") ;
        Sleep(2000) ;
        system("cls") ;
        mainMenu() ;
    }
    switch(choice){
        case 1 :
            system("cls");
            chooseMode(&mode);
            chooseDifficulty(&difficullty);
            inputAmountOfSession(&session);

            play(difficullty, session, mode);
        break;

        case 2 :
            system("cls");
            highScore();
            break;

        case 3 :
            memset(activeUname, 0, sizeof(activeUname));
            system("cls");
            main();
        break;
    }
}

void chooseMode(int *mode){
    do{
        showProgramTitle();
        printf("(1) 3X3       (2) 5X5       (3) 7X7\n\n");
        printf("Pilih Mode : " );
        scanf("%d", mode);
        if(*mode == 0){
            system("cls");
            mainMenu();
        }
        else if(*mode != MODE_3X3 && *mode != MODE_5X5 && *mode != MODE_7X7){
            printf("Pilih Mode dengan menginput angka 1, 2, atau 3 !");
            Sleep(1500);
        }
        system("cls");
    } while(*mode != MODE_3X3 && *mode != MODE_5X5 && *mode != MODE_7X7);
}

void chooseDifficulty(int *difficulty){
    do{
        showProgramTitle();
        printf("(1) Easy     (2) Medium    (3) Hard\n\n");
        printf("Pilih Difficulty : " );
        scanf("%d", difficulty);
        if(*difficulty == 0){
            system("cls");
            mainMenu();
        }
        else if (*difficulty!= EASY && *difficulty != MEDIUM && *difficulty != HARD){
            printf("Pilih difficulty dengan menginput angka 1, 2, atau 3 !");
            Sleep(1500);
        }

        system("cls");
    } while(*difficulty!= EASY && *difficulty != MEDIUM && *difficulty != HARD);
}

void inputAmountOfSession(int *session){
    do{
        showProgramTitle();
        printf("Ingin berapa kali main (maks 9) : " );
        scanf("%d", session);
        if (*session < 1 || *session > 9){
            printf("Jumlah sesi melebihi batas");
            Sleep(1500);
        }

        system("cls");
    } while(*session < 1 || *session > 9);
}

void initBoardValue(int *arr, int maxBox){
    int boardIndex = 1;
    for(int i = 0; i < maxBox; i++){
        for(int j = 0; j < maxBox ; j++){
            *((arr + i*maxBox) + j) = boardIndex;
            boardIndex++;
        }
    }
}

void determineOutputColor(char *charRep){

    if(strcmp(charRep,"O") == 0 || strcmp(charRep," O") == 0){
        makeOutputRed();
    } else if(strcmp(charRep,"X") == 0 || strcmp(charRep," X") == 0){
        makeOutputBlue();
    }

    if(strlen(charRep) > 1)
        printf(" %s  ", charRep);
    else
        printf("  %s  ", charRep);

    makeOutputWhite();
}

void showBoard(int mode, int *boardValue){
    char charRepValue [mode == 1 ? 3*3 : mode == 2 ? 5*5 : 7*7][3];
    int counter = 0;
    int start;
    int index;

    switch(mode){
        // Mode 3X3
        case 1:
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    if(*((boardValue + i*3) + j) == O){
                        strcpy(charRepValue[counter], "O");
                    }

                    else if(*((boardValue + i*3) + j) == X){
                        strcpy(charRepValue[counter], "X");
                    }
                    else {
                        itoa(*((boardValue + i*3) + j), charRepValue[counter], 10);
                    }
                    counter++;
                }
            }

            printf(" _____ _____ _____\n");
            printf("|     |     |     |\n");

            index = 0;
            for(start = 0 ; start < 3; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 2){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|\n");
            printf("|     |     |     |\n");

            index = 3;
            for(start = 0 ; start < 3; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 2){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|\n");
            printf("|     |     |     |\n");

            index = 6;
            for(start = 0 ; start < 3; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 2){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|\n");
        break;

        // Mode 5X5
        case 2 :
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(*((boardValue + i*5) + j) == 0){
                        if (counter > 8)
                            strcpy(charRepValue[counter], " O");
                        else
                            strcpy(charRepValue[counter], "O");
                    }

                    else if(*((boardValue + i*5) + j) == -1){
                        if (counter > 8)
                            strcpy(charRepValue[counter], " X");
                        else
                            strcpy(charRepValue[counter], "X");
                    }
                    else {
                        itoa(*((boardValue + i*5) + j), charRepValue[counter], 10);
                    }
                    counter++;
                }
            }

            printf(" _____ _____ _____ _____ _____\n");
            printf("|     |     |     |     |     |\n");

            index = 0;
            for(start = 0 ; start < 5; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 4){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            index = 5;
            for(start = 0 ; start < 5; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 4){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            index = 10;
            for(start = 0 ; start < 5; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 4){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            index = 15;
            for(start = 0 ; start < 5; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 4){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            index = 20;
            for(start = 0 ; start < 5; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 4){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|\n");
        break;

        //MODE 7X7
        case 3 :

            for(int i = 0; i < 7; i++){
                for(int j = 0; j < 7; j++){
                    if(*((boardValue + i*7) + j) == 0){
                        if (counter > 8)
                            strcpy(charRepValue[counter], " O");
                        else
                            strcpy(charRepValue[counter], "O");
                    }

                    else if(*((boardValue + i*7) + j) == -1){
                        if (counter > 8)
                            strcpy(charRepValue[counter], " X");
                        else
                            strcpy(charRepValue[counter], "X");
                    }
                    else {
                        itoa(*((boardValue + i*7) + j), charRepValue[counter], 10);
                    }
                    counter++;
                }
            }

            printf(" _____ _____ _____ _____ _____ _____ _____\n");
            printf("|     |     |     |     |     |     |     |\n");

            index = 0;
            for(start = 0 ; start < 7; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 6){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            index = 7;
            for(start = 0 ; start < 7; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 6){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            index = 14;
            for(start = 0 ; start < 7; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 6){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            index = 21;
            for(start = 0 ; start < 7; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 6){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            index = 28;
            for(start = 0 ; start < 7; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 6){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            index = 35;
            for(start = 0 ; start < 7; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 6){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            index = 42;
            for(start = 0 ; start < 7; start++){
                printf("|");
                determineOutputColor(charRepValue[index]);
                if(start == 6){
                    printf("|");
                }
                index++;
            }
            printf("\n");

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
        break;
    }
}

void putInputToBoard(int inputPos, int *boardValue, int mode, int *player){
    Position pos;
    switch(mode){
        //Mode 3X3
        case 1:
            pos.x = (inputPos-1) / 3;
            pos.y = (inputPos-1) % 3;

            if( *((boardValue + pos.x*3) + pos.y) != O && *((boardValue + pos.x*3) + pos.y) != X){
                if (*player == O)
                    *((boardValue + pos.x*3) + pos.y) = O;
                else
                    *((boardValue + pos.x*3) + pos.y) = X;
            }

            else{
                printf("\nPosisi sudah terisi\n");
                Sleep(1000);
                (*player)--;
            }

        break;

        //Mode 5X5
        case 2:
            pos.x = (inputPos - 1) / 5;
            pos.y = (inputPos-1) % 5;

            if( *((boardValue + pos.x*5) + pos.y) != 0 && *((boardValue + pos.x*5) + pos.y) != -1)
                if (*player == O)
                    *((boardValue + pos.x*5) + pos.y) = O;
                else
                    *((boardValue + pos.x*5) + pos.y) = X;
            else{
                printf("\nPosisi sudah terisi\n");
                Sleep(1000);
                (*player)--;
            }

        break;

        //Mode 7X7
        case 3:
            pos.x = (inputPos - 1) / 7;
            pos.y = (inputPos-1) % 7;

            if( *((boardValue + pos.x*7) + pos.y) != 0 && *((boardValue + pos.x*7) + pos.y) != -1)
                if (*player == O)
                    *((boardValue + pos.x*7) + pos.y) = O;
                else
                    *((boardValue + pos.x*7) + pos.y) = X;
            else{
                printf("\nPosisi sudah terisi\n");
                Sleep(1000);
                (*player)--;
            }

        break;
    }
}

int checkWin3x3(int Board[3][3]){
    if ((Board[0][0]==Board[0][1]) && (Board[0][1]==Board[0][2]))
        return WIN ;
    else if ((Board[1][0]==Board[1][1]) && (Board[1][1]==Board[1][2]))
        return WIN ;
    else if ((Board[2][0]==Board[2][1]) && (Board[2][1]==Board[2][2]))
        return WIN ;
    else if ((Board[0][0]==Board[1][0]) && (Board[1][0]==Board[2][0]))
        return WIN ;
    else if ((Board[0][1]==Board[1][1]) && (Board[1][1]==Board[2][1]))
        return WIN ;
    else if ((Board[0][2]==Board[1][2]) && (Board[1][2]==Board[2][2]))
        return WIN ;
    else if ((Board[0][0]==Board[1][1]) && (Board[1][1]==Board[2][2]))
        return WIN ;
    else if ((Board[0][2]==Board[1][1]) && (Board[1][1]==Board[2][0]))
        return WIN ;

    else if (Board[0][0] != 1 && Board[0][1] != 2 && Board[0][2] != 3 &&  //check if all value in the board isn't the initial value
            Board[1][0] != 4 && Board[1][1] != 5 && Board[1][2] != 6 &&  //and nobody win then draw
            Board[2][0] != 7 && Board[2][1] != 8 && Board[2][2] != 9)
            return DRAW ;

    else
        return CONTINUE;
}

int checkWin5x5(int board[5][5]){
    int sameCount = 1;
    int countBlank = 0;
    int checkedChar;
    int iteration;
    int i, j, k, l;

    //Check for blank block
    for(i = 0 ; i < 5 ; i++){
        for (j = 0 ; j < 5 ; j++){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];

            if(checkedChar != X && checkedChar != O)
                countBlank++;
        }
    }

    //Check Horizontally
    for(i = 0; i < 5 ; i++){
        sameCount = 1;
        for(j = 0 ; j < 4 ; j++){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];

            if(checkedChar == board[i][j + 1])
                sameCount++;

            else
                sameCount = 1;

            if(sameCount == 4)
                return WIN;
        }
    }
    sameCount = 1;

    //Check Vertically
    for(i = 0; i < 5 ; i++){
        sameCount = 1;
        for(j = 0 ; j < 4 ; j++){
            checkedChar = board[j][i] == X ? X : board[j][i] == O ? O : board[j][i];
            if(checkedChar == board[j + 1][i])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 4)
                return WIN;
        }
    }
    sameCount = 1;

    //Check Diagonally from Left
    iteration = 0;
    while(iteration < 2){
        i = iteration;
        j = 0;
        k = 0;
        l = iteration;

        sameCount = 1;
        while(i < 4 && j < 4){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];
            if(checkedChar == board[i + 1][j + 1])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 4){
                return WIN;
            }

            i++;
            j++;
        }

        sameCount = 1;
        while(k < 4 && l < 4){
            checkedChar = board[k][l] == X ? X : board[k][l] == O ? O : board[k][l];
            if(checkedChar == board[k + 1][l + 1])
                sameCount++;

            else
                sameCount = 1;

            if(sameCount == 4)
                return WIN;

            k++;
            l++;
        }
        iteration++;
    }
    sameCount = 1;

    //Check Diagonally from Right
    iteration++;
    while(iteration < 5){
        i = 0;
        j = iteration;
        k = iteration - 2;
        l = 4;


        sameCount = 1;
        while(i < 4 && j >= 0){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];
            if(checkedChar == board[i + 1][j - 1])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 4)
                return WIN;

            i++;
            j--;
        }

        sameCount = 1;
        while(k < 4){
            checkedChar = board[k][l] == X ? X : board[k][l] == O ? O : board[k][l];
            if(checkedChar == board[k + 1][l - 1])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 4)
                return WIN;

            k++;
            l--;
        }
        iteration++;
    }

    if (countBlank == 0)
        return DRAW;

    return CONTINUE;
}

int checkWin7x7(int board[7][7]){
    int sameCount = 1;
    int countBlank = 0;
    int checkedChar;
    int iteration;
    int i, j, k, l;

    //Check for blank block
    for(i = 0 ; i < 7 ; i++){
        for (j = 0 ; j < 7 ; j++){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];

            if(checkedChar != X && checkedChar != O)
                countBlank++;
        }
    }

    //Check Horizontally
    for(i = 0; i < 7 ; i++){
        sameCount = 1;
        for(j = 0 ; j < 6 ; j++){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];

            if(checkedChar == board[i][j + 1])
                sameCount++;

            else
                sameCount = 1;

            if(sameCount == 5)
                return WIN;
        }
    }
    sameCount = 1;

    //Check Vertically
    for(i = 0; i < 7 ; i++){
        sameCount = 1;
        for(j = 0 ; j < 6 ; j++){
            checkedChar = board[j][i] == X ? X : board[j][i] == O ? O : board[j][i];
            if(checkedChar == board[j + 1][i])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 5)
                return WIN;
        }
    }
    sameCount = 1;

    //Check Diagonally from Left
    iteration = 0;
    while(iteration < 4){
        i = iteration;
        j = 0;
        k = 0;
        l = iteration;

        sameCount = 1;
        while(i < 6 && j < 6){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];
            if(checkedChar == board[i + 1][j + 1])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 5){
                return WIN;
            }

            i++;
            j++;
        }

        sameCount = 1;
        while(k < 6 && l < 6){
            checkedChar = board[k][l] == X ? X : board[k][l] == O ? O : board[k][l];
            if(checkedChar == board[k + 1][l + 1])
                sameCount++;

            else
                sameCount = 1;

            if(sameCount == 5)
                return WIN;

            k++;
            l++;
        }
        iteration++;
    }
    sameCount = 1;

    //Check Diagonally from Right
    iteration--;
    while(iteration < 7){
        i = 0;
        j = iteration;
        k = iteration - 2;
        l = 6;


        sameCount = 1;
        while(i < 6 && j >= 0){
            checkedChar = board[i][j] == X ? X : board[i][j] == O ? O : board[i][j];
            if(checkedChar == board[i + 1][j - 1])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 5)
                return WIN;

            i++;
            j--;
        }

        sameCount = 1;
        while(k < 6){
            checkedChar = board[k][l] == X ? X : board[k][l] == O ? O : board[k][l];
            if(checkedChar == board[k + 1][l - 1])
                sameCount++;
            else
                sameCount = 1;

            if(sameCount == 5)
                return WIN;

            k++;
            l--;
        }
        iteration++;
    }

    if (countBlank == 0)
        return DRAW;

    return CONTINUE;
}

void checkAvailableSpot(int *boardValue, Position *pos, int maxBox, int *count){
    for(int i = 0; i < maxBox ; i++){
        for(int j = 0 ; j < maxBox ; j++){
            if (*((boardValue + i*maxBox) + j) != X && *((boardValue + i*maxBox) + j) != O ) {
                pos[*count].x = i;
                pos[*count].y = j;
                (*count)++;
            }
        }
    }
}

void theWinner(int player, char winner[10]){
    if (player == X)
        strcpy(winner, "Player") ;
    else if (player == O)
        strcpy(winner, "Bot") ;
}

void showWinner(int player, int check, char winner[10]){
    theWinner(player, winner) ;
    if (check == WIN){
        printf("\n\n==> \a%s Win\n", winner) ;
    }
    else {
        printf("\n\n==> \aGame Draw\n") ;
    }
}

void showGameWinner(int playerCount, int botCount){
    printf("\n\n ==> %s \n", playerCount > botCount ? "Player Win The Game" : playerCount == botCount ? "Game Draw" : "Bot Win The Game");
}

void setWinOrDrawCount(int player, int check, int *botCount, int *playerCount, int *drawCount){
    if(check == DRAW){
       (*drawCount)++;
    } else if(check == WIN) {
        if(player == X)
            (*playerCount)++;
        else
           (*botCount)++;
    }
}

void showScoreBoard(int playerCount, int botCount, int drawCount, int session){
    printf("             SCOREBOARD\n");
    printf("  ________    _________     ________\n");
    printf(" |        |  |         |   |        |\n");
    printf(" | Player |  |   Bot   |   |  Draw  |\n");
    printf(" |   %d    |  |    %d    |   |   %d    |\n", playerCount, botCount, drawCount);
    printf(" |________|  |_________|   |________|\n");
    printf("\n");
    printf("            Game Tersisa\n");
    printf("                 %d\n", session);
}

int minimax(int *boardValue, int depth, int alpha, int beta, bool isBot, int mode){
    int result = mode == MODE_3X3 ? checkWin3x3(boardValue) : mode == MODE_5X5 ? checkWin5x5(boardValue) : checkWin7x7(boardValue);
    int maxBox = mode == MODE_3X3 ? 3 : mode == MODE_5X5 ? 5 : 7;

    if(result != CONTINUE || depth < 1){
        if(result == WIN)
            return isBot ? PLAYER_WIN : BOT_WIN;

        else if(result == DRAW || depth < 1)
            return TIE;

    }

    if(isBot){
        int bestScore = -1000;
        for(int i = 0; i < maxBox ; i++ ){
            for(int j = 0; j < maxBox; j++){
                if (*((boardValue + i*maxBox) + j) != X && *((boardValue + i*maxBox) + j) != O ){
                    int lastValue = *((boardValue + i*maxBox) + j);
                    *((boardValue + i*maxBox) + j) = O;
                    int score = minimax(boardValue, depth -1, alpha, beta, false, mode);
                    *((boardValue + i*maxBox) + j) = lastValue;
                    bestScore = bestScore < score ? score : bestScore;
                    alpha = alpha > score ? alpha : score;
                    if(beta <= alpha){
                        return alpha;
                    }
                }
            }
        }

        return bestScore;
    }
    else {
        int bestScore = 1000;
        for(int i = 0; i < maxBox ; i++ ){
            for(int j = 0; j < maxBox; j++){
                if (*((boardValue + i*maxBox) + j) != X && *((boardValue + i*maxBox) + j) != O ){
                    int lastValue = *((boardValue + i*maxBox) + j);
                    *((boardValue + i*maxBox) + j) = X;
                    int score = minimax(boardValue, depth -1, alpha, beta, true, mode);
                    *((boardValue + i*maxBox) + j) = lastValue;
                    bestScore = bestScore > score ? score : bestScore;
                    beta = beta < score ? beta : score;
                    if(beta <= alpha){
                        return beta;
                    }
                }
            }
        }

        return bestScore;
    }
}
void botEasy(int *boardValue, int mode){
    int maxBox = mode == MODE_3X3 ? 3 : mode == MODE_5X5 ? 5 : 7;
    Position availiablePos[maxBox*maxBox];
    int ukuran = 0;
    checkAvailableSpot(boardValue, availiablePos, maxBox, &ukuran);

    srand(time(0));
    int index = rand() % ukuran;

    *((boardValue + availiablePos[index].x*maxBox) + availiablePos[index].y) = O;
}

void botMedium(int *boardValue, int mode){
    int bestScore = -1000;
    int maxBox = mode == MODE_3X3 ? 3 : mode == MODE_5X5 ? 5 : 7;
    Position move;

    for(int i = 0; i < maxBox ; i++){
        for(int j = 0; j < maxBox; j++){
            if (*((boardValue + i*maxBox) + j) != X && *((boardValue + i*maxBox) + j) != O ){
                int lastValue = *((boardValue + i*maxBox) + j);
                *((boardValue + i*maxBox) + j) = O;
                int score = minimax(boardValue, MEDIUM_DEPTH, ALPHA, BETA, false, mode);
                *((boardValue + i*maxBox) + j) = lastValue;

                if(bestScore < score){
                    bestScore = score;
                    move.x = i;
                    move.y = j;
                }
            }
        }
    }

    *((boardValue + move.x*maxBox) + move.y) = O;
}

void botHard(int *boardValue, int mode){
    int bestScore = -1000;
    int maxBox = mode == MODE_3X3 ? 3 : mode == MODE_5X5 ? 5 : 7;
    Position move;

    for(int i = 0; i < maxBox ; i++){
        for(int j = 0; j < maxBox; j++){
            if (*((boardValue + i*maxBox) + j) != X && *((boardValue + i*maxBox) + j) != O ){
                int lastValue = *((boardValue + i*maxBox) + j);
                *((boardValue + i*maxBox) + j) = O;
                int score = minimax(boardValue, HARD_DEPTH, ALPHA, BETA, false, mode);
                *((boardValue + i*maxBox) + j) = lastValue;

                if(bestScore < score){
                    bestScore = score;
                    move.x = i;
                    move.y = j;
                }
            }
        }
    }

    *((boardValue + move.x*maxBox) + move.y) = O;
}

void *threadTimer(){
    isTimeout = false;

    while(startTime <= maxTime){
        Sleep(1000);
        startTime++;
    }
    isTimeout = true;
    startTime = 0;
    return NULL;
}

void play(int difficulty, int session, int mode){
    int boardTiles = mode == MODE_3X3 ? 3 : mode == MODE_5X5 ? 5 : 7;
    int boardValue [boardTiles][boardTiles];
    int inputPos;
    int check = CONTINUE ;
    int player = X;
    char winner[10] = {};
    int botWinCount = 0;
    int playerWinCount = 0;
    int drawCount = 0;
    int initialSession = session;
    int choice;
    int iteration = 1 ;

    //maxTime = 0 + (mode == MODE_3X3 ? 10 : mode == MODE_5X5 ? 12 : 15) + (difficulty == EASY ? 5 : mode == MEDIUM ? 3 : 0);

    do {

        initBoardValue(*boardValue, boardTiles);

        do {
            player = (player % 2);

            showScoreBoard(playerWinCount, botWinCount, drawCount, session);
            showBoard(mode, *boardValue);

            if(player == O){
                switch(difficulty){
                    //easy
                    case 1 : botEasy(*boardValue, mode);
                        break;
                    //medium
                    case 2 : botMedium(*boardValue, mode);
                        break ;
                    //hard
                    case 3 : botHard(*boardValue, mode);
                        break;
                }
            }

            else {
                printf("\n\n");
                printf("Batas waktu untuk menginput adalah %d detik", maxTime);
                printf("\nMasukan Posisi : ");

                pthread_t timer_thread;
                startTime = 0;
                pthread_create(&timer_thread, NULL, threadTimer, NULL);

                scanf("%d", &inputPos);
                if(inputPos == 0 && iteration == 1){
                    system("cls");
                    mainMenu();
                }
                else if(isTimeout){
                    printf("Melebihi batas waktu input");
                    Sleep(1500);
                    //if(pthread_kill(timer_thread, 0) == 0)
                      //  printf("ad");
                    startTime = 0;
                } else {
                    //pthread_kill(timer_thread, )
                    startTime = 0;
                    if(inputPos > 0 && inputPos <= pow(boardTiles,2)){
                        putInputToBoard(inputPos, *boardValue, mode, &player);
                    } else {
                        printf("\nPosisi tidak valid\n");
                        player++;
                        Sleep(1000);
                    }
                }
            }
            iteration++ ;
            system("cls");

            switch(mode){
                //mode3x3
                case 1 :
                    check = checkWin3x3(boardValue) ;
                break;

                //mode5x5
                case 2 :
                    check = checkWin5x5(boardValue) ;
                break;

                //mode3x3
                case 3 :
                    check = checkWin7x7(boardValue) ;
                break;


            }

            if (check == CONTINUE){
                player--;
            }

        } while(check == CONTINUE);


        showBoard(mode, *boardValue);
        showWinner(player, check, winner);
        setWinOrDrawCount(player, check, &botWinCount, &playerWinCount, &drawCount);

        getch() ;
        system("cls");
        session--;
    } while(session > 0);

    if(playerWinCount > botWinCount)
        writeScore(difficulty);

    do{
        showScoreBoard(playerWinCount, botWinCount, drawCount, session);
        showGameWinner(playerWinCount, botWinCount);

        printf("\n(1) Main Lagi\t(2) Ke Main Menu\n\n");
        printf("Pilih : ");
        scanf("%d", &choice);

        if(choice < 1 || choice > 2){
            printf("Inputan tidak valid");
            system("cls");
        } else{
            system("cls");
            switch(choice){
                case 1 : play(difficulty, initialSession, mode);
                    break;
                case 2 : mainMenu();
                    break;
            }
        }
    } while(choice < 1 || choice > 2);
}

int main()
{
    int choice;
    do{
        showProgramTitle();
        printf("(1) Login    (2) Daftar    (3) Exit\n\n");
        printf("Pilih : ");
        scanf("%d", &choice);

        if(choice < 1 || choice > 3){
            printf("Inputan tidak valid\n");
            Sleep(2000);
            system("cls");
        } else {
            system("cls");
            switch(choice){
                case 1 : login();
                    break;
                case 2 : daftar();
                    break;
                case 3 : exit(0);
                    break;
           }
        }

    }while(choice < 1 || choice > 3);

    mainMenu();

    return 0;
}

