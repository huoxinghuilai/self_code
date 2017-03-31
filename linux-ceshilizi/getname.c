#include<netinet.h>
#include<arpa/inet.h>
#incl;due<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	char *host,**names,**addrs; //字符型指针
	struct hostent *hostinfo; //结构体指针 
	
	if(argc==1){
		char name[256];
		gethostname(myname,255); //获取主机名，存放到myname
		host=myname;
	}
	else
		host=garv[1];
	
	hostinfo=gethostbyname(host); //获取主机信息
	if(!hostinfo){
		fprintf(stderr,"cannot get info for host:%s\n",host);
		exit(1);
	}
	
	printf("result for host %s:\n",host);
	printf("name:%s\n",hostinfo->h_name);
	printf("aliases:");
	
	names=hostinfo->h_aliases;
	while(*names){
		printf(" %s",*name);
		names++;
	}
	printf("\n");
	
	if(hostinfo->h_addrtype!=AF_INET){
		fprintf(stderr,"not an IP host!\n");
		exit(1);
	}
	
	addrs=hostinfo->h_addr_list; //保存当前主机的IP地址
	while(*addrs){
		printf(" %s",inet_ntoa(*(struct in_addr *)*addrs));
		addrs++;
	}
	printf("\n");
	exit(0);
}
