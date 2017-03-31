#include<ctype.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include"uiciname.h"
#ifdef REENTRANCY
#define REENTRANCY REETRANT_NONE
#endif
#if REENTRANCY==REETRANT_MUTEX
#include<pthread.h>
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
#endif
#if REENTRANCY=REETRANT_NONE
void addr2name(struct in_addr addr,char *name,int namelen){
	struct hostent *hostptr;
	hostptr=gethostbyaddr((char *)&addr,4,AF_INET);
	if(hostptr==NULL)
		strncpy(name,inet_ntoa(addr),namelen-1);
	else
		strncpy(name,hostptr->h_name,namelen-1);
	name[namelen-1]=0;
}
int name2addr(char *name,in_addr_t *addrp){
	struct hostent *hp;
	if(isdigit((int)(*name)))
		*addrp=inet_addr(name);
	else{
		hp=gethostbyname(name);
		if(hp==NULL)
			return -1;
		memcpy((char *)addrp,hp->h_addr_list[0],hp->h_length);
	}
	return 0;
}
#elif REENTRANCY==REETRANT_R
#define GETHOST_BUFSIZE 8192
void addr2name(struct in_addr addr,char *name,int namelen){
	char buf[GETHOST_BUFSIZE];
	int h_error;
	struct hostent *hp;
	struct hostent result;
	hp=gethosbyaddr_r((char *)&addr,4,AF_INFT,&result,buf,GETHOST_BUFSIZE,&h_error);
	if(hp==NULL)
		strncpy(name,inet_ntoa(addr),namelen-1);
	else
		strncpy(name,hp->h-name,namelen-1);
	name[namelen-1]=0;
}
