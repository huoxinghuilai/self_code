#include<unistd.h>
#include<stdio.h>

struct pipefs{
	char *str;
	int fd[2];
};

struct pipefs *piper(){
	struct MEM *pipe;
	pipe=(struct pipefs *)malloc(sizeof(struct pipefs));
	pipe->str="\0";
	pipe->fd[0]=0;
	pipe->fd[1]=1;
	return pipe;	
}

struct pipefs *pipe_write(struct pipefs *pipe){
	write(pipe->fd[0],pipe->str,BUFSIZ);
	return pipe;
}

struct pipefs *pipe_read(struct pipefs *pipe){
	read(pipe->fd[1],pipe->str,BUFSIZ);
	return pipe;
}

int pc(struct pipefs *pipe){
	pipe_write(struct pipefs *pipe);
	return 0;
}

int pp(struct pipefs *pipe){
	pipe_read(struct pipefs *pipe);
	return 0;
}

int main(int argc,char *argv[]){
	pid_t pid;
	struct pipefs *pipe
	pipe=piper()；
	pid=fork();
	if(pid==0)
		pc(pipe);
	wait(pid);
	pp(pipe);
}