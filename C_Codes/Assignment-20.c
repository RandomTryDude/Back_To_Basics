#include <stdio.h>
#include "colors.h"


struct Values{
	int var1;
	char ascii_code;
	float var2;

}; // or here Values; vor example

int main(void){
	struct Values s1; // Either declare it here 
	s1.var1 = 5;
	s1.var2 = 5.05;
	s1.ascii_code = 'A';

	printf("Char %c\nint %i\nfloat %.2f\n",s1.ascii_code,s1.var1,s1.var2);


	return 0;
}
