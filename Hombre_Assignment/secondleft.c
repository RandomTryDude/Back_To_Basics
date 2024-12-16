#include <stdio.h>
#include "colors.h"


int main(void){
	
	int uservar;

	printf("Enter the amounts of seconds : ");
	scanf("%i",&uservar);

	int hours = uservar / 3600 ;
	
	int minutes = (uservar % 3600) / 60 ;
	
	int seconds = (uservar % 60) ;

	
	
	printf("Converted time : %d hours %d minutes %d seconds from %i seconds",hours,minutes,seconds,uservar);

	return 0;


	

}
