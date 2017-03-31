#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

void do_something(long t){
int i=0;
for(i=0;i<t;i++)
for(i=0;i<t;i++)
for(i-0;i<t;i++)
;
}

int main(){
pid_t pid;
printf("PID before fork():%d\n",getpid());
pid=fork();
pid_t npid=getpid();
if(pid<0)
perror("fork error\n");
else if(pid==0){
while(1){
printf("I am child process,PID is %d\n",npid);
do_something(10000000);
}
}
else if(pid>=0){
while(1){
printf("I am father process,PID is %d\n",npid);
do_something(10000000);
}
}
return 0;
}

