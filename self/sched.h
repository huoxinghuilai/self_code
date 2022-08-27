extern struct task *ready_queue[6];
extern struct task *wait_queue[6];

struct task *add_to_queue(struct task *t[],struct task *p);
int create_ready_queue(void);
int create_wait_queue(void);
int print_ready_queue(void);
int print_wait_queue(void);
int sched_task(void);
