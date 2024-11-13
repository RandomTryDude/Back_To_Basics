#include <stdio.h>
#include "colors.h"



int main(void){
	int number = 15;

	int *ptr = &number;

	printf("The value of int variable is %d\n",number);
	printf("The value of the pointer to the int variable is : %d\n",ptr);
	printf("The memory address of the int variable is: %d\n",&number);
	printf("The value held at the memory localtion that the pointer is pointing to is : %d\n",*ptr);




return 0;
}
