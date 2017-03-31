//tail /var/log/messages
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/miscdevice.h>

#define LEDS_MAJOR 255
#define DEVICE_NAME "fist_miscdev"

static int first_miscdev_open(struct inode *pinode,struct file *pfile){
printk(KERN_EMERG"Linux miscdevice:%s is call\r\n",_FUNCTION_);
//本代码仅作入门说明驱动框架，暂时不实现其中的代码，后续的章节中会实现
return 0;
}

static int first_miscdev_ioctl(
struct inode *inode,
struct file *file,
unsigned int cmd,
unsigned long arg){
return 0;
}

size_t first_miscdev_read(struct file *filp,char _user *buf,size_t count,loff_t *offset){
printk(KERN_EMERG"Linux miscdevice:%s is call\r\n",_FUNCTION_);
return count;
}

size_t first_miscdev_write(struct file *filp,const char _user *buf,size_t count,loff_t *offset){
printk(KERN_EMERG"Linux miscdevice:%s is call\r\n",_FUNCTION_);
return count;
}

loff_t first_miscdev_llseek(struct file *filp,loff_t loff,int origin){
printk(KERN_EMERG"Linux miscdevice:%s is call\r\n",_FUNCTION_);
printk(KERN_EMERG"loff:%ld;origin:%d\r\n",(long)loff,origin);
return loff;
}

int first_miscdev_release(struct inode*inode,struct file *file){
printk(KERN_EMERG"Linux miscdevice:%s is call\r\n",_FUNCTION_);
return 0;
}

static struct file_operations dev_fops={
.owner=THIS_MODULE,
.ioctl=first_miscdev_ioctl,
.open=first_miscdev_open,
.read=first_miscdev_read,
.write=first_miscdev_write,
.release=first_miscdev_release,
.llseek=first_miscdev_llseek,
};

static struct miscdevice misc={
.minor=LEDS_MAJOR,
.name=DEVICE_NAME,
.fops=&dev_fops,
};

static int __init first_miscdev_init(void){
int ret;
ret=misc_register(&misc);
if(ret<0)
printk(KERN_EMERG DEVICE_NAME"\t err\r\n");
printk(KERN_EMERG DEVICE_NAME"\t inintialized\n");
return ret;
}

static void __exit first_miscdev_exit(void){
misc_deregister(&misc);
printk(KERN_EMERG"Goodbye,cruel world!priority=0\n");
}

module_init(first_miscdev_init);
module_exit(first_miscdev_exit);
MODULE_LISENCE("GPL");