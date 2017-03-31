#include<string.h>


void clent(int readfd,int writefd){

size_t len;
ssize_t n;
char buff[BUFSIZ];

fgets(buff,BUFSIZ,stdin);
len=strlen(buff);
if(buff[len-1]='\n')
len--;

write(writefd,buff,len);

while((n=read(readfd,buff,BUFSIZ))>0)
write(stdout,buff,n);
}
 
