#include <stdio.h>
#include "colors.h"


int main(void){
    char Var[] = "That's a char?!";
    int Var2 = 5;
    float Var3 = 5.05;

    printf(COLOR_RED "Here's a char : %s \n"COLOR_RESET, Var);
    printf(COLOR_BLUE "Here's an integer : %i \n" COLOR_RESET,Var2);
    printf(COLOR_YELLOW "Here's a float : %f \n" COLOR_RESET, Var3);

    return 0;


}
