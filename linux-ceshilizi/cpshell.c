#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int process(char *cmdlist[50])
{
printf("i am child\n");
execvp(cmdlist[0],cmdlist);
exit(0);
}

int main()
{
char cmd[50];
int pid;

char *cmdlist[50];
char *flag1,*flag2;
char *cp;
int n=0;
int i=0;

printf("plesae input command:\n");
fgets(cmd,50,stdin);              //获取输入的命令。

flag1=cmd;
flag2=flag1;
while((*flag1)!='\0')
{
if((*flag1)==' ')
{
cp=(char *)malloc(sizeof(char)*n+1);
strncpy(cp,flag2,n);
cp[n]='\0';
cmdlist[i]=cp;
printf("%s\n",cmdlist[i]);
flag2=flag2+n+1;
flag1++;
i++;
n=0;
continue;
}
n++;
flag1++;
}
cp=(char *)malloc(sizeof(char)*n+1);
strncpy(cp,flag2,n);
cp[n]='\0';
cmdlist[i]=cp;
printf("%s\n",cmdlist[i]);

pid=fork();
if(pid==-1)
printf("create process failed.\n");
else if(pid==0)
{
process(cmdlist);//进入子进程，去做相关的命令。
}
else
printf("i am parent\n");

wait(NULL);//等待信号。
printf("it is over\n");
}
