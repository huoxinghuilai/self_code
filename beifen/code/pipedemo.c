#include<stdio.h>
#include<unistd.h>

int main(){
int len,i,pipes[2];
char buf[BUFSIZ];

if(pipe(pipes)==-1){//pipe返回-1，则管道建立失败，返回0，则管道建立成功
perror("could not make pipe");
exit(1);
}

printf("got a pipe!it is file descriptions: {%d %d}\n",pipes[0],pipes[1]);//管道中的两个文件描述符

while(fgets(buf,BUFSIZ,stdin)){//获取输入
len=strlen(buf);

if(write(pipes[1],buf,len)!=len){//向管道中写入
perror("aritting to pipe");
break;
}

for(i=0;i<len;i++){
buf[i]='X';
len=read(pipes[0],buf,BUFSIZ);//从管道中读取

if(len==-1){//没有读取到
perror("reading from pipe");
break;
}

if(write(1,buf,len)!=len){//向标准输出中写入
perror("waiting to stdout");
break;
}
}
}
}
