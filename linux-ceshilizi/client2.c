#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpe/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char ch='A';
	
	sockfd=socket(af_inet,sock_stream,0);
	
	addres.sin_family=AF_INE;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=9734;
	len=sizeof(address);
	
	result=connect(sockfd,(struct sockaddr *)&address,len);
	
	if(result=-1){
		perror("oops:client1");
		exit(1);
	}
	
	write(sockfd,&ch,1);
	read(sockfd,&ch,1);
	printf("char from server=%c\n",ch);
	close(sockfd);
	exit(0);
}
