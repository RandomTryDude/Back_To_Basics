#include <stdio.h>
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b|34m"
#define COLOR_RESET "\x1b[0m"
int main(void){
	printf(COLOR_RED "Hello World!\n" COLOR_RESET);

	return 0;
}
