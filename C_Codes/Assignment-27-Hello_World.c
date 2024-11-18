#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void){
	int fd = 1;
	char buf[] = "Hello World!\n";
	int buflen = strlen(buf);
	write(fd , buf , buflen);

	return 0;
}
