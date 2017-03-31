#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>

int main(){
int fd[2],nbytes;
pid_t childpid;
char string[]="data from child process\n";
char readbuffer[32];

if(pipe(fd)<0){
perror("pipe");
exit(1);
}
if((childpid=fork())==-1){
perror("fork");
exit(1);
}
if(childpid==0){
close(fd[0]);
write(fd[1],string,strlen(string));
exit(1);
}
else{
close(fd[1]);
nbytes=read(fd[0],readbuffer,sizeof(readbuffer));
printf("received string: %s",readbuffer);
}
return 0;
}

