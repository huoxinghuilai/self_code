#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "sched.h"
//#include "mm.h"

#define TASK_PRIO 5
#define TASK_TIME 10

// 设置任务优先级和时间片
int set_task_prio_and_time(struct task *p)
{
	p->prio = rand() % TASK_PRIO;
	p->time = TASK_TIME - (p->prio);
}

int create_task_vmm(struct task *p)
{
	struct virt_page *page_head = &p->page_list;
	
	page_head->next = p->reserve->next;
	page_head->prev = p->reserve->prev;

	p->reserve->prev->next = page_head;
	p->reserve->next->prev = page_head;

	memset(p->reserve, 0, sizeof(void *));

	return 0;
}

// 初始任务
int init_boot_task(void)
{
//        init_task = (struct task *)malloc(sizeof(struct task));
		printf("task size: %d\n", sizeof(struct task));
		init_task = (struct task *)vmm_alloc(sizeof(struct task));
		if (!init_task) {
			printf("init task malloc failed.\n");
		}

		create_task_vmm(init_task);	

        init_task->id = count_task++;
        memcpy(init_task->name, "init", strlen("init"));

        set_task_prio_and_time(init_task);

        init_task->regs = (void *)vmm_alloc(sizeof(struct regs));
        memset(init_task->regs, 0, sizeof(struct regs));

        init_task->stack = (void *)vmm_alloc(64);
        memset(init_task->stack, 0, 64);

        init_task->children = NULL;
        init_task->layer = NULL;
        init_task->parent = NULL;

        init_task->prev = NULL;
        init_task->next = NULL;

        current_task = init_task;

        return 0;
}

struct task *get_current_task(void)
{
        return current_task;
}

// 为当前进程添加父子，兄弟关系（头插形式）
void add_to_parent_sub(struct task *task, struct task *parent)
{
        task->layer = parent->children;
        parent->children = task;

        return;
}

struct task *create_task(void)
{
        struct task *new;
        struct task *cur;

        new = (struct task *)vmm_alloc(sizeof(struct task));
        if (!new) {
                return NULL;
        }

	create_task_vmm(init_task);

        new->id = count_task++;
	printf("new->id: %d\n", new->id);

        sprintf(new->name, "task_%d", new->id);
	printf("new->name: %s\n", new->name);

        set_task_prio_and_time(new);
printf("1\n");
        cur = get_current_task();
printf("2\n");
        if (cur) {
                new->parent = cur;
                add_to_parent_sub(new, new->parent);
        } else {
                printf("不允许创建无根进程（init_task 进程除外）.\n");
                free(new);

                return NULL;
        }
printf("3\n");        
        new->status = READY;
        add_to_queue(ready_queue, new);
printf("4\n");
        return new;
}

int show_task(void)
{
        struct task *p;

        p = init_task;

        while (p) {
                printf("task[%d]: %s\n", p->id, p->name);

                if (p->children) {
                       p = p->children;
			continue;			
                }

                if (p->layer) {
                        p = p->layer;
                } else {
				if (p->parent)
                        		p = p->parent->layer;
				else
					p = NULL;
                }
        }
}  
