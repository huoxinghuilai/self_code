#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>

static int irq;
static char *interface;
static int count=0;

module_param(interface,charp,0644);
module_param(irq,int,0644);

static irqreturn_t intr_handle(int irq,void *dev_id){

static long interval=0;

if(count==0)
interval=jiffies;

interval=jiffies-interval; //计算两个中断之间得见个，时间单位为节拍
printk("the interval between two interrupts is %ld\n",interval);
interval=jiffies;
count++;

return IRQ_NONE;
}

static int __init intr_init(){
if(request_irq(irq,&intr_handle,IRQF_SHARED,interface,&irq)){
printk(KERN_ERR "fails to register IRQ %d\n",irq);
return -EIO;
}
printk("%s request on IRQ %d succeeded\n",interface,irq);
return 0;
}

static void __exit intr_exit(){
printk("the %d interrupts happened on irq %d",count,irq);
free_irq(irq,&irq);
printk("freeing IRQ %d\n",irq);
return ;
}

module_init(intr_init);
module_exit(intr_exit);
MODULE_LICENSE("GPL");
 
