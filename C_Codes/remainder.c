#include <stdio.h>
#include "colors.h"

int main(void){

	int numerator;
	int denominator;

	printf("Enter a numerator: ");
	scanf("%d",&numerator);
	printf("Enter a denominator: ");
	scanf("%d",&denominator);

	int calc = numerator % denominator;

	if(calc != 0){
		printf(COLOR_RED "There's a remainder!# : " COLOR_RESET "%i" COLOR_RESET,calc);
		     }
	else{
		printf(COLOR_GREEN "Nothing to see here!" COLOR_RESET);
	}
	return 0;

	

}
