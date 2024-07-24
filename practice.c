// Author: Shira Rotem
// Purpose: final project - Batship

#include <stdio.h>
#define MAX 10

void fileConnection(char array[][MAX], int* tHit);
void fileConnCheck(FILE *file, char array[][MAX], int* tHit);
void disDisplayArray(char array[][MAX]);
void winCheck(char array[][MAX], int tHit, int* win);
void getTurn(int* outRow, int* outCol, int* t);
void checkHitMiss(char hArray[][MAX], char dArray[][MAX], int outRow, int outCol);

int main() {

    char hiddenA[MAX][MAX], displayA[MAX][MAX];
    int iRow, iCol, hit, check, tRow, tCol, tNum;

    // Game loop
    tNum = 0;
    hit = 0; // Initialize hit to 0

    fileConnection(hiddenA, &hit); // Pass &hit to fileConnection

    for (iRow = 0; iRow < MAX; iRow++) {
        for (iCol = 0; iCol < MAX; iCol++) {
            displayA[iRow][iCol] = ' ';
        }
    }

    check = 2; // Initialize check to ensure the loop starts

    // Main game loop
    do {
        disDisplayArray(displayA);

        winCheck(displayA, hit, &check); // Pass hit to winCheck
        if (check == 1) {
            break;
        }
        getTurn(&tRow, &tCol, &tNum);
        checkHitMiss(hiddenA, displayA, tRow, tCol); // Pass tRow and tCol directly

    } while (check != 1);

    return 0;
}

// FUNCTIONS
void fileConnection(char array[][MAX], int* tHit) { // Added int* tHit
    FILE *fileE, *fileM, *fileH;
    char diff = 't';

    printf("Let's play Batship!\n\nPlease select your game difficulty\nEasy (type E)\nMedium (type M)\nHard (type H)\n");

    while (diff != 'E' && diff != 'e' && diff != 'M' && diff != 'm' && diff != 'H' && diff != 'h') {

        scanf(" %c", &diff);

        if (diff == 'E' || diff == 'e') {
            fileE = fopen("levelE.txt", "r");
            fileConnCheck(fileE, array, tHit); // Pass tHit to fileConnCheck
            fclose(fileE);
        } else if (diff == 'M' || diff == 'm') {
            fileM = fopen("levelM.txt", "r");
            fileConnCheck(fileM, array, tHit); // Pass tHit to fileConnCheck
            fclose(fileM);
        } else if (diff == 'H' || diff == 'h') {
            fileH = fopen("levelH.txt", "r");
            fileConnCheck(fileH, array, tHit); // Pass tHit to fileConnCheck
            fclose(fileH);
        } else {
            printf("Invalid letter difficulty. Try again\n");
        }
    }
}

void fileConnCheck(FILE *file, char array[][MAX], int* tHit) { // Added int* tHit
    int row, col;

    if (file == NULL) {
        printf("Invalid file. Try again");
    } else {
        *tHit = 0; // Initialize tHit to 0
        for (row = 0; row < MAX; row++) {
            for (col = 0; col < MAX; col++) {
                fscanf(file, " %c", &array[row][col]); // Add space before %c to skip whitespace
                if (array[row][col] == 'S') {
                    (*tHit)++; // Increment tHit for each 'S'
                }
            }
        }
    }
}

void disDisplayArray(char array[][MAX]) {
    int row, num, col;

    printf("   A B C D E F G H I J\n");

    for (row = 0, num = 1; row < MAX; row++, num++) {
        printf("%-2d", num);
        for (col = 0; col < MAX; col++) {
            printf(" %c", array[row][col]);
        }
        printf("\n");
    }
}

void winCheck(char array[][MAX], int tHit, int* win) { // Added int tHit
    int row, col, hit = 0;

    for (row = 0; row < MAX; row++) {
        for (col = 0; col < MAX; col++) {
            if (array[row][col] == 'X') {
                hit++;
            }
        }
    }

    if (hit == tHit) {
        *win = 1;
        printf("You won!!\n");
    } else {
        *win = 2;
        printf("        FIRE AWAY!\n(enter a spot in the grid like A1)\n");
    }
}

void getTurn(int* outRow, int* outCol, int* t) {
    int rowNum, check = 0;
    char colLett;

    while (check != 1) {
        scanf(" %c%d", &colLett, &rowNum);

        if ((colLett >= 'A' && colLett <= 'J') && (rowNum >= 1 && rowNum <= 10)) {
            check = 1;
        } else if (colLett >= 'A' && colLett <= 'J') {
            printf("Invalid row input. Please try again\n");
        } else if (rowNum >= 1 && rowNum <= 10) {
            printf("Invalid column input. Please try again\n");
        } else {
            printf("Invalid row and column input. Please try again\n");
        }
    }

    *outRow = rowNum - 1;
    *outCol = colLett - 'A';

    (*t)++;
}

void checkHitMiss(char hArray[][MAX], char dArray[][MAX], int outRow, int outCol) { // Removed pointers
    if (hArray[outRow][outCol] == 'S') {
        dArray[outRow][outCol] = 'X';
    } else {
        dArray[outRow][outCol] = 'O';
    }
}
