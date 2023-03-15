#ifndef __TASK_H
#define __TASK_H

struct task {
    unsigned long id;
    char name[10];

    struct vmm *vmm_list;

    struct task *parent;
    struct task *children;

    struct task *prev;
    struct task *next;

    void *(*call_back)(void *);
};

static unsigned int count_task;
static struct task init_task;
extern struct task *current_task;

int task_structure_init(void);
struct task *get_current_task(void);
struct task *create_task(char *,void *(*func)(void *));

#endif