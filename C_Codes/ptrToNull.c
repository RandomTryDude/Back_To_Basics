#include <stdio.h>
#include "colors.h"



int main(void){
	int number = 5;

	int *PTR = &number;

	printf("the deferenced value is :  %i \n",*PTR);
	printf("The ptr value is %p\n",PTR);
	


	return 0;




}
