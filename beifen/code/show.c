#include<unistd.h>
#include<stdio.h>

int main(){

pid_t pid;

int i,j;
scanf("%d %d",&i,&j);

pid=fork();

if(pid==-1)
printf("wrong!\n");

if(pid==0){
printf("%d %d\n",i,j);
printf("test1\n");
}

printf("%d %d\n",i,j);
printf("test2\n");
}
