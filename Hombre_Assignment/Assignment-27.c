#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>



ssize_t write(int fd,const void *buf , size_t count){
ssize_t (*new_write)(int fd,const void *buf , size_t count);
int result;
new_write = dlsym(RTLD_NEXT, "write");
if(strcmp(buf , "Hello World!\n") == 0){
new_write(fd , "Goodbye , Cruel World\n" ,21);
}
else
{
new_write(fd,buf,count);
}
result = 1;
return result;
}
