#ifndef __FILE_H
#define __FILE_H

struct file {
    char *name;
    char *path;

    struct file *next;
    struct dentry *parent_dentry;
    struct inode *inode;
};

struct file *look_up_file_by_path(struct dentry *, char *, int, int);
struct file *add_new_file_to_list(struct dentry *, char *, int);

#endif