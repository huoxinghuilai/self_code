#ifndef __DIR_H
#define __DIR_H

struct dentry {
    char *name;
    char *path;
    struct dentry *next;    // 兄弟连接节点
    struct dentry *child;   // 父子链接节点
    struct dentry *parent_dentry;   // 父目录

    struct file *file_head; // 目录文件链接节点
    struct inode *inode;
};

extern struct dentry root_dentry;

void dentry_init(void);
void look_up_dentry_by_path(struct dentry **, char *, int, int);
#endif
