#include <stdio.h>
#include "colors.h"
#include <time.h>
#include <stdlib.h>


struct stats_form{
	int points;
	int games;
};


struct stats_form player[5];


int main(void){
	char *color_codes[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW};
	srand(time(0));
	for(int i=0 ; i < 5 ; i++){
		printf("Enter player %i points total: ",i+1);
		scanf("%10d",&player[i].points);
		printf("Enter player %i game total:",i+1);
		scanf("%10d",&player[i].games);
	}
	
	for(int i=0; i<5 ; i++){
		int rd = rand()%4;
		printf("%sPlayer %i scoring average was %.2f ppg\n" COLOR_RESET ,color_codes[rd], i+1,((float)player[i].points / player[i].games));

	}

return 0;

}
