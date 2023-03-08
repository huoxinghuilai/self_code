#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dir.h"
#include "inode.h"
#include "file.h"
#include "fs_type.h"

struct fs_type root_fs_type;
const char *root_fs = "root_fs";

int fs_type_init(void)
{
    memset(&root_fs_type, 0, sizeof(struct fs_type));

    root_fs_type.name = (char *)malloc(strlen(root_fs) + 1);
    memcpy(root_fs_type.name, root_fs, strlen(root_fs));

    return 0;
}

int register_fs_type(struct fs_type *fs)
{
    fs->next = root_fs_type.next;
    root_fs_type.next = fs->next;
}

int mount_fs_type_to_inode(struct fs_type *fs, struct inode *node)
{
    if (node->fs_type != fs)
        node->fs_type = fs;

    return 0;
}