#include <stdio.h>
#include "colors.h"



int main(int argc , char *argv[]){
	if(argc != 3){
		printf("Usage: %s Firstname Lastname",argv[0]);
		return 1;
	}
	else {
		printf("Hello %s %s ",argv[1],argv[2]);
	}

	return 0;




}
