#include <stdio.h>
#include <stdlib.h>

#include "../fs_type.h"

unsigned long xfs_read(int fd, char *buff, int length)
{
    printf("xfs_read.\n");
    return 0;
}

unsigned long xfs_write(int fd, char *buff, int length)
{
    printf("xfs_write.\n");
    return 0;
}

struct fs_operations xfs_ops = {
    .fs_read = xfs_read,
    .fs_write = xfs_write,
};

struct fs_type xfs = {
    .name = "xfs",
    .ops = &xfs_ops,
    .next = NULL,
};

int xfs_init(void)
{
    register_fs_type(&xfs);
}