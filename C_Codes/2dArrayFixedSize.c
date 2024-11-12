#include <stdio.h>
#include "colors.h" 


//total
//average

int main(void){
	int players_match[4][5] ;
	int average_total[2][5] = {0} ;
	
	for(int i = 0 ; i < 4 ; i++){
		printf("Game #%i\n",i+1);
		for(int k = 0 ; k < 5 ; k++){
			printf("Enter scoring total for Player #%i: ",k+1);
			scanf("%d",&players_match[i][k]);
			
			average_total[0][k] += players_match[i][k];
		}

	}
	for(int i = 0 ; i < 5 ; i++){
		average_total[1][i] = (float)(average_total[0][i] / 4 );
	}
	float res = average_total[1][0];
	int topPlayer = 1 ;
	for(int i = 0 ; i < 5 ; i++){
		
		if(res <= average_total[1][i]){
			res = average_total[1][i];
			topPlayer++;
			}
		}	
	

	printf("Player #%d had the highest scoring average at %.2f points per game",topPlayer,res);
	
	return 0;
}
