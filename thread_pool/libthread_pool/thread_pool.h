#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>

struct list {
	struct list *prev;
	struct list *next;
};

struct task {
	struct list list;	// for list work-queue or wait-queue;
	
	int (*func)(void *);
	char *name;
	void *argv;
};

struct thread_info {		// store thread status;
	pthread_mutex_t mutex;
	int status;

	struct task *task;	
};

struct thread_pool {
	int count;
	int free;		// How many task can exec by pool;
	struct list work_queue;	// work queue;
	struct list wait_queue; // wait queue;
};

extern pthread_t core_pthread;
extern struct thread_pool *pool;

int thread_pool_init(int num);
struct task *create_sub_task(char *name, int (*func)(void *), void *argv);
int show_sub_task(struct list *head);

#endif

