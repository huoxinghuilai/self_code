#ifndef __FS_TYPE_H
#define __FS_TYPE_H

struct fs_operations {
    unsigned long (*fs_read)(int, char *, int);
    unsigned long (*fs_write)(int, char *, int);
};

struct fs_type {
    char *name;
    struct fs_operations *ops;
    struct fs_type *next;
};

extern struct fs_type root_fs_type;
int fs_type_init(void);
int register_fs_type(struct fs_type *);
int mount_fs_type_to_inode(struct fs_type *, struct inode *);
#endif