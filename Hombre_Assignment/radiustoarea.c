#include <stdio.h>
#include "colors.h"
#include <stdlib.h>

#define PIE 3.14

int main(void){
	float radius;
	float result;
	
	printf("Length of a radius : ");
	scanf("%f",&radius);

	
	result = PIE * (radius * radius);
	printf("The area is :" COLOR_RED "%f" COLOR_RESET , result);

	
	return 0;	


}
