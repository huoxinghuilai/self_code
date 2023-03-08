#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "dir.h"
#include "file.h"
#include "fs_type.h"
#include "inode.h"
#include "xfs/xfs.h"

#define NO_USED 0x0
#define NOW_USEING 0x1

struct file_desc {
    int status;
    int fd;
    struct inode *inode;
};

static struct file_desc file_desc[256];

struct inode *parse_path_for_inode(char *path, int flags)
{
    char *str = path;
    int pos_last = 0, pos = 0, length = 0;
    char *dentry_name = NULL;
    struct dentry *dentry = NULL;
    struct file *file = NULL;

    // 目前暂不支持相对路径搜索文件
    if (*path != '/') {
        printf("暂不支持相对路径。\n");
        return NULL;
    }

    while (*str) {
        if (*str == '/') {
            length = pos - pos_last;
            if (length == 0) {      // 处理根目录
                length = 1;
            }

            dentry_name = (char *)malloc(length + 1);
            memset(dentry_name, 0, length + 1);
            memcpy(dentry_name, &path[pos_last], length);

#if DEBUG_FS
            printf("menu's name: %s.\n", dentry_name);
#endif

            look_up_dentry_by_path(&dentry, dentry_name, flags, DIR_TYPE);
            free(dentry_name);
            pos_last = pos;
        }

        pos++;
        str++;
    }

    if (path[pos_last + 1] != '\0') {
#if DEBUG_FS
        printf("file's name: %s\n", &path[pos_last]);
#endif
        file = look_up_file_by_path(dentry, &path[pos_last], flags, FILE_TYPE);
    }

    if (file) {
        return file->inode;
    } else {
        return;
    } 
}

int get_unused_fd(struct inode *node)
{
    struct file_desc *tmp = file_desc;
    int i = 0;

    while (i < 256) {
        if (tmp[i].status == NO_USED) {
            tmp[i].status = NOW_USEING;
            tmp[i].inode = node;
            tmp[i].fd = i;
            return tmp[i].fd;
        }
        i++;
    } 

    return -1;
}

/*
 * open 接口
 */
int open_lz(char *path, int flags)
{
    struct inode *node = NULL;
    int fd = -1;

#if DEBUG_FS
    printf("=================open operation===============\n");
#endif

    if (!path) {
        printf("文件路径不允许为空。\n");
        return -1;
    }

    /* 解析文件路径，获取 inode 节点 */
    node = parse_path_for_inode(path, flags);
    if (!node) {
        return -1;
    }

#if DEBUG_FS
    printf("the node of %s has been found.\n", node->file->path);
#endif

    fd = get_unused_fd(node);
    if (fd < 0) {
        return -1;
    }

    return fd;
}

int main(int argc, char *argv[])
{
    int fd = -1;

    // 初始根目录和根文件系统
    fs_type_init();
    xfs_init();
    dentry_init();

    // 测试创建文件
    fd = open_lz("/var/tmp/log.txt", O_CREATE);
    printf("fd: %d\n", fd);

    // 测试创建同目录重命名文件
    fd = open_lz("/var/tmp/log.txt", O_CREATE);
    printf("fd: %d\n", fd);

    // 测试创建目录
    fd = open_lz("/var/usr/", O_CREATE);
    printf("fd: %d\n", fd);

    // 测试不同目录重命名文件
    fd = open_lz("/var/usr/log.txt", O_CREATE);
    printf("fd: %d\n", fd);
    mount_fs_type_to_inode(&xfs, file_desc[fd].inode);   

    show_dentry_and_file(&root_dentry); 
};