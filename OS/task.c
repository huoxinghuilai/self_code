#include "common.h"
#include "mem.h"
#include "task.h"

struct task *current_task = 0;

static int init_boot_task(void)
{
    struct task *task = &init_task;
    if (!task) {
        return -1;
    }

    task->id = count_task++;
    _memcpy(task->name, "init\n", _strlen("init\n"));
    print_uart0(task->name);

    task->vmm_list = 0;

    task->children = 0;
    task->parent = 0;

    task->prev = 0;
    task->next = 0;

    current_task = task;

    return 0;
}

int task_structure_init(void) {
    int ret = 0;

    ret = init_boot_task();
    if (ret == -1) {
        return -1;
    }

    return 0;
}

struct task *get_current_task(void) {
    return current_task;
}

void add_to_parent_sub(struct task *task, struct task *parent)
{
        parent->children = task;
}

struct task *create_task(char *name, void *(*func)(void *))
{
    struct task *new;
    struct task *cur = get_current_task();

    new = (struct task *)vmm_alloc(sizeof(struct task));
    if (!new) {
            return 0;
    }

    new->id = count_task++;
    _memcpy(new->name, name, _strlen(name));
    print_uart0(new->name);
    new->call_back = func;

    if (cur) {
        new->parent = cur;
        add_to_parent_sub(new, new->parent);
    } else {
        print_uart0("错误：进程无父进程.\n");
        vmm_free(new);

        return 0;
    }

    return new;
}