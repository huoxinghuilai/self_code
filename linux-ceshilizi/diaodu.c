#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct task{ //进程结构体
	int id; //编号
	int pro; //优先级
	int time; //运行时间`
	int flag; //标志位
	struct task *next; //后继节点
	struct task *prev; //前驱节点
};

struct task *rq[6]; //就绪队列，表长为6
struct task *wq[6]; //阻塞队列
struct task *head; //寄存变量

struct task *mkrq(){ //初始化就绪队列
	int i=0;
	
	for(i;i<6;i++){ 
		rq[i]=(struct task *)malloc(sizeof(struct task));
		rq[i]->next=rq[i];
		rq[i]->prev=rq[i];
	}
}

struct  task *mkwq(){ //初始化阻塞队列
	int i=0;
	
	for(i;i<6;i++){ 
		wq[i]=(struct task *)malloc(sizeof(struct task));
		wq[i]->next=wq[i];
		wq[i]->prev=wq[i];
	}
}

int pt(struct task *p){ //优先级越高，时间片越大
	p->pro=rand()%5; //关键字为5，因为是<=6中最大的素数，而求余后的值作为优先级
	p->time=10-p->pro;
}

struct task *init(int i){
	int j=0;
	
	struct task *p; //形成一个双循环链表
	head=(struct task *)malloc(sizeof(struct task));
	head->next=head;
	head->prev=head;
	for(j;j<i;j++){
		p=(struct task *)malloc(sizeof(struct task));
		p->id=j;
		pt(p);
		p->flag=0; //标记所有进程开始均为就绪态
		head->prev->next=p;
		p->prev=head->prev;
		head->prev=p;
		p->next=head;
	}	
}

struct task *add(struct task *t[],struct task *p){ //加入到队列中
	t[p->pro]->prev->next=p; 
	p->prev=t[p->pro]->prev;
	p->next=t[p->pro];
	t[p->pro]->prev=p;
}

struct task *del(struct task *t[],struct task *p){ //从队列中删除
	t[p->pro]->next=p->next; 
	p->next->prev=t[p->pro];
	p->next=p;
	p->prev=p;
	return p;
}

int cwr(){ //检查进程是否由阻塞态进入到就绪态，并且转移
	int i;
	struct task *p;
	for(i=0;i<6;i++){ //这块自己不知道阻塞态的恢复怎么模拟出来，所以用的是按优先级和链表顺序来执行的
		if(wq[i]->next!=wq[i]){
			p=del(wq,wq[i]->next);
			p->flag=0;
			add(rq,p);
			break;
		}
	}
	return 0;
}

int crw(struct task *p){
	p->flag=1;
	add(wq,p);
	return 0;
}

int pp(){ //打印进程最初的顺序
	struct task *p;
	p=head->next;
	while(p!=head){
		printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
		head->next=p->next;
		p->next->prev=head;
		if(p->flag==0)
			add(rq,p);			
		else
			add(wq,p);
		p=head->next;
	}
}

int cq(struct task *t[]){ //检查队列中是否还有进程
	int i=0;
	int j=0;
	for(i;i<6;i++){
		if(t[i]->next==t[i])
			j++;
	}
	if(j==6)
		return 0;
	else
		return 1;
}

int prq(){ //打印就绪队列中的进程
	int i=0;
	struct task *p;
	for(i;i<6;i++){
		p=rq[i]->next;
		while(p!=rq[i]){
		printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
		p=p->next;
		}
	}
	if(cq(rq)==0)
		printf("就绪队列无进程\n");
}

int pwq(){ //打印阻塞队列中的进程
	int i=0;
	struct task *p;
	for(i;i<6;i++){
		p=wq[i]->next;
		while(p!=wq[i]){
			printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
			p=p->next;
		}	
	}
	if(cq(wq)==0)
		printf("阻塞队列无进程\n");
}

int run(){ //进程运行
	int i;
	struct task *p;
	int t;
	t=rand()%5;
	
	while(cq(rq)==0 && cq(wq)==1) //这块自己没有做好处理
		cwr();
	if(t<3)
		cwr();

    for(i=0;i<6;i++){ //从就绪队列中取出要运行的进程
		if(rq[i]->next!=rq[i]){
			p=del(rq,rq[i]->next);
			p->flag=2;
			break;
		}
	}
	while(--(p->time)){
		printf("正在运行的进程为:\n");
		printf("%d %d %d %d\n",p->id,p->pro,p->time,p->flag);
		Sleep(1);
		t=rand()%5;
		if(t>=3){
			crw(p);
		    break;
		}
		Sleep(1);	
	}
	if(t<3){
		printf("该进程运行完毕\n");
		free(p);
		return 0;
	}
    return 0;
}


int main(){

	//初始化相关的链表
	mkrq();
	mkwq();
	init(5);

	printf("初始进程:\n");
	pp();
	printf("就绪队列:\n");
	prq();
	printf("阻塞队列:\n");
	pwq();
	
	//进程开始运行
	while(1){
		run();
		printf("就绪队列:\n");
		prq();
		printf("阻塞队列:\n");
		pwq();
		if((cq(rq) || cq(wq))==0)
			break;
	}
}
