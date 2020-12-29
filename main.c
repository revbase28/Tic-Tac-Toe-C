#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

//Constant
const int MODE_3X3 = 1;
const int MODE_5X5 = 2;
const int MODE_7X7 = 3;
const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;
const int X = -1;
const int O = 0;

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
                    if(*((boardValue + i*3) + j) == 0){
                        strcpy(charRepValue[counter], "O");
                    }

                    else if(*((boardValue + i*3) + j) == -1){
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

void putInputToBoard(int inputPos, int *boardValue, int mode){
    Position pos;
    switch(mode){
        //Mode 3X3
        case 1:
            pos.x = (inputPos - 1) / 3;
            pos.y = (inputPos-1) % 3;

            if( *((boardValue + pos.x*3) + pos.y) != 0 && *((boardValue + pos.x*3) + pos.y) != -1)
                *((boardValue + pos.x*3) + pos.y) = 0;
            else{
                printf("\nPosisi sudah terisi\n");
                Sleep(1000);
            }

        break;

        //Mode 5X5
        case 2:
            pos.x = (inputPos - 1) / 5;
            pos.y = (inputPos-1) % 5;

            if( *((boardValue + pos.x*5) + pos.y) != 0 && *((boardValue + pos.x*5) + pos.y) != -1)
                *((boardValue + pos.x*5) + pos.y) = 0;
            else{
                printf("\nPosisi sudah terisi\n");
                Sleep(1000);
            }

        break;

        //Mode 7X7
        case 3:
            pos.x = (inputPos - 1) / 7;
            pos.y = (inputPos-1) % 7;

            if( *((boardValue + pos.x*7) + pos.y) != 0 && *((boardValue + pos.x*7) + pos.y) != -1)
                *((boardValue + pos.x*7) + pos.y) = 0;
            else{
                printf("\nPosisi sudah terisi\n");
                Sleep(1000);
            }

        break;
    }
}

void play3X3(int difficulty){
    int boardValue3X3 [3][3];
    int inputPos;

    initBoardValue(*boardValue3X3, 3);

    do{
        showBoard(MODE_3X3, *boardValue3X3);
        printf("\n\n");
        printf("Masukan Posisi : ");
        scanf("%d", &inputPos);

        if(inputPos > 0 && inputPos <= 9){
            putInputToBoard(inputPos, *boardValue3X3, MODE_3X3);
        } else {
            printf("\nPosisi tidak valid\n");
            Sleep(1000);
        }
        system("cls");
    } while(true);

}

void play5X5(int difficulty){
    int boardValue5X5 [5][5];
    int inputPos;

    initBoardValue(*boardValue5X5, 5);
    do{
        showBoard(MODE_5X5, *boardValue5X5);
        printf("\n\n");
        printf("Masukan Posisi : ");
        scanf("%d", &inputPos);

        if(inputPos > 0 && inputPos <= 25){
            putInputToBoard(inputPos, *boardValue5X5, MODE_5X5);
        } else {
            printf("\nPosisi tidak valid\n");
            Sleep(1000);
        }
        system("cls");
    } while(true);

}

void play7X7(int difficulty){
    int boardValue7X7 [7][7];
    int inputPos;

    initBoardValue(*boardValue7X7, 7);

    do{
        showBoard(MODE_7X7, *boardValue7X7);
        printf("\n\n");
        printf("Masukan Posisi : ");
        scanf("%d", &inputPos);

        if(inputPos > 0 && inputPos <= 50){
            putInputToBoard(inputPos, *boardValue7X7, MODE_7X7);
        } else {
            printf("\nPosisi tidak valid\n");
            Sleep(1000);
        }
        system("cls");
    } while(true);
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

