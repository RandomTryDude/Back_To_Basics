#include <stdio.h>


struct basic{

	int banana;

};

int main(void){

struct basic *ptr;
struct basic test;

	ptr= &test;

	test.banana = 5;
	printf("%d\n",test.banana);

	(*ptr).banana = 10;
	printf("%d\n",(*ptr).banana);

	ptr->banana = 15;
	printf("%d\n",ptr->banana);





return 0;
}
