#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/mm.h>
#include<linux/sced.h>
#include<linux/cdev.h>
#include<asm/io.h>
#include<asm/system.h>
#include<asm/uaccess.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");

#define MYCDEV_MAJOR 231
#define MYCDEV_SIZE 1024

static int mycdev_open(struct inode *inode,struct file *fp){
return 0;
}

static int mycdev_release(struct inode *inode,struct file *fp){
return 0;
}

static int mycdev_read(struct file *fp,char __user *buf,size_t size,loff_t *pos){
unsigned long p=*pos;
unsigned int count=size;
char kernel_buf[MYCDEV_SIZE]="this is mycdev";
int i;

if(p>=MYCDEV_SIZE)
return -1;
if(count>MYCDEV_SIZE)
count=MYCDEV_SIZE-p;
if(copy_to_user(buf,kernel_buf,count)!=0){
printk("read error!\n");
return -1;
}

printk("reader: %d bytes was read...\n",count);
return count;
}

static ssize_t mycdev_write(struct file *fp,const char __user *buf,size_t size,loff_t *pos){
return size;
}

static const struct file_operations mycdev_fops={
.owner=THIS_MODULE,
.read=mycdev_read,
.write=mycdev_write,
.open=mycdev_open,
.release=mycdev_release,
};

static int __init mycdev_init(void){
int ret;

printk("mycdev module is starting..\n");

ret=register_chrdev(MYCDEV_MAJOR,"my_cdev",&mycdev_fops);
if(ret<0){
printk("register failed..\n");
return 0;
}
else{
printk("register success..\n");
}

return 0;
}

static void __exit mycdev_exit(void){
printk("mycdev module is leaving..\n");
unregister_chrdev(MYCDEV_MAJOR,"my_cdev");
}

module_init(mycdev_init);
module_exit(mycdev_exit);
