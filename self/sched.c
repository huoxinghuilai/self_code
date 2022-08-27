#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "task.h"

// 规划任务优先级为 0 ~ 5，按照优先级创建对应的就绪队列与阻塞队列
struct task *ready_queue[6];
struct task *wait_queue[6];

struct task *create_ready_queue(void) {
	int i;

	for (i = 0; i < 6; i++) { 
		ready_queue[i] = (struct task *)malloc(sizeof(struct task));
		ready_queue[i]->next=ready_queue[i];
		ready_queue[i]->prev=ready_queue[i];
	}
}

struct task *create_wait_queue(void) {
	int i;
	
	for (i = 0; i < 6; i++) { 
		wait_queue[i] = (struct task *)malloc(sizeof(struct task));
		wait_queue[i]->next = wait_queue[i];
		wait_queue[i]->prev = wait_queue[i];
	}
}

struct task *add_to_queue(struct task *t[],struct task *p) {
printf("5 p->prio: %d %x %x\n", p->prio, t[p->prio], t[p->prio]->prev);
	t[p->prio]->prev->next = p;
printf("6\n");
	p->prev = t[p->prio]->prev;
printf("7\n");
	p->next = t[p->prio];
printf("8\n");
	t[p->prio]->prev = p;
printf("9\n");

	return p;
}

struct task *del_from_queue(struct task *t[],struct task *p) {
	t[p->prio]->next = p->next; 
	p->next->prev = t[p->prio];
	p->next = p;
	p->prev = p;

	return p;
}

int check_wait_to_ready(void) {	// 检查进程是否由阻塞态进入到就绪态，并且转移
	int i;
	struct task *p;

	for (i = 0; i < 6; i++) {	// 阻塞态按优先级来执行
		if(wait_queue[i]->next != wait_queue[i]) {
			p = del_from_queue(wait_queue, wait_queue[i]->next);
			p->status = READY;
			add_to_queue(ready_queue, p);
			break;
		}
	}

	return 0;
}

int check_ready_to_wait(struct task *p) {
	p->status = PEND;
	add_to_queue(wait_queue, p);

	return 0;
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

int print_ready_queue(void) {
	int i;
	struct task *p;

	for (i = 0; i < 6; i++) {
		p = ready_queue[i]->next;
		while(p != ready_queue[i]){
			printf("%2d  %4d  %4d  %4d\n",p->id, p->prio, p->time, p->status);
			p = p->next;
		}
	}

	if(queue_is_empty(ready_queue) == 0)
		printf("就绪队列无进程\n");
}

int print_wait_queue(void) {
	int i;
	struct task *p;

	for (i = 0; i < 6; i++) {
		p = wait_queue[i]->next;
		while(p != wait_queue[i]) {
			printf("%2d  %4d  %4d  %4d\n",p->id, p->prio, p->time, p->status);
			p = p->next;
		}	
	}
	if(queue_is_empty(wait_queue) == 0)
		printf("阻塞队列无进程\n");
}

int sched_task(void) {
	int i, t;
	struct task *p;

	if (queue_is_empty(ready_queue) == 0 && queue_is_empty(wait_queue) == 0) {
		printf("无任务可执行\n");

		return 1;
	}
	
	if (queue_is_empty(ready_queue) == 0 && queue_is_empty(wait_queue) == 1) {	
		check_wait_to_ready();
	}

      for (i = 0; i < 6; i++) {	// 当任务得到执行时，状态由就绪切换为运行，需要从就绪表中删除
		if(ready_queue[i]->next != ready_queue[i]) {
			p = del_from_queue(ready_queue, ready_queue[i]->next);
			p->status = RUN;
			break;
		}
	}

	printf("运行进程: %s\n", p->name);

	while (p->time--) {

		t = rand() % 5;
		if (t < 3) {
			check_ready_to_wait(p);
			break;
		}

		if (t >= 3) {
			printf("该进程运行完毕\n");
			free(p);
			return 0;
		}

	}

	if (p->time == -1) {
		set_task_prio_and_time(p);
		check_ready_to_wait(p);
	}

    return 0;
}
