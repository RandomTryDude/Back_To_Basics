#include <stdio.h>
#include <stdlib.h>
#include "colors.h"



int main(void){

	char* ptr;

	ptr = (char*)malloc(10 * sizeof(char)); // 10 could be a var of X value
	
	if(ptr == NULL){
		printf("Failed to allocate memory on the heap\n");
		return 1;
	}
	printf("Memory allocated with success");
	free(ptr);
	
	



	return 0;

}
