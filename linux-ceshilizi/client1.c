#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#inlcude<sys/un.h>
#inlcude<unistd.h>
#include<stdlib.h>

int main()
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch='A';
	
	sockfd=socket(AF_UNIX,SOCK_STREAM,0); //创建套接字
	
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,"Server_socket");
	len=sizeof(address);
	
	result=connect(sockfd,(struct sockaddr *)&address,len);//连接服务器
	
	if(result==-1){
		perror("oops:client1");
		exit(1);
	}
	
	write(sockfd,&ch,1);//向服务器写入
	read(sockfd,&ch,1);//从服务器读取
	printf("char from server=%c\n",ch);
	close(sockfd);
	exit(0);
}
