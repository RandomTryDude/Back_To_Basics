#include <stdio.h>
#include "colors.h"
#include <string.h>


int main(void){
	int score[10];
	char YN[2];
	int total = 0;
	int scorecount;
	
	for(scorecount = 0; scorecount <= 8 && strcmp(YN,"N") != 0 ; scorecount++ ){
		printf("Enter a test score: ");
		scanf("%d",&score[scorecount]);
		total += score[scorecount];	
		
		printf("Would you like to continue? Y/N: ");
		scanf("%1s",YN);
		
	}
	
	printf("Average : %.2f",((double)total/scorecount) ); 
	
	return 0;










}
