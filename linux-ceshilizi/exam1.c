#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 100//相关的宏定义
#define NIL -1
#define false 0
#define true 1

struct sem{//定义进程的消息结构体
int num;
int pro;
struct sem *next;
};


struct task{//定义任务结构体

int id;//编号
char state;//状态
int next;//等待同一个信号量的下一个进程
struct sem *s;//消息
int count;//运行次数
char addr;//返回时的地址
int prio;//优先级
};

struct sign{//定义信号量结构体
int value;
int first;//等待该信号量的第一个进程
};

struct task pcb[4];//定义了全局变量
struct sign si[3];
char addr;
int i,seed,exe;

void eexit(int n){
	pcb[n].state='c';
	printf("prcess %d is completed\n",n);
	exe=NIL;
}

void send(int sender,int receiver,int snum){//进程发送消息

struct sem *p,*q;//定义了两个消息结构体
p=(struct sem *)malloc(sizeof(struct sem));//分配空间
p->num=snum;//p->num运行次数
p->next=NULL;//指向的下一个节点为空
p->pro=sender;//p->pro为发送进程的编号
printf("send message to %d process\n",receiver);
printf("process %d already run %d times\n",sender,snum);

q=pcb[receiver].s;//q为接收进程的信息指针
if(q==NULL)
pcb[receiver].s=p;
else{
while(q->next!=NULL)
q=q->next;
q->next=p;
}
}

void wakeup(int se){

int w;
w=si[se].first;
if(w!=NIL){
si[se].first=pcb[w].next;
pcb[w].state='r';
printf("process %d is wakeup\n",w);
}
} 

int v(int se,char ad){

si[se].value=si[se].value+1;
if(si[se].value>0)
return false;
else{
wakeup(se);
pcb[exe].count=i;
pcb[exe].addr=ad;
return true;
}
}

float random(){

int m;
if(seed<0)
m=-seed;
else
m=seed;
seed=(25171*seed+13841)%65536;
return (float)(m/32767.0);
}

int timeint(char ad){

float x;
x=random();
if((x<0.33)&&(exe==1))
return false;
if((x<0.66)&&(exe==2))
return false;
if((x<1.00)&&(exe==3))
return false;
else{
pcb[exe].count=i;
pcb[exe].addr=ad;
pcb[exe].state='t';
printf("time slice interrupt\n");
printf("process %d enter into ready\n",exe);
exe=NIL;
return true;
}
}

void block(int se){//进程阻塞处理

int w;
printf("process %d is blocked\n",exe);
pcb[exe].state='w';//状态改为等待状态
pcb[exe].next=NIL;//把等待该进程释放信号的进程清空
w=si[se].first;//记录
if(w==NIL)
si[se].first=exe;
else{
while(pcb[w].next!=NIL)
w=pcb[w].next;
pcb[w].next=exe;
}
}

int p(int se,char ad){

si[se].value=si[se].value-1;//信号量减1
if(si[se].value>=0 )   
return false;
else{
block(se);
pcb[exe].count=i;
pcb[exe].addr=ad; 
exe=NIL;    
return true;          
}
}

void receive(int receiver){//进程接收信号量

struct sem *p,*q;
p=pcb[receiver].s;
while(p!=NULL){
printf("receive message from process %d\n",p->pro);
printf("process %d already run %d times\n",p->pro,p->num);
q=p;
p=p->next;
free(q);
}
pcb[receiver].s=NULL;
}

void process3(int s1,int s2){

if(addr=='a')
goto a3;
if(addr=='b')
goto b3;
if(addr=='c')
goto c3;
while(i<5){
receive(3);
printf("p3 calls p on sem1\n");
if(p(2,'a'))
goto stop3;
a3:printf("p3 is exe on its c-s1\n");
if(timeint('b'))
goto stop3;
b3:s2=s2+1;
printf("s2=%d",s2);
printf("p3 calls v on sem1 quit c-s1\n");
if(v(2,'c'))
goto stop3;
c3:printf("p3 cyclen count=%d\n",i+1);
i=i+1;
send(3,1,i);
send(3,2,i);
stop3:if(i>=5)
eexit(3);
}
}

void process2(int s1,int s2){

if(addr=='a')
goto a2;
if(addr=='b')
goto b2;
if(addr=='c')
goto c2;
if(addr=='d')
goto d2;
if(addr=='e')
goto e2;
if(addr=='f')
goto f2;
while(i<5){
receive(2);
printf("p2 calls p on sem1\n");
if(p(1,'a'))
goto stop2;
a2:printf("p2 is exe on its c-s1\n");
if(timeint('b'))
goto stop2;
b2:s1=s1+1;
printf("s1=%d\n",s1);
printf("p2 calls v on sem1 quit c-s1\n");
if(v(1,'c'))
goto stop2;
c2:printf("p2 calls on sem2\n");
if(p(2,'d'))
goto stop2;
d2:printf("p2 is exe on its c-s2\n");
if(timeint('e'))
goto stop2;
e2:s2=s2+1;
printf("s2=%d\n",s2);
printf("p2 calls v on sem2 quit c-s2\n");
if(v(2,'f'))
goto stop2;
f2:printf("p2 cyclen count=%d\n",i+1);
i=i+1;
send(2,1,i);
send(2,3,i);
}
stop2:if(i>=5)
eexit(2);
}

