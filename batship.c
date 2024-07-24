//Author: Shira Rotem
//Prupose: final project - Batship

#include <stdio.h>
#define MAX 10

void fileConnection(char array[][MAX]);
void fileConnCheck(FILE *file, char array[][MAX]);
void disDisplayArray(char array[][MAX]);
void winCheck(char array[][MAX], int* tHit, int* win);
void getTurn(int* outRow, int* outCol, int* t);
void checkHitMiss(char hArray[][MAX], char dArray[][MAX], int* outRow, int* outCol);

int main(){

char hiddenA[MAX][MAX], displayA[MAX][MAX], gameC;
int iRow, iCol, hit, check, tRow, tCol, tNum, score;

do{

tNum = 0;

fileConnection(hiddenA); 

for(iRow=0; iRow<MAX; iRow++){
	for(iCol=0; iCol<MAX; iCol++){
		displayA[iRow][iCol]=' ';
	}
}

	
do{

hit = 0;

disDisplayArray(displayA);

for(iRow=0; iRow<MAX; iRow++){
	for(iCol=0; iCol<MAX; iCol++){
		if(hiddenA[iRow][iCol]=='S'){
			hit = hit + 1;
		}
	}
}

winCheck(displayA, &hit, &check);

if(check!=1){
	getTurn(&tRow, &tCol, &tNum);
	checkHitMiss(hiddenA, displayA, &tRow, &tCol);
}

}while(check!=1);

score = 100 - (tNum - hit);

printf("\ncongatulations!!!!\n\nIt took %d turns for you to hit %d spots and destroy all ships\n\nYour score is %d!\n", tNum, hit, score);

printf("\nPlay again? (Y/N) ");
scanf(" %c", &gameC);

}while(gameC=='Y' || gameC=='y');

return 0;
}

//FUNCTIONS
void fileConnection(char array[][MAX]){
	FILE *fileE, *fileM, *fileH;
	char diff='t';
	
	printf("\nLet's play Batship!\n\nPlease select your game difficulty\nEasy (type E)\nMedium (type M)\nHard (type H)\n");
	
	while(diff!='E' && diff!='e' && diff!='M' && diff!='m' && diff!='H' && diff!='h'){

		scanf(" %c", &diff);

		if(diff == 'E' || diff == 'e'){
			fileE = fopen("levelE.txt", "r");
			fileConnCheck(fileE, array);//31 S
			fclose(fileE);
		}
		else if(diff == 'M' || diff == 'm'){
			fileM = fopen("levelM.txt", "r");
			fileConnCheck(fileM, array);//22 S
			fclose(fileM);
		}
		else if(diff == 'H' || diff == 'h'){
			fileH = fopen("levelH.txt", "r");
			fileConnCheck(fileH, array);//11
			fclose(fileH);
		}
		else{
			printf("Invalid letter difficulty. Try again\n");
		}
	}
}
void fileConnCheck(FILE *file, char array[][MAX]){
	int row, col;
	char temp[MAX + 2];
	int tI;

	if(file == NULL){
		printf("Invalid file. Try again\n");
	}
	else{	
		for(row = 0; row < MAX; row++){
			if(fgets(temp, MAX + 2, file) != NULL){
				tI = 0;
				while(temp[tI] != '\0' && temp[tI] != '\n'){
					tI = tI + 1;
				}
				for(col = 0; col < MAX; col++){
					if(col < tI && (temp[col] == ' ' || temp[col] == 'S')){
						array[row][col] = temp[col];
					}
					else{
						array[row][col] = ' '; 
					}
				}
			}
			else{
				for(col = 0; col < MAX; col++){
					array[row][col] = ' ';
				}
			}
		}
	}
}

void disDisplayArray(char array[][MAX]){
	int row, num, col;
	
	printf("   A B C D E F G H I J\n");
		
	for(row=0, num=1; row < MAX; row++, num++){
		printf("%-2d", num);
		for(col = 0; col < MAX; col++){
			printf(" %c", array[row][col]);
		}
		printf("\n");
	}	
}	
void winCheck(char array[][MAX], int* tHit, int* win){
	int row, col, hit=0;
	
	for(row=0; row<MAX; row++){
		for(col=0; col<MAX; col++){
			if(array[row][col]=='X'){
				hit=hit+1;
			}
		}
	}

	if(hit==*tHit){
		*win=1;
	}
	else{
		*win=2;
		printf("        FIRE AWAY!\n(enter a spot in the grid like A1)\n");
	}
	
	
}
void getTurn(int* outRow, int* outCol, int* t){
	int rowNum, check=0;
	char colLett;
	
	while(check!=1){
		scanf(" %c%d", &colLett, &rowNum);	

		if((colLett>='A' && colLett<='J') && (rowNum>=1 && rowNum<=10)){
			check=1;
		}
		else if(colLett>='A' && colLett<='J'){
			printf("Invalid row input. Please try again\n");
		}
		else if(rowNum>=1 && rowNum<=10){
			printf("Invalid column input. Please try again\n");
		}
		else{
			printf("Invalid row and column input. Please try again\n");
		}
	}
	
	*outRow = rowNum - 1;
	*outCol = colLett - 'A';
	
	*t = *t + 1;	
}
void checkHitMiss(char hArray[][MAX], char dArray[][MAX], int* outRow, int* outCol){
	
	if(hArray[*outRow][*outCol]=='S'){
		dArray[*outRow][*outCol] = 'X';
	}
	else if(hArray[*outRow][*outCol]==' '){
		dArray[*outRow][*outCol] = 'O';
	}
	else if(hArray[*outRow][*outCol]=='\n'){
		dArray[*outRow][*outCol] = 'S';
	}
}
