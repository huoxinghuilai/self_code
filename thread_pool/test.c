#include <stdio.h>

#include "thread_pool.h"

int sub_func(void *argv)
{
	int i = *(int *)argv;

	printf("%s %d %d\n", __func__, __LINE__, i);

	return 0;
}

int main(int argc, char *argv[])
{
	int num = 10;
	int inc_1 = 10, inc_2 = 20, inc_3 = 30;

	thread_pool_init(num);

	create_sub_task("thread_1", sub_func, (void *)&inc_1);
	create_sub_task("thread_2", sub_func, (void *)&inc_2);
	create_sub_task("thread_3", sub_func, (void *)&inc_3);
	create_sub_task("thread_4", sub_func, (void *)&inc_1);
	create_sub_task("thread_5", sub_func, (void *)&inc_2);
	create_sub_task("thread_6", sub_func, (void *)&inc_3);
	create_sub_task("thread_7", sub_func, (void *)&inc_1);
	create_sub_task("thread_8", sub_func, (void *)&inc_2);
	create_sub_task("thread_9", sub_func, (void *)&inc_3);
	create_sub_task("thread_10", sub_func, (void *)&inc_1);
	create_sub_task("thread_12", sub_func, (void *)&inc_2);
	create_sub_task("thread_13", sub_func, (void *)&inc_3);

	show_sub_task(&(pool->wait_queue));

	pthread_join(core_pthread, NULL);

	return 0;
}

