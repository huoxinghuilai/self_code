#include<string.h>


void server(int readfd,int writefd){

int fd;
ssize_t n;
char buff[BUFSIZ];

if((n=read(readfd,buff,BUFSIZ))==0)
err_quit("end-of-file while reading pathname");
buff[n]='\0';

if((fd=open(buff,ORDONLY))<0){
snprintf(buff+n,sizeof(buff)-n,":can't open, %s\n",strerror(errno));
n=strlen(buff);
write(writefd,buff,n);
}
else{
while((n=read(fd,buff,n))>0)
write(writefd,buff,n);
close(fd);
}
}
