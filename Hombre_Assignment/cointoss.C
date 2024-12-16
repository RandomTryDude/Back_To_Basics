#include <stdio.h>
#include "colors.h"
#include <stdlib.h>
#include <time.h>

int main(void){
	int flipAmount;
	int head;
	int tail;

	srand(time(0));
	printf("How many times would you like to flip the coin? ");
	
	scanf("%d",&flipAmount);
	
	for(int i=0; i < flipAmount ; i++) {
		int TMP = rand()%2;
		if(TMP == 1){
			head++;
		}
		
		else {
		tail++;
		}
	}
	printf(COLOR_RED "Head %d " COLOR_BLUE "Tail %d " COLOR_RESET "for " COLOR_YELLOW " total throw %d" COLOR_RESET ,head,tail,flipAmount);	

return 0;
}
