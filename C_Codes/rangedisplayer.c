#include <stdio.h>
#include "colors.h"


int main(void){
	int number;

	printf("Select a number in range 1 , 500 : ");
	scanf("%d",&number);

	if(number >= 1 && number <= 100){
		printf("Number %i in range 1-100",number);
	}
	else if (number >=101 && number <=200){
		printf("Number %i in range 101-200",number);
	}
	else if (number >= 201 && number <=300){
		printf("Number %i in range 201-300",number);
	}
	else if (number >= 301 && number <=400){
		printf("Number %i in range 301-400",number);
	}
	else if (number >=401 && number <= 500){
		printf("Number %i in range 401-500",number);
	}
	else{
		printf("Number not in range");
		return 1;
	}
	return 0;



}
