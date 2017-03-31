//管道
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(){
int data_processed;
int file_pipes[2];
const char some_data[]="123";
char buffer[BUFSIZ+1];

memset(buffer,'\0',sizeof(buffer));//buffer里面赋值为空。

if(pipe(file_pipes)==0)
{
data_processed=write(file_pipes[1],some_data,strlen(some_data));//系统调用，write返回3。
printf("wrote %d bytes\n",data_processed);
data_processed=read(file_pipes[0],buffer,BUFSIZ);//系统调用，read返回3。
printf("read %d bytes: %s\n",data_processed,buffer);
exit(EXIT_SUCCESS);
}
exit(EXIT_FAILURE);
}

//int pipe(int file_discriptor[2]);
//数据基于先进先出的原则，即队列。
//写道file_descriptor[1]的数据可以从file_descriptor[0]读回来。
