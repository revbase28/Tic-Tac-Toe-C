#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//Constant
const int MODE_3X3 = 1;
const int MODE_5X5 = 2;
const int MODE_7X7 = 3;
const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;
const int X = -1;
const int O = 0;

int counter = 0;

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

void showBoardValue(int value, char *buffer){

    static char charRepOfValue[3] = {};
    itoa(value, charRepOfValue, 10);
    buffer = value == 0 ? "O" : value == -1 ? "X" : charRepOfValue;
    //printf("%s", buffer);
}

void showBoard(int mode, int *boardValue){
    char charRepValue [mode == 1 ? 3*3 : mode == 2 ? 5*5 : 7*7][3];
    int counter = 0;

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
            printf("|  %s  |  %s  |  %s  |\n", charRepValue[0], charRepValue[1], charRepValue[2]);
            printf("|_____|_____|_____|\n");
            printf("|     |     |     |\n");
            printf("|  %s  |  %s  |  %s  |\n", charRepValue[3], charRepValue[4], charRepValue[5]);
            printf("|_____|_____|_____|\n");
            printf("|     |     |     |\n");
            printf("|  %s  |  %s  |  %s  |\n", charRepValue[6], charRepValue[7], charRepValue[8]);
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

            printf("|  %s  |  %s  |  %s  |  %s  |  %s  |\n" , charRepValue[0], charRepValue[1], charRepValue[2], charRepValue[3], charRepValue[4]);

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            printf("|  %s  |  %s  |  %s  |  %s  | %s  |\n" , charRepValue[5], charRepValue[6], charRepValue[7], charRepValue[8], charRepValue[9]);

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[10], charRepValue[11], charRepValue[12], charRepValue[13], charRepValue[14]);

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[15], charRepValue[16], charRepValue[17], charRepValue[18], charRepValue[19]);

            printf("|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[20], charRepValue[21], charRepValue[22], charRepValue[23], charRepValue[24]);

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

            printf("|  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n" , charRepValue[0], charRepValue[1], charRepValue[2], charRepValue[3], charRepValue[4], charRepValue[5], charRepValue[6]);

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            printf("|  %s  |  %s  | %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[7], charRepValue[8], charRepValue[9], charRepValue[10], charRepValue[11], charRepValue[12], charRepValue[13]);

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[14], charRepValue[15], charRepValue[16], charRepValue[17], charRepValue[18], charRepValue[19], charRepValue[20]);

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[21], charRepValue[22], charRepValue[23], charRepValue[24], charRepValue[25], charRepValue[26], charRepValue[27]);

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[28], charRepValue[29], charRepValue[30], charRepValue[31], charRepValue[32], charRepValue[33], charRepValue[34]);

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[35], charRepValue[36], charRepValue[37], charRepValue[38], charRepValue[39], charRepValue[40], charRepValue[41]);

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
            printf("|     |     |     |     |     |     |     |\n");

            printf("| %s  | %s  | %s  | %s  | %s  | %s  | %s  |\n" , charRepValue[42], charRepValue[43], charRepValue[44], charRepValue[45], charRepValue[46], charRepValue[47], charRepValue[48]);

            printf("|_____|_____|_____|_____|_____|_____|_____|\n");
        break;
    }
}

void play3X3(int difficulty){
    int boardValue3X3 [3][3];
    initBoardValue(*boardValue3X3, 3);
    showBoard(MODE_3X3, *boardValue3X3);
}

void play5X5(int difficulty){
    int boardValue5X5 [5][5];
    initBoardValue(*boardValue5X5, 5);
    showBoard(MODE_5X5, *boardValue5X5);
}

void play7X7(int difficulty){
    int boardValue7X7 [7][7];
    initBoardValue(*boardValue7X7, 7);
    showBoard(MODE_7X7, *boardValue7X7);
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

