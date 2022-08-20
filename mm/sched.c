#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct task {
	int id;
	int pro;
	int time;
	int flag;
	struct task *next;
	struct task *prev;
};

// 规划任务优先级为 0 ~ 5，按照优先级创建对应的就绪队列与阻塞队列
struct task *ready_queue[6];
struct task *wait_queue[6];
struct task *head;

struct task *create_ready_queue() {
	int i;

	for (i = 0; i < 6; i++) { 
		ready_queue[i] = (struct task *)malloc(sizeof(struct task));
		ready_queue[i]->next = ready_queue[i];
		ready_queue[i]->prev = ready_queue[i];
	}
}

struct task *create_wait_queue() {
	int i;
	
	for (i = 0; i < 6; i++) { 
		wait_queue[i] = (struct task *)malloc(sizeof(struct task));
		wait_queue[i]->next = wait_queue[i];
		wait_queue[i]->prev = wait_queue[i];
	}
}

int set_prio(struct task *p) {
	p->pro = rand() % 5;
	p->time = 10 - (p->pro);
}

// 初始任务
struct task *init_task(int i) {
	int j;	
	struct task *p;

	head = (struct task *)malloc(sizeof(struct task));
	head->next = head;
	head->prev = head;

	for (j = 0; j < i; j++) {
		p = (struct task *)malloc(sizeof(struct task));
		p->id = j;
		p->flag = 0;	// 标记任务为就绪态

		set_prio(p);

		head->prev->next = p;
		p->prev = head->prev;
		head->prev = p;
		p->next = head;
	}	
}

struct task *add_to_queue(struct task *t[],struct task *p) {
	t[p->pro]->prev->next = p; 
	p->prev = t[p->pro]->prev;
	p->next = t[p->pro];
	t[p->pro]->prev = p;

	return p;
}

struct task *del_from_queue(struct task *t[],struct task *p) {
	t[p->pro]->next = p->next; 
	p->next->prev = t[p->pro];
	p->next = p;
	p->prev = p;

	return p;
}

int check_wait_to_ready() {	// 检查进程是否由阻塞态进入到就绪态，并且转移
	int i;
	struct task *p;

	for (i = 0; i < 6; i++) {	// 阻塞态按优先级来执行
		if(wait_queue[i]->next != wait_queue[i]) {
			p = del_from_queue(wait_queue, wait_queue[i]->next);
			p->flag = 0;
			add_to_queue(ready_queue, p);
			break;
		}
	}
	return 0;
}

int check_ready_to_wait(struct task *p) {
	p->flag = 1;
	add_to_queue(wait_queue, p);

	return 0;
}

// 按照优先级打印
int print_init_task() {
	struct task *p;

	printf("id  prio  time  flag\n",p->id, p->pro, p->time, p->flag);

	p = head->next;
	while (p != head) {	// 遍历任务链表，并从链表中删除
		printf("%2d  %4d  %4d  %4d\n",p->id, p->pro, p->time, p->flag);

		head->next = p->next;
		p->next->prev=head;

		if(p->flag == 0)
			add_to_queue(ready_queue, p);			
		else
			add_to_queue(wait_queue, p);

		p=head->next;
	}
}

int queue_is_empty(struct task *t[]) {
	int i, j = 0;

	for (i = 0; i < 6; i++) {
		if(t[i]->next == t[i])
			j++;
	}
	if(j == 6)
		return 0;
	else
		return 1;
}

int print_ready_queue() {
	int i;
	struct task *p;

	for (i = 0; i < 6; i++) {
		p = ready_queue[i]->next;
		while(p != ready_queue[i]){
			printf("%2d  %4d  %4d  %4d\n",p->id, p->pro, p->time, p->flag);
			p = p->next;
		}
	}

	if(queue_is_empty(ready_queue) == 0)
		printf("就绪队列无进程\n");
}

int print_wait_queue() {
	int i;
	struct task *p;

	for (i = 0; i < 6; i++) {
		p = wait_queue[i]->next;
		while(p != wait_queue[i]) {
			printf("%2d  %4d  %4d  %4d\n",p->id, p->pro, p->time, p->flag);
			p = p->next;
		}	
	}
	if(queue_is_empty(wait_queue) == 0)
		printf("阻塞队列无进程\n");
}

int run() {
	int i, t;
	struct task *p;

	t = rand() % 5;
	
	while (queue_is_empty(ready_queue) == 0 && queue_is_empty(wait_queue) == 1)
		check_wait_to_ready();

	if(t < 3)
		check_wait_to_ready();

       for (i = 0; i < 6; i++) {	// 当任务得到执行时，状态由就绪切换为运行，需要从就绪表中删除
		if(ready_queue[i]->next != ready_queue[i]) {
			p = del_from_queue(ready_queue, ready_queue[i]->next);
			p->flag = 2;
			break;
		}
	}

	while (p->time--) {
		printf("正在运行的进程为:\n");
		printf("%2d  %4d  %4d  %4d\n",p->id, p->pro, p->time, p->flag);

		sleep(1);

		t = rand() % 5;

		if(t >= 3) {
			check_ready_to_wait(p);
		    break;
		}

		
	        if(t < 3) {
		    printf("该进程运行完毕\n");
		    free(p);
		    return 0;
                }

		if (p->time == 0) {
		    set_prio(p);
		    check_ready_to_wait(p);	
		}
	}

    return 0;
}

int main(int argc, char *argv[]) {

	create_ready_queue();
	create_wait_queue();

	init_task(5);

	printf("初始进程:\n");
	print_init_task();

	printf("就绪队列:\n");
	print_ready_queue();
	
	printf("阻塞队列:\n");
	print_wait_queue();
	
	//进程开始运行
	while (1) {
		run();
	//	printf("就绪队列:\n");
	//	print_ready_queue();
	//	printf("阻塞队列:\n");
	//	print_wait_queue();
	}

	return 0;
}
