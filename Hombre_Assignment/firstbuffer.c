#include <stdio.h>
#include "colors.h"
#include <stdlib.h>

int altmain(void){
	char fullName[32];

	printf(COLOR_YELLOW "Type your full name: \n" COLOR_RESET);
	fgets(fullName,sizeof(fullName),stdin);
	printf(COLOR_BLUE "Welcome home %s" COLOR_RESET , fullName);
	return 0;
// size is static , meaning you can have a name longer that 32 

}

int main(void){
    char *firstname;
    char *secondname;
    
    
    printf("Firstname : ");
    scanf("%ms",&firstname);
    printf("Secondname : ");
    scanf("%ms",&secondname);
    printf("Hello" COLOR_BLUE " %s %s \n" COLOR_RESET ,firstname,secondname);
    
    free(firstname);
    free(secondname);
    
    return 0;

// Size are Dynamic meaning you can input any size of name

}
