#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

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

typedef struct{
    int x;
    int y;
} Position;

void showProgramTitle(){
    printf("===================================\n");
    printf("            TIC TAC TOE\n");
    printf("===================================\n\n");
}

void chooseMode(int *mode){
    do{
        showProgramTitle();
        printf("(1) 3X3       (2) 5X5       (3) 7X7\n\n");
        printf("Pilih Mode : " );
        scanf("%d", mode);

        if(*mode != MODE_3X3 && *mode != MODE_5X5 && *mode != MODE_7X7){
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
        if (*difficulty!= EASY && *difficulty != MEDIUM && *difficulty != HARD){
            printf("Pilih difficulty dengan menginput angka 1, 2, atau 3 !");
            Sleep(1500);
        }

        system("cls");
    } while(*difficulty!= EASY && *difficulty != MEDIUM && *difficulty != HARD);
}

void initBoardValue(int *arr, int num){
    int boardIndex = 1;
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num ; j++){
            *((arr + i*num) + j) = boardIndex;
            boardIndex++;
        }
    }
}

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
            Board[1][0] != 5 && Board[1][1] != 5 && Board[1][2] != 6 &&  //and nobody win then draw
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

            if(sameCount == 4)
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

            if(sameCount == 4)
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

            if(sameCount == 4){
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

            if(sameCount == 4)
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

            if(sameCount == 4)
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

void theWinner(int player, char winner[10]){
    if (player == O)
        strcpy(winner, "Player") ;
    else if (player == X)
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

void play3X3(int difficulty){
    int boardValue3X3 [3][3];
    int inputPos;
    int check = CONTINUE ;
    int player = O;
    char winner[10] = {};

    do {
        initBoardValue(*boardValue3X3, 3);

        do {
            player = (player % 2);

            showBoard(MODE_3X3, *boardValue3X3);
            printf("\n\n");
            printf("Masukan Posisi : ");
            scanf("%d", &inputPos);

            if(inputPos > 0 && inputPos <= 9){
                putInputToBoard(inputPos, *boardValue3X3, MODE_3X3, &player);
            } else {
                printf("\nPosisi tidak valid\n");
                player++;
                Sleep(1000);
            }
            system("cls");

            check = checkWin3x3(boardValue3X3) ;

            if (check == CONTINUE)
                player--;

        } while(check == CONTINUE);

        showBoard(MODE_3X3, *boardValue3X3);
        showWinner(player, check, winner);

        getch() ;
    } while(1);
}

void play5X5(int difficulty){
    int boardValue5X5 [5][5];
    int inputPos;
    int check = CONTINUE ;
    int player = O;
    char winner[10] = {};

    do{
        initBoardValue(*boardValue5X5, 5);

        do{
            player = (player % 2);

            showBoard(MODE_5X5, *boardValue5X5);
            printf("\n\n");
            printf("Masukan Posisi : ");
            scanf("%d", &inputPos);

            if(inputPos > 0 && inputPos <= 25){
                putInputToBoard(inputPos, *boardValue5X5, MODE_5X5, &player);
            } else {
                printf("\nPosisi tidak valid\n");
                player++ ;
                Sleep(1000);
            }

            check = checkWin5x5(boardValue5X5);
            system("cls");

            if (check == CONTINUE)
                player--;

        } while(check == CONTINUE);

        showBoard(MODE_5X5, *boardValue5X5);
        showWinner(player, check, winner) ;

        getch() ;
        system("cls");
    }while(1) ;
}

void play7X7(int difficulty){
    int boardValue7X7 [7][7];
    int inputPos;
    int check = CONTINUE;
    int player = O;
    char winner[10] = {};

    do {
        initBoardValue(*boardValue7X7, 7);

        do{
            player = (player % 2);

            showBoard(MODE_7X7, *boardValue7X7);
            printf("\n\n");
            printf("Masukan Posisi : ");
            scanf("%d", &inputPos);

            if(inputPos > 0 && inputPos <= 50){
                putInputToBoard(inputPos, *boardValue7X7, MODE_7X7, &player);
            } else {
                printf("\nPosisi tidak valid\n");
                player++;
                Sleep(1000);
            }

            check = checkWin7x7(boardValue7X7);
            system("cls");

            if (check == CONTINUE)
                player--;

        } while(check == CONTINUE);

        showBoard(MODE_7X7, *boardValue7X7);
        showWinner(player, check, winner) ;

        getch() ;
        system("cls");
    } while(1);
}

int main()
{
    int mode;
    int difficullty;

    chooseMode(&mode);
    chooseDifficulty(&difficullty);

    switch(mode){
        case 1 :
            play3X3(difficullty);
        break;

        case 2 :
            play5X5(difficullty);
        break;

        case 3 :
            play7X7(difficullty);
        break;
    }

    return 0;
}

