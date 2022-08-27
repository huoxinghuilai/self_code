#include "mm.h"

#define RUN 0
#define READY 1
#define PEND 2

struct regs {
    int pc;
    int lr;
    int sp;
};

struct task {
    int id;
    char name[10];
	
    int prio;
    int time;
    int status;
    
    struct regs *regs;
    void *stack;
    
    struct task *children;
    struct task *layer;
    struct task *parent;

    struct task *prev;
    struct task *next;

	struct virt_page page_list;
	struct virt_page *reserve;
};

static unsigned int count_task;
static struct task *init_task;
static struct task *current_task;
static struct task *head_task;

int init_boot_task(void);
struct task *create_task(void);
int show_task(void);
int set_task_prio_and_time(struct task *p);
