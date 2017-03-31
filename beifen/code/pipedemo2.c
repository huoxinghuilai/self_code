#include<stdio.h>

#define CHILD_MESS "i want a cookis\n"
#define FAR_MESS "testing..\n"
#define oops(m,x) {perror(m),exit(x);}

int main(){
int pipes[2];
int len;
int buf[BUFSIZ];
int read_len;

if(pipe(pipes)==-1)
oops("cannot get a pipe",1);

switch(fork()){
case -1:
oops("cannot fork",2);

case 0:
len=strlen(CHILD_MESS);
while(1){
if(write(pipes[1],CHILD_MESS,len)!=len)
oops("write",3);
sleep(5);
}

default:
len=strlen(FAR_MESS);
while(1){
if(write(pipes[1],FAR_MESS,len)!=len)
oops("write",4);
sleep(1);
read_len=read(pipes[0],buf,BUFSIZ);
if(read_len<=0)
break;
write(1,buf,read_len);
}
}
}


