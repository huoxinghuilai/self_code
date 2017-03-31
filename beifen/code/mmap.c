#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(int argc, char *argv[]){

    int fd[2];
    unsigned long *ptr;
    FILE *fp;

    if(argc!=3)
	printf("请正确输入！\n");
    printf("%s\n%s\n",argv[1],argv[2]);

    fd[0]=open(argv[1],O_RDONLY);
    printf("%d ",fd[0]);
    fd[1]=open(argv[2],O_RDWR|O_CREAT);
    printf("%d\n",fd[1]);

    ptr=mmap(0,BUFSIZ,PROT_EXEC,MAP_SHARED,fd[0],0);
    printf("%x\n",*ptr);

    write(fd[1],ptr,BUFSIZ);
    munmap(ptr,BUFSIZ);

    return 0;
}
