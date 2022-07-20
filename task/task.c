//struct process
struct task;

struct tcb {
	struct task *task;
};

struct task {
	char *name;
	void *regs;
	void *stack;
	
	struct list_head *children;
	struct list_node *layer;
	struct list_node *parent;
};

// 该变量用于记录当前运行的任务
// 在任务切换过程中修改
static struct task *current_task;

struct task *get_current_task(void)
{
	return current_task;
}

int create_task(void)
{
	struct task *new;
	struct task *cur;

	new = (struct task *)kmalloc(sizeof(struct task));
	if (!task) {
		return -ENOMEM;
	}

	cur = get_current_task();
	if (!cur) {
		return -ENOSYS;
	}

	new->parent = cur;
	add_to_parent_child(new->layer, new->parent);

	new->status = READY;

	if (is_need_exec(new))
		exec_task(new);
	else
		add_task_to_ready(new);
}

int exec_task(struct task *task)
{
	struct vma *vma;

	vma = (struct vma *)kmalloc(sizeof(struct vma));

	load_exec(task->exec);

	exec_sched(task);
}
