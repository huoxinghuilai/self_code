//模拟有20000个客户端同时向服务器发请求  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include <arpa/inet.h>  
#include <sys/wait.h>  
#include <string.h>  
#define PROCESS_COUNT 20000  
void func(int argc,char * argv[])  
{  
    int fd =socket(AF_INET,SOCK_STREAM,0);  
    struct sockaddr_in addr;  
    addr.sin_family = AF_INET;  
    addr.sin_port = htons(9988);  
    addr.sin_addr.s_addr =inet_addr("127.0.0.1");  
    connect(fd,(structsockaddr*)&addr,sizeof(addr));  
    if (argc==2)  
       write(fd,argv[1],strlen(argv[1]));  
    else  
        write(fd,"1",1);  
    char buf[1024];  
    //recv(fd,buf,sizeof(buf),0);  
}  
   
int main(int argc,char *argv[])  
{  
    for (int i = 0 ; i <PROCESS_COUNT; i++)  
    {  
        pid_t pid = fork();  
        if (pid == 0)  
        {  
            func(argc,argv);  
            return 0;  
        }  
    }  
    for (int i = 0 ; i <PROCESS_COUNT; i++)  
    {  
        wait(NULL);  
    }  
   
    return 0;  
}  

