共享内存、消息队列和信号量集等经典的UNIX进程间通信（IPC）基址都在POSIX：XSI扩展中进行了标准化。这些基址允许不相关的进程通过一种合理有效的途径来交换信息，这些机制用键（key）来标识、创建或访问相应的实体。创建这些实体的进程寿命结束之后，这些实体仍可能存在与系统之中，但为了方便起见，POSIX：XSI也提供了列举和删除这些实体的命令解释程序命令。
POSIX进程间通信是POSIX：XSI扩展的一部分，起源与UNIX System V进程间通信。IPC中包含消息队列、信号量集和共享内存，为同一个系统中的进程提供了共享信息的机制。
POSIX：XSI用一个唯一的整数来标识每个IPC对象，这个整数大于或等于零，从对象的获取函数中返回这个整数的方式与open函数返回表示文件描述符的整数的方式类似。
创建或访问一个IPC对象时，你比需制定一个建来说明要创建或访问的特定对象。用下面三种方式之一来选择一个键。
由系统来选择一个键（IPC_PRIVATE）。
直接选一个键。
通过调用ftok请求系统从指定的路径中生成一个键。
命令解释程序和实用程序的POSIX：XSI扩展定义了间擦汗和善出IPC资源的命令解释程序命令。
ipcs命令显示了与POSIX：XSI进程间通信资源有关的信息。可以通过给一个ID或者键来删除单个的资源。可以用ipcrm命令来删除POSIX：XSI进程间通信的资源。
共享内存允许进程对相同的内存段进行读和写。
访问一个共享的内存段
int shmget(key_t key,size_t size,int shmflg);
共享内存段的连接和分离
void *shmat(int shmid,const void *shmaddr,int shmflg);
此处的shmid由shmid=shmget()得来。
用完一个共享内存段时，程序毁掉用shmdt来分离共享内存段。
int shmdt(const void *shmaddr);
此处的shmaddr由shmaddr=shmat()得来。
控制共享内存段
int shnctl(int shmid,int cmd,struct shmid_ds *buf);

