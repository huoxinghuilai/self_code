#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READY 1

struct regs {
        int pc;
        int lr;
        int sp;
};

struct task {
        unsigned int id;
        char name[5];
        struct regs *regs;
        void *stack;
        int status;

        struct task *children;
        struct task *layer;
        struct task *parent;

        struct task *prev;
        struct task *next;
};

static unsigned int count_task;
static struct task *first_task;
static struct task *current_task;
static struct task ready;
static struct task pend;

int init_first_task(void)
{
        first_task = (struct task *)malloc(sizeof(struct task));

        memcpy(first_task->name, "init", strlen("init"));

        first_task->regs = (void *)malloc(sizeof(struct regs));
        memset(first_task->regs, 0, sizeof(struct regs));

        first_task->stack = (void *)malloc(64);
        memset(first_task->stack, 0, 64);

        first_task->children = NULL;
        first_task->layer = NULL;
        first_task->parent = NULL;

        first_task->id = count_task++;

        current_task = first_task;

        return 0;
}

struct task *get_current_task(void)
{
        return current_task;
}

int exec_task(struct task *task)
{
}

int exec_sched(struct task *task)
{
}

void add_to_parent_child(struct task *task, struct task *parent)
{
        printf("add_to_parent_child.\n");
        task->layer = parent->children;
        parent->children = task;

        return;
}

void add_task_to_ready(struct task *task)
{
        printf("add_task_to_ready.\n");
        task->next = &ready;
        printf("1\n");
        task->prev = ready.prev;
        printf("2\n");
        ready.prev->next = task;
        printf("3\n");
        ready.prev = task;
        printf("4\n");

        return;
}

struct task *create_task(char *name)
{
        struct task *new;
        struct task *cur;

        new = (struct task *)malloc(sizeof(struct task));
        if (!new) {
                return NULL;
        }
        memcpy(new->name, name, strlen(name));
        printf("new->name: %s\n", new->name);

        new->id = count_task++;

        cur = get_current_task();
        if (!cur) {
                return NULL;
        }

        new->parent = cur;
        add_to_parent_child(new, new->parent);

        new->status = READY;
        add_task_to_ready(new);

        return new;
}

void init_ready_task(struct task *ready)
{
        ready->prev = ready;
        ready->next = ready;

        return;
}

int main(int argc, char *argv[])
{
        struct task *task;
        struct task *tmp;

        init_first_task();
        printf("first task: %s %d\n", first_task->name, first_task->id);

        init_ready_task(&ready);

        task = create_task("task1");
        printf("task1: %x %s %d\n", task, task->name, task->id);

        task = create_task("task2");
        printf("task2: %x %s %d\n", task, task->name, task->id);

        tmp = ready.next;
        while(tmp != &ready) {
                printf("tmp: %x\n", tmp);
                printf("task: %s %d\n", tmp->name, tmp->id);
                tmp = tmp->next;
        }

        task = get_current_task();
        printf("task: %x %x %s %d\n", first_task, task, task->name, task->id);
        if (task->children) {
                tmp = task->children;
                printf("%x\n", task);
                printf("task: %s %d\n", tmp->name, tmp->id);

                if (task->children->layer) {
                        tmp = task->children->layer;
                        printf("task: %s %d\n", tmp->name, tmp->id);
                }
        }

        return 0;
}
