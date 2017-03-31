//模拟接收每个客户端发来的请求后并往dbg.txt文件写入一个字节  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/stat.h>  
#include <sys/epoll.h>  
#include <arpa/inet.h>  
#include <sys/wait.h>  
#include <stdlib.h>  
#include <fcntl.h>  
#include <string.h>  
#include <errno.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <signal.h>

//信号处理函数  
void sig_handle(int sig)  
{  
    printf("recv signal :%d\n",sig);  
}  

//主函数
int main(int argc, char * argv[])  
{  
    signal(SIGPIPE,sig_handle); //如果捕捉到SIGPIPE信号，则执行信号处理函数  
    
	if (argc<2)  
    {  
        printf("usage:%s + [count]\n",argv[0]);  
        return 0;  
    }  
    
	unlink("dbg.txt"); //删除已有的dbg.txt文件  
    int dbg = open("dbg.txt",O_CREAT|O_APPEND|O_RDWR,0666); //打开一个新的dbg.txt文件   
    
	int count = atoi(argv[1]); //字符转换  
    
	int fd = socket(AF_INET,SOCK_STREAM,0); //创建套接字  
    
	struct sockaddr_in addr; //设置服务器的地址结构  
    memset(&addr,0,sizeof(addr));  
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr=;	
    addr.sin_port = htons(9988);  
    
	int ret = bind(fd,(struct sockaddr*)&addr,sizeof(addr)); //将套接字描述符与服务器地址绑定  
    if (ret ==-1)  
    {  
        perror("bind");  
        return 0;  
    }  
    
	listen(fd,250); //创建监听队列，容量是250
	
    int is_child_process = 0;//判断在哪个进程中，父进程0，子进程1  
    for (int i = 0 ; i < count ; i++)  
    {  
        pid_t pid = fork();  
        if (pid==0)  
        {  
            is_child_process = 1;  
            break;  
        }  
    }  
  
    struct epoll_event ev;  //设置epoll
    ev.events = EPOLLIN|EPOLLET;  
    ev.data.fd = fd;  
    
	int epfd = epoll_create(1024);//建立epfd的描述符  
    
	int flags = fcntl(fd,F_GETFL);  
    flags |= O_NONBLOCK;  
    fcntl(fd,F_SETFL,flags);  
  
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);  
    while (1)  
    {  
        struct epoll_event evs[10];  
        int process_count = epoll_wait(epfd,evs,10,5000);  
        if (process_count == 0) continue;//如果监听的进程都没有事件产生，则再次进入循环，继续监听  
        for (int i = 0 ; i < process_count ;i++)  
        {  
            if (evs[i].data.fd == fd)  
            {  
                //当进程中的socket描述符是server的socket本身时候，则accept否则就直接操作  
                int ret = accept(evs[i].data.fd,NULL,NULL);  
                if (ret == -1)  
                {  
                    printf("errno:%s",strerror(errno));  
                    //其他错误，直接exit  
                    break;  
                }  
                ev.data.fd = ret;  
                epoll_ctl(epfd,EPOLL_CTL_ADD,ret,&ev);  
            }  
            else  
            {  
                //read or write  
                char buf[1024];  
  
                int ret = read(evs[i].data.fd,buf,sizeof(buf));  
                if (ret == -1)  
                {  
                    perror("read");  
                    if (errno == EINTR)  
                        break;  
                    exit(0);  
                }  
                else if (ret == 0)  
                {  
                    //normal exit  
                    close(evs[i].data.fd);  
                    break;  
                }  
                //printf("recv data %s from pid:%d\n",buf,getpid());  
                write(dbg,"1",1);  
            }  
        }  
    }  
    if (!is_child_process)  
    {  
        for (int i = 0 ; i < count; i ++)  
        {  
            wait(NULL);//等待所有的子进程退出为止  
        }  
    }  
    return 0;  
}  