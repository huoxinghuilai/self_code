#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define oops(m,x) {perror(m);exit(x);}

int make_dgram_server_socket(int); //建立数据报服务器
int get_internet_address(char *,int *,struct sockaddr_in *); //获取IP地址
void say_who_called(struct sockaddr_in *); //谁在连接服务器

int main(int ac,char *av[]){

int port; //端口号
int sock; //套接口
char buf[BUFSIZ]; //字符数组
size_t msglen; //长度
struct sockaddr_in saddr; //地址
socklen_t saddrlen; //地址长度

if(ac==1 || (port=atoi(av[1])) <=0){ //没有输入端口号
fprintf(stderr,"usage: dgrecv portnumber\n");
exit(1);
}

if((sock=make_dgram_server_socker(port))==-1)
oops("cannot make socket",2);

saddrlen=sizeof(saddr);
while((msglen=recvfrom(sock,buf,BUFSIZ,0,&saddr,&saddrlen))>0){

buf[msglen]='\0';
printf("dgrecv: got a messag: %s\n",buf);
say_who_called(&saddr);
}

return 0;
}

void say_who_called(struct sockaddr_in *addrp){

char host[BUFSIZ];
int port;

get_internet_address(host,BUFSIZ,&port,addrp);
printf("from: %s: %d\n",host,port);
}


