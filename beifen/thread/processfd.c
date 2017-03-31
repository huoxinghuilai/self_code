//为输入监视单个的文件描述符的processfd函数
#include <stdio.h>
#include "restart.h"
#define BUFSIZE 1024

void docommand(char *cmd,int cmdsize);

void *processfd(void *arg){
char buf[BUFSIZE];
int fd;
ssize_t nbytes;

fd=*((int)(arg));
for(;;){
if((nbytes=r_read(fd,buf,BUFSIZE))<=0)
break;
docomand(buf,nbytes);
}
return NULL;
