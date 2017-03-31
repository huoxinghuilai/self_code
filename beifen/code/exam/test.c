#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/sched.h>
#include<linux/sem.h>
#include<linux/list.h>
#include<linux/mm.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void){
struct task_struct *task,*p;
struct list_head *pos;
struct file *file=NULL;

int count=0;
printk(KERN_ALERT "Hello World enter begin:\n");
task=&init_task;
list_for_each(pos,&task->tasks){
list_entry(pos,struct task_struct,tasks);
count++;
printk(KERN_ALERT "%d,%s\n",p->pid,p->comm);
file=gettaskfile(p);
if(file){
printk(KERN_ALERT "%s\n",file->f_dentry->d_name.name);
}
}
printk(KERN_ALERT "the number of process is:%d\n",count);
return 0;
}

static void hello_exit(void){
printk(KERN_ALERT "hello world exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

