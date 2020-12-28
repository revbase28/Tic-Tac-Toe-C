#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//Constant
const int MODE_3X3 = 1;
const int MODE_5X5 = 2;
const int MODE_7X7 = 3;
const int EASY = 1;
const int MEDIUM = 2;
const int HARD = 3;

void showBoard(){
    printf("___________________\n");
    printf("|     |     |     |\n");
    printf("|  0  |  0  |  0  |\n");
    printf("|_____|_____|_____|\n");
    printf("|     |     |     |\n");
    printf("|  0  |  0  |  0  |\n");
    printf("|_____|_____|_____|\n");
    printf("|     |     |     |\n");
    printf("|  0  |  0  |  0  |\n");
    printf("|_____|_____|_____|\n\n");
}

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

int main()
{
    int mode;
    int dificullty;

    chooseMode(&mode);
    chooseDifficulty(&dificullty);

    printf("%d %d", mode, dificullty);

    return 0;
}

