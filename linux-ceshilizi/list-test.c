#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/slab.h>
#include<linux/list.h>

MODULE_LICENSE("GPL");

#define N 10
struct numlist{
int num;
struct list_head list;
};

struct numlist numhead;

static int __init doublelist_init(void){//构建双链表
struct numlist *listnode;
struct list_head *pos;
struct numlist *p;
int i;

printk("doublelist id starting...\n");
INIT_LIST_HEAD(&(numhead.list));//初始化表头节点

for(i=0;i<N;i++){//建立节点，并把节点连接起来
listnode=(struct numlist *)kmalloc(sizeof(struct numlist),GFP_KERNEL);//分配空间，后边的参数是指内核函数可以重新装载
listnode->num=i+1;
list_add_tail(&(listnode->list),&(numhead.list));//因为numlist不是指针类型，所以只能用list这一指针来连接
printk("node %d has added to the doublelist..\n",i+1);
}

i=1;
list_for_each(pos,&numhead.list){//查找每个节点
p=list_entry(pos,struct numlist, list);//宏定义
printk("node %d's data: %d\n",i,p->num);
i++;
}
return 0;
}

static void __exit doublelist_exit(void){//删除双链表
struct list_head *pos,*n;
struct numlist *p;
int i;

i=1;
list_for_each_safe(pos,n,&(numhead.list)){
list_del(pos);
p=list_entry(pos,struct numlist,list);
kfree(p);//释放节点
printk("node %d has removed from the doublelist...\n",i++);
}
printk("doublelist is exiting..\n");
}

module_init(doublelist_init);
module_exit(doublelist_exit);





