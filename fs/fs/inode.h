#ifndef __INODE_H
#define __INODE_H

struct inode {
    struct fs_type *fs_type;
    struct file *file;
    struct dentry *dentry;
    int type;
};

struct inode *make_inode_for_dentry_file(void *, int);
#endif