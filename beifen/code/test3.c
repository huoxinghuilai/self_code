#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
int data_processed;
char buffer[BUFSIZ+1];
int file_description;

printf("%s",argv[1]);
memset(buffer,'\0',sizeof(buffer));
sscanf(argv[1],"%d",&file_description);
data_processed=read(file_description,buffer,BUFSIZ);

printf("%d - read %d bytes: %s\n",getpid(),data_processed,buffer);
exit(EXIT_SUCCESS);
}


