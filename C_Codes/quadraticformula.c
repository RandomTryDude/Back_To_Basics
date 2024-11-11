#include <stdio.h>
#include "colors.h"
#include <math.h>


int main(void){
	float a,b,c;


	printf("Value of variable 'A' :");
	scanf("%f",&a);
	printf("Value of variable 'B' :");
	scanf("%f",&b);
	printf("Value of variable 'C' :");
	scanf("%f",&c);

	float denominatorPos;
	float denominatorNeg;
	
	denominatorPos = (-b + sqrtf(b*b - 4 * a * c)) / (2 * a);
	denominatorNeg = (-b - sqrtf(b*b - 4 * a * c)) / (2 * a);

	if(((a * (denominatorPos * denominatorPos ) )+ (b * denominatorPos) + c) == 0){
		printf("Result for + operator %f \n",denominatorPos);
	}
	else{
		
		printf("Result for + operator %f \n but uh... i'd check that",denominatorPos);
	}
	
	if(((a * (denominatorNeg * denominatorNeg )) + (b * denominatorNeg )+ c) == 0){
		printf("Result for - operator %f \n",denominatorNeg);

	}
	else{
		
		printf("Result for - operator %f \n but uh... i'd check that",denominatorNeg);
	}
	

	return 0;








}
