#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

//结构体
struct list_head {
	struct list_head *next, *prev;
};

//初始化头结点
 void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

//添加结点
 void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

//尾插法
 void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

//删除结点
 void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

//删除结点
 void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

//求出结点的首地址
#ifndef container_of
#define container_of(ptr, type, member) \
    (type *)((char *)(ptr) - (char *) &((type *)0)->member)
#endif

//结点的首地址
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#endif