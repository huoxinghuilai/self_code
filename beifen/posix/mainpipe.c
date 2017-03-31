#include<unistd.h>
#include<stdlib.h>
#include<pipe.h>

void client(int,int),server(int,int);

int main(int argc,char &argv[]){

int pipe1[2],pipe2[2];
pid_t childpid;

pipe(pipe1);
pipe(pipe2);

if((childpid=fork())==0){

close(pipe1[1]);
close(pipe2[0]);

server(pipe1[0],pepe2[1]);
exit(0);
}

close(pipe1[0]);
close(pipe2[1]);

client(pipe1[1],pipe2[0]);

waitpid(chilpid,NULL,0);
exit(0);
}
