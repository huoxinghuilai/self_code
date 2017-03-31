#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

int sockfd;int len;
struct sockaddr_un address;
int result;
char ch='A';

sockfd=socket(AF_UNIX)
