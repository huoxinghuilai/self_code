#define COMM_SIZE 16

struct syscall_buf{
u32 serial;
u32 ts_sec;
u32 ts_micro;
u32 syscall;
u32 status;
pid_t pid;
uid_t uid;
u8 comm[COMM_SIZE];
}

DECLARE_WAIT_QUEUE_HEAD(buffer_wait);

#define AUDIT_BUF_SIZE 100
static struct syscall_buf audit_buf[AUDIT_BUF_SIZE];
static int current_pos=0;
static u32 serial=0;

void syscall_audit(int syscall,int return_status){
struct syscall_buf *ppb_temp;
if(current_pos<AUDIT_BUF_SIZE){
ppb_temp=&audit_buf[curretn_pos];
ppb_temp->serial=serial++;
ppb_temp->ts_sec=xtime.tv_sec;
ppb_temp->ts_micro=xtime.tv_usec;
ppb_temp->syscall=syscall;
ppb_temp->status=return_status;
ppb_temp->pid=current->pid;
ppb_temp->uid=current->uid;
ppb_temp->euid=current->euid;

memcpy(ppb_temp->comm,current->comm,COMM_SIZE);

if(++current_pos==AUDIT_BUF_SIZE*8/10){
printk("IN MODULE_audit:yes,it near full\n");
wake_up_interruptible(&buffer_wait);
}
}

int sys_audit(u8 type,u8 *us_buf,u16 us_buf_size,u8 reset){
int ret=0;
if(!type){
if(__clear_user(us_buf,us_buf_size)){
printk("error:clear_user\n");
return 0;
}
printk("in module_systemcall:starting...\n");
rte=wait_event_interruptible(buffer_wait,current_pos>=AUDIT_BUF_SIZE*8/10);
printk("in module_systemcall:over,current_pos is %d\n",current_pos);
if(__copy_to_user(us_buf,audit_buf,(current_pos)*sizeof(struct syscall_buf))){
printk("error:copy error\n");
return 0;
}
ret=current_pos;
current_pos=0;
}
return ret;
}


