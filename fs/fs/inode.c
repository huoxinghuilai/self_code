#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "dir.h"
#include "file.h"
#include "inode.h"
#include "fs_type.h"

struct inode *make_inode_for_dentry_file(void *param, int type)
{
    struct inode *inode = NULL;
    struct dentry *dentry = NULL;
    struct file *file = NULL;

    inode = (struct inode *)malloc(sizeof(struct inode));
    memset(inode, 0, sizeof(struct inode));

    // 根据类型，创建对应的目录节点或是文件节点
    if (type & DIR_TYPE) {
        dentry = (struct dentry *)param;
        dentry->inode = inode;
        inode->dentry = dentry;

        /*
         * 根目录无父目录，文件系统类型直接赋予
         * 目录为非根目录时，文件系统默认与父目录保持一致
         */
        if (dentry == &root_dentry) {
            inode->fs_type = &root_fs_type;
        } else {
            inode->fs_type = dentry->parent_dentry->inode->fs_type;
        }

        inode->type |= DIR_TYPE;
    }

    if (type & FILE_TYPE) {
        file = (struct file *)param;
        file->inode = inode;
        inode->file = file;

        // 文件系统类型默认与父目录保持一致
        inode->fs_type = file->parent_dentry->inode->fs_type;
        inode->type |= FILE_TYPE;
    }
}