#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thread_pool.h"

#define STOP 0
#define READY 1
#define RUNNING 2

static struct thread_info *thread_info;
struct thread_pool *pool = NULL;

pthread_t core_pthread;			// pool's core thread;
pthread_t *sub_thread;			// pool's sub thread;

void delete_task_from_queue(struct task *task);

void *sub_thread_exec(void *argv)
{
	struct thread_info *task_info;

	task_info = (struct thread_info *)argv;
	
	while(1) {
		pthread_mutex_lock(&task_info->mutex);
		if (task_info->status == READY) {
			printf("%s %d %s\n", __func__, __LINE__, task_info->task->name);
			task_info->task->func(task_info->task->argv);

			delete_task_from_queue(task_info->task);
			task_info->task = NULL;
			task_info->status = STOP;
			pool->free++;
		}
		pthread_mutex_unlock(&task_info->mutex);
	}
}


/*
 * sub thread info change;
 */
int sub_thread_info_change(struct task *task)
{
	int i;

	for (i = 0; i < pool->count; i++) {

		pthread_mutex_lock(&thread_info[i].mutex);
		if (thread_info[i].status == STOP) {
			thread_info[i].task = task;
			thread_info[i].status = READY;	

			pthread_mutex_unlock(&thread_info[i].mutex);
			return 0;
		}
		pthread_mutex_unlock(&thread_info[i].mutex);
	}

	return -1;
}

/*
 * insert task to queue;
 */
void insert_task_to_queue(struct task *task, struct list *head)
{

	struct list *list = &task->list;

	list->next = head;
	list->prev = head->prev;
	head->prev->next = list;
	head->prev = list;

	if (head == &(pool->wait_queue))
		pool->free -= 1;
}

/*
 * delete task from queue;
 */

void delete_task_from_queue(struct task *task)
{
	struct list *list = &task->list;

	list->prev->next = list->next;
	list->next->prev = list->prev;
}

/*
 * get task from queue;
 */
struct task *get_task_from_queue(struct list *head)
{
	struct task *task = NULL;

	if (head->next != head) {
		task = (struct task *)head->next;
		delete_task_from_queue(task);
	}

	return task;
}

/*
 * core thread, check work_queue, 
 * if not full, get task from wait_queue into work_queue;
 */
void *core_thread_exec(void *argv)
{
	while (1) {
		if (pool->free != 0) {

			struct task *task;
			
			task = get_task_from_queue(&pool->wait_queue);
			if (task == NULL)
				continue;

			insert_task_to_queue(task, &(pool->work_queue));	

			sub_thread_info_change(task);		
		}
	}	
}

/*
 * thread_pool;
 */

int thread_pool_init(int num)
{
	int i;
	
	// init thread pool
	pool = (struct thread_pool *)malloc(sizeof(struct thread_pool));
	memset(pool, 0, sizeof(struct thread_pool));	

	pool->count = num;
	pool->free = num;

	pool->work_queue.next = &pool->work_queue;
	pool->work_queue.prev = &pool->work_queue;

	pool->wait_queue.next = &pool->wait_queue;
	pool->wait_queue.prev = &pool->wait_queue;

	sub_thread = (pthread_t *)malloc(pool->count * sizeof(pthread_t));
	if (sub_thread == NULL) {
		return -1;
	}
	memset(sub_thread, 0, pool->count * sizeof(pthread_t));

	thread_info = (struct thread_info *)malloc(pool->count * sizeof(struct thread_info));
	if (thread_info == NULL) {
		return -1;
	}
	memset(thread_info, 0, pool->count * sizeof(struct thread_info));


	// create core thread
	pthread_create(&core_pthread, NULL, core_thread_exec, NULL);


	for (i = 0; i < pool->count; i++) {
		pthread_mutex_init(&thread_info[i].mutex, NULL);
		pthread_create(&sub_thread[i], NULL, sub_thread_exec, &thread_info[i]);
	}

	return 0;
}

/*
 * create sub task;
 */
struct task *create_sub_task(char *name, int (*func)(void *), void *argv)
{
	struct task *task;
	
	task = (struct task *)malloc(sizeof(struct task));
	memset(task, 0, sizeof(struct task));	
	
	task->name = name;
	task->func = func;
	task->argv = argv;

	insert_task_to_queue(task, &pool->wait_queue);

	return task;
}

int show_sub_task(struct list *head)
{
	struct list *list = head->next;

	while (list != head) {
		struct task *task = (struct task *)list;
		
		printf("%s.\n", (char *)(task->name));
		list = list->next;
	}

	return 0;
}

