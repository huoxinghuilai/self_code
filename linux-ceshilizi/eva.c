/*建立服务器*/
#include<socket.h> //需要的头文件

/*创建套接字*/
int sockfd;
sockfd=socket(AF_INET,SOCK_STREAM,0); 
 
/*设置套接字相关的信息*/
struct sockaddr_in *addrs,*addrc;
int addrlens,addrlenc;
addr->sin_family=AF_INET;
addr->sin_port=;
addr->sin_addr.s_addr=;
addrlen=sizeof(addr);

/*绑定套接字和相关的信息*/
bind(sockfd,(struct sockaddr_in *)addr,addrlen);

/*设置接收队列，监听的套接字以及最大数目*/
listen(sockfd,5);

/*循环处理队列中收到的信号，这块可以用多个方法*/
/*为每一个信号fork一个进程*/
while (!fork()){
	
	/*接收请求并且处理*/
	int fd;
	fd=accept(sockfd,(struct sockaddr_in *)addrc,addrlenc);
	if(fd>=0){
	write(fd,&ch,1);
	close(fd);
}

/*使用select系统调用*/
fd_set *fds;
FD_ZERO(fds);
FD_SET(sockfd,fds);
while(1){
//select();
//accept();	
}
//close();