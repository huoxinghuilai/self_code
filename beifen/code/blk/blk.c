#include<linux/module.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/errno.h>
#include<linux/mm.h>
#include<linux/sched.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<asm/io.h>
#include<asm/system.h>
#include<asm/uaccess.h>

#define GLOBALMEM_SIZE 4096
#define GLOBALMEM_MAJOR 255

static globalmem_major=GLOBALMEM_MAJOR;
static struct globalmem_dev *globalmem_devp;

struct globalmem_dev{
struct cdev cdev;
unsigned char mem[255];
};
struct globalmem_dev dev;

int globalmem_release(struct inode *inode,struct file *filp){
return 0;
}

int globalmem_open(struct inode *inode,struct file *filp){
filp->private_data=globalmem_devp;
return 0;
}

static ssize_t globalmem_write(struct file *filp,char __user *buf,size_t size,loff_t *ppos){
return size;
}

static ssize_t globalmem_read(struct file *filp,char __user *buf,size_t size, loff_t *ppos){
unsigned long p=*ppos;
unsigned int count =size;
int ret=0;
struct globalmem_dev *dev=filp->private_data;
if(p>=GLOBALMEM_SIZE)
return count ? -ENXIO : 0;
if(count>GLOBALMEM_SIZE-p)
count=GLOBALMEM_SIZE-p;
if(copy_to_user(buf,(void *)(dev->mem+p),count)){
ret=-EFAULT;
}
else{
*ppos+=count;
ret=count;
printk(KERN_INFO "read %d bytes from %d\n",count,p);
}
return ret;
}

static const struct file_operations globalmem_fops={
.owner=THIS_MODULE,
.read=globalmem_read,
.write=globalmem_write,
.open=globalmem_open,
.release=globalmem_release,
};

static void globalmem_setup_cdev(struct globalmem_dev *dev,int index){
int ret;
int devno=MKDEV(globalmem_major,index);
cdev_init(&dev->cdev,&globalmem_fops);
dev->cdev.owner=THIS_MODULE;
dev->cdev.ops=&globalmem_fops;
ret=cdev_add(&dev->cdev,devno,1);
if(ret){
printk("add globalmem error");
}
}

int globalmem_init(void){
int result;
dev_t devno=MKDEV(globalmem_major,0);
if(globalmem_major){
result=register_chrdev_region(devno,1,"globalmem");
}
else{ //动态分配主设备号
result=alloc_chrdev_region(&devno,0,1,"globalmem");
globalmem_major=MAJOR(devno);
}
if(result<0)
return result;
globalmem_devp=kmalloc(sizeof(struct globalmem_dev),GFP_KERNEL);
if(!globalmem_devp){
result=-ENOMEM;
goto fail_malloc;
}
memset(globalmem_devp,0,sizeof(struct globalmem_dev));
globalmem_setup_cdev(globalmem_devp,0);
return 0;
fail_malloc:unregister_chrdev_region(devno,1);
return result;
}

static void __exit globalmem_exit(void){
cdev_del(&(dev.cdev));
kfree(&dev);
unregister_chrdev_region(MKDEV(globalmem_major,0),1);
}

module_init(globalmem_init);
module_exit(globalmem_exit);


