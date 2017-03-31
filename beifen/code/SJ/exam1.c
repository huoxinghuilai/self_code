#include<stdio.h>
#include<stdlib.h>

#define MAX 100
#define NIL -1

struct sem{//消息块类型

int num;
struct sem *next;
int pro;
};

//进程块的数据结构
struct task{

int id;
char state;
int next;//等待号
struct sem *s;//消息队列指针
int count;//运行次数
char addr;//返回地址
int prio;
};

struct sign{//信号量类型

int value;
int first;
};

struct task p[3];
struct sign s[2];
char addr;//当前进程地址
int i,seed,exe;//运行次数，随机数，当前运行进程号

void send(int sender,int receiver,int snum){//

struct sem *p,*q;
p=(struct sem *)malloc(sizeof(struct sem));
p->num=snum;
p->next=NULL;
p->pro=sender;
printf("send message to %d process\n",receiver);
printf("process %d already run %d times",sender,sum);

q=p[receiver].sem;
if(q=NULL)
p[receiver].sem=p;
else{
while(q->next!=NULL)
q=q->next;
q->next=p;
}
}

void receive(int receiver){

struct sem *p,*q;
p=p[receiver].sem;//当前进程的信号量
while(p!=NULL){
printf("receive message from process %d\n",p->pro);
printf("process %d already run %d times\n",p->pro,p->num);//pro和num寄存的？
q=p;
p=p->next;
free(q);
}
p[receiver].sem=NULL;
}

//初始化进程中的变量初值
void init(){

int j;
for(j=1;j<=3;j++){
p[j].id=j;
p[j].state="r";
p[j].next=NIL;//等待
p[j].sem=NULL;//消息队列
printf("process %d priority?",j);
scanf("%d",&p[j].prio);
p[j].count=0;
p[j].addr='0';
}

s[1].value=1;
s[1].first=NIL;
s[2].value=1;
s[2].first=NIL;
exe=NIL;
}

float random(){

int m;
if(seed<0)
m=-seed;
else
m=seed;
seed=(25171*seed+13841)%65536;
return(m/32767.0);
}
//查找处于就绪态并且优先级最高的进程
int find(){

int j,pd,w;
pd=NIL;
w=MAX;
//现在高就绪态中查找
for(j=1;j<=3;j++)
if(p[j].state='r')
if(p[j].prio<w){
w=p[j].prio;
pd=j;
}
if(pd==NIL)
//判断为真，则说明在高就绪态中没有进程，则在低就绪态中查找
for(j=1;j<=3;j++)
if(p[j].state=='t')
if(p[j].prio<w){
w=p[j].prio;
pd=j;
}
return pd;
}

//进程调度程序
int scheduler(){

int pd;
pd=find();//查找应该被调度的进程
if((pd==NIL)&&(exe==NIL))
return NIL;
else{//改变被调度的进程的状态以及优先级
if(pd!=NIL){
if(exe==NIL){
p[pd].state='e';
exe=pd;
printf("process %d is executing\n",exe);
}
else if(p[pd].prio<p[exe],prio){//如果被调度的进程优先级高于当前运行的，则抢占资源优先运行
p[exe].state='r';
printf("process %d enter into ready\n",exe);
p[pd].state='e';
exe=pd;
printf("process %d is executing\n",exe);
}
}
i=p[exe].count;
addr=p[exe].addr;
return exe;
}
}

void block(int se){

int w;
printf("process %d is blocked\n",exe);
p[exe].state='w';
p[exe].next=NIL;
w=s[se].first;
if(w==NIL)
s[se].first=exe;
else{
while(p[w].next!=NIL)
w=p[w].next;
p[w].next=exe;
}
}

void wakeup(int se){

int w;
w=s[se].first;
if(w!=NIL){
s[se].first=p[w].next;
p[w].state='r';
printf("process %d is wakeup\n",w);
}
}

int p(int se,char ad){

s[se].value=s[se].value-1;
if(s[se].value)>=0    
return false;
else{
block(se);
p[exe].count=i;
p[exe].addr=ad; 
exe=NIL;    
return true;              
}
}

int v(int se,char ad){

s[se].value=s[se].value+1;
if(s[se].value>0)
return false;
else{
wakeup(se);
p[exe].count=i;
p[exe].addr=ad;
return true;
}
}

int timeint(char ad){

float x;
x=random();
if((x<0.33)&&(exe==0))
return false;
if((x<0.66)&&(exe==1))
return false;
if((x<1.00)&&(exe==2))
return false;
else{
p[exe].count=i;
p[exe].addr=ad;
p[exe].state='t';
printf("time slice interrupt\n");
printf("process %d enter into ready\n",exe);
exe=NIL;
return true;
}
}

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
receive(1);//？
printf("p1 calls p on sem1\n");
if(p(1,'a'))//请求到信号，去执行stop1
goto stop1;
a1:printf("p1 is exe on its c-s1\n");
if(timeint('b')) 
goto stop1;
b1:s1=s1+1;
printf("s1=%d",s1);
printf("p1 calls v on sem1 quit c-s1\n");
if(v(1,'c'))
goto stop1;
c1:printf("p1 calls on sem2\n");
if(p(2,'d'))
goto stop1;
d1:printf("p1 is exe on its c-s2\n");
if(timeint('e'))
goto stop1;
e1:s2=s2+1;
printf("s2=%d\n",s2);
printf("p1 calls v on sem2 quit c-s2\n");
if(v(2,'f'))
goto stop1;
f1:printf("p1 cyclen count=%d",i+1);
i=i+1;
send(1,2,i);
send(1,3,i);
}
stop1:if(i>=5)
exit(1);
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
printf("s1=%d",s1);
printf("p2 calls v on sem1 quit c-s1\n");
if(v(1,'c'))
goto stop2;
c2:printf("p2 calls on sem2\n");
if(p(2,'d'))
goto stop1;
d2:printf("p2 is exe on its c-s2\n");
if(timeint('e'))
goto stop1;
e2:s2=s2+1;
printf("s2=%d\n",s2);
printf("p1 calls v on sem2 quit c-s2\n");
if(v(2,'f'))
goto stop1;
f1:printf("p2 cyclen count=%d\n",i+1);
i=i+1;
send(1,2,i);
send(1,3,i);
}
stop2:if(i>=5)
exit(1);
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
a2:printf("p3 is exe on its c-s1\n");
if(timeint('b'))
goto stop3;
b2:s2=s2+1;
printf("s2=%d",s2);
printf("p2 calls v on sem1 quit c-s1\n");
if(v(2,'c'))
goto stop3;
c2:printf("p3 cyclen count=%d\n",i+1);
i=i+1;
send(3,1,i);
send(3,2,i);
stop3:if(i>=5)
exit(3);
}

//主程序入口
int main(){

int k,s1,s2;//k用来记录被调度的进程ID，s1，s2是临界资源公用计数器
printf("C.O.S example one\n");
init();//初始化每个进程数据结构中的变量初值
s1=0;
s2=0;
printf("s1=%d,s2=%d\n",s1,s2);
loop:k=scheduler();//调用调度程序返回选中进程号
if(k!=NIL)
switch(k){
case 1:process1(s1,s2);goto loop;
case 2:process2(s1,s2);goto loop;
case 3:process3(s1,s2);goto loop;
default:printf("process identifer error\n");
}
printf("s1=%d,s2=%d",s1,s2);
printf("completed\n");
}

}
