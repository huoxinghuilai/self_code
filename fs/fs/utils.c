#include <stdio.h>

#include "dir.h"
#include "file.h"
#include "inode.h"
#include "fs_type.h"

void show_dentry_and_file(void *param)
{
    struct dentry *dentry = (struct dentry *)param;
    struct dentry *tmp;

    printf("%s %s\n", dentry->path, dentry->inode->fs_type->name);

    if (dentry->child) {
        show_dentry_and_file(dentry->child);
    }

    if (dentry->next) {
        show_dentry_and_file(dentry->next);
    }

    /*
     * 打印目录中独立的文件
     */
    if (dentry->file_head) {
        struct file *file = dentry->file_head;
        while (file) {
            printf("%s %s\n", file->path, file->inode->fs_type->name);
            file = file->next;
        }
    }

    return;
}