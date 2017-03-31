#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/list.h>
#include<linux/spinlock.h>
#include<linux/kdev_t.h>

#define SUPER_BLOCKS_ADDRESS 0xffffffff813c4aa0
#define SB_LOCK_ADDRESS 0xffffffff81fe3fa0

static int __init my_init(void){
struct super_block *sb;
struct list_head *pos;
struct list_head *linode;
struct inode *pinode;
unsigned long long count=0;
printk("\nprint some fileds of super_blocks:\n");
spin_lock((spinlock_t *)SB_LOCK_ADDRESS); //jiasuo
list_for_each(pos,(struct list_head *)SUPER_BLOCKS_ADDRESS){
sb=list_entry(pos,struct super_block,s_list);
printk("dev_t:%d:%d ",MAJOR(sb->s_dev),MINOR(sb->s_dev));
printk("file_type name:%s\n",sb->s_type->name);
list_for_each(linode,&sb->s_inodes){
pinode=list_entry(pos,struct inode,i_sb_list);
count++;
printk("%lu\t",pinode->i_ino);
}
}
spin_unlock((spinlock_t *)SB_LOCK_ADDRESS);
printk("the number of inodes:%llu\n",sizeof(struct inode)*count);
return 0;
}

static int __exit my_exit(void){
printk("unloading...\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");