//进程1的运行
void process1(int s1,int s2){

if(addr=='a')
goto a1;
if(addr=='b')
goto b1;
if(addr=='c')
goto c1;
if(addr=='d')
goto d1;
if(addr=='e')
goto e1;
if(addr=='f')
goto f1;
while(i<5){
receive(1);//查看receive函数
printf("p1 calls p on sem1\n");//p1进程请求信号量sem1
if(p(1,'a'))//查看p函数，地址为a
goto stop1;
a1:printf("p1 is exe on its c-s1\n");
if(timeint('b'))//地址为b 
goto stop1;
b1:s1=s1+1;
printf("s1=%d\n",s1);
printf("p1 calls v on sem1 quit c-s1\n");
if(v(1,'c'))//地址为c
goto stop1;
c1:printf("p1 calls on sem2\n");
if(p(2,'d'))//地址为d
goto stop1;
d1:printf("p1 is exe on its c-s2\n");
if(timeint('e'))//地址为e
goto stop1;
e1:s2=s2+1;
printf("s2=%d\n",s2);
printf("p1 calls v on sem2 quit c-s2\n");
if(v(2,'f'))//地址为f
goto stop1;
f1:printf("p1 cyclen count=%d\n",i+1);
i=i+1;
send(1,2,i);
send(1,3,i);
}
stop1:if(i>=5)
eexit(1);
}

//查找进程函数
int find(){

int j,pd,w;
pd=NIL;
w=MAX;//设置一个最大的优先级为100

for(j=1;j<=3;j++)//在最高就绪态中开始循环三次，找出优先级最高的进程
if(pcb[j].state='r')
if(pcb[j].prio<w){
w=pcb[j].prio;
pd=j;
}
//如果在最高就绪态中没有，则在最低就绪态开始寻找优先级最高的进程
if(pd==NIL)
for(j=1;j<=3;j++)
if(pcb[j].state=='t')
if(pcb[j].prio<w){
w=pcb[j].prio;
pd=j;
}
return pd;//返回找出的进程ID
}

//调度进程
int scheduler(){

int pd;//记录进程ID
pd=find();//查看find函数
if((pd==NIL)&&(exe==NIL))
return NIL;
else{
if(pd!=NIL){//没有正在执行的进程，则把找到的进程放入执行态
if(exe==NIL){
pcb[pd].state='e';//把进程状态改为e
exe=pd;//记录当前运行的进程ID
printf("process %d is executing\n",exe);
}
else if(pcb[pd].prio<pcb[exe].prio){//如果调度的进程优先级比正在执行的优先级高，则抢占它的资源，优先运行
pcb[exe].state='r';//把正在执行的进程放入到高就绪态
printf("process %d enter into ready\n",exe);
pcb[pd].state='e';//把调度的进程放入执行态
exe=pd;//记录当前进程的ID
printf("process %d is executing\n",exe);
}
}
i=pcb[exe].count;//记录当前进程运行的次数
addr=pcb[exe].addr;//记录当前进程的地址
return exe;//返回进程ID
}
}

//初始化进程
void init(){

int j;
for(j=1;j<=3;j++){//3次循环，分别给3个进程进行初始化
pcb[j].id=j;//进程标识号
pcb[j].state='r';//开始都处于高就绪态
pcb[j].next=NIL;//等待同一个信号量的下一个进程的ID
pcb[j].s=NULL;//信息块指针
printf("process %d priority?  ",j);
scanf("%d",&pcb[j].prio);//优先级
pcb[j].count=0;//运行的次数
pcb[j].addr='0';//返回的地址
}

si[1].value=1;//信号量，表示资源是否被占用，为1，没有占用，为0，则被占用
si[1].first=NIL;//等待该信号量的下一个进程ID
si[2].value=1;
si[2].first=NIL;
exe=NIL;//当前运行的进程的标识号
}



//主程序入口地址
int main(){

int k,s1,s2;//k用来记录被调度进程的ID；s1,s2是临界资源公用的计数器
printf("C.O.S example one\n");
init();//进程结构体初始化，赋给结构体中每个变量初值
s1=0;
s2=0;
printf("s1=%d,s2=%d\n",s1,s2);
loop:k=scheduler();//开始调度进程，即开始模拟管理进程
if(k!=NIL)
switch(k){//根据k的值，即ID号，来运行不同的进程
case 1:process1(s1,s2);goto loop;//查看process_函数
case 2:process2(s1,s2);goto loop;
case 3:process3(s1,s2);goto loop;
default:printf("process identifer error\n");
}
printf("s1=%d,s2=%d",s1,s2);
printf("completed\n");
}


