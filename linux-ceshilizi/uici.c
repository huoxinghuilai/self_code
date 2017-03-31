#include<errno.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/socket.h>
#include"uici.h"
#include"uiciname.h"
#ifndef MAXBACKLOG
#define MAXBACKLOG 50
#endif
static int u_ignore_sigpipe(){
	struct sigaction act;
	if(sigaction(SIGPIPE,(struct sigaction *)NULL,&act)==-1)
		return -1;
	if(act.sa_handler==SIG_DFL){
		act.sa_handler=SIG_IGN;
		if(sigaction(SIGPIPE,&ACT,(struct sigaction *)NULL)==-1)
			return -1;
	}
	return 0;
}
int u_open(u_port_t port){
	int error;
	struct sockaddr_in server;
	int sock;
	int true=1;
	if((u_ignore_sigpipe()==-1)||((sock=socket(AF_INET,SOCK_STREAM,0))==-1))
		return -1;
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char *)&true,sizeof(true))==-1){
		error=errno;
		while((close(sock)==-1)&&(errno=EINTR));
		errno=error;
		return -1;
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons((short)port);
	if((bind(sock,(struct sockaddr *)&server,sizeof(server))==-1)||(listen(sock,MAXBACKLOG)==-1)){
		error=errno;
		while((close(sock)==-1)&&(errno==EINTR));
		errno=error;
		return -1;
	}
	return sock;
}
int u_accept(int fd,char *hostn,int hostnsize){
	int len=sizeof(struct sockaddr);
	struct sockaddr_in netclient;
	int retval;
	while(((retval=accept(fd,(struct sockaddr *)(&netclient),&len))==-1)&&(errno==EINTR))
		;
	if((retval==-1)||(hostn==NULL)||(hostnsize<=0))
		return retval;
	addr2name(netclient.sin_addr,hostn,hoxtnsize);
	return retval;
}
int u_connect(u_port_t port,char *hostn){
	int error;
	int retval;
	struct sockaddr_in server;
	int sock;
	fd_set sockser;
	if(name2addr(hostn,&(serve.sin_addr,s_addr))==-1){
		errno=EINVAL;
		return -1;
	}
	server.sin_port=htons((short)port);
	server.sin_family=AF_INET;
	if((u_ignore_sigpipe()==-1)||((sock=socket(AF_INET,SOCK_STREAM,0))==-1))
		return -1;
	if(((retval=connect(sock,(struct sockaddr *)&server,szeof(server)))==-1)&&((errno==EINTR)||(errno==EALREADY))){
		FD_ZERO(&sockset);
		FD_SET(sock,&sockset);
		while(((retval=select(sock+1,NULL,&sockset,NULL,NULL))==-1)&&(errno==EINTR)){
			FD_ZERO(&sockset);
			FD_SET(sock,&sockset);
		}
	}
	if(retval==-1){
		error=errno;
		while((close(sock)==-1)&&(errno==EINTR));
		errno=error;
		return -1;
	}
	return sock;
}