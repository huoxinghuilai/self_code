#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "dir.h"
#include "inode.h"

struct dentry root_dentry;

void insert_dentry_to_list(struct dentry **head, struct dentry *dentry)
{
    if (*head == NULL) {
        *head = dentry;
    } else {
        dentry->next = (*head)->next;
        (*head)->next = dentry;
    }
}

struct dentry *add_new_dentry_to_list(struct dentry *dentry, char *dentry_name)
{
    struct dentry *dentry_new = NULL;
    int length_path = 0, length_name;

    dentry_new = (struct dentry *)malloc(sizeof(struct dentry));
    memset(dentry_new, 0, sizeof(struct dentry));

    dentry_new->parent_dentry = dentry;

    dentry_new->name = (char *)malloc(strlen(dentry_name) + 1);
    memset(dentry_new->name, 0, strlen(dentry_name) + 1);
    memcpy(dentry_new->name, &dentry_name[1], strlen(dentry_name));

    length_path = strlen(dentry->path);
    length_name = strlen(dentry_name);
    dentry_new->path = (char *)malloc(length_path + length_name + 2);
    memset(dentry_new->path, 0, length_path + length_name + 2);
    strcpy(dentry_new->path, dentry->path);

    if ((dentry->path[length_path - 1]) != '/') {
        strcat(dentry_new->path, "/");
    }
    strcat(dentry_new->path, dentry_new->name);

#if DEBUG_FS
    printf("dentry_name: %s dentry_path: %s\n", dentry_new->name, dentry_new->path);
#endif

    insert_dentry_to_list(&dentry->child, dentry_new);

    return dentry_new;
}

void look_up_dentry_by_path(struct dentry **dentry, char *dentry_name, int flags, int type)
{
    struct dentry *dentry_tmp = NULL;
    struct dentry *dentry_new = NULL;
    struct inode *node = NULL;

    if (*dentry == NULL) {
        *dentry = &root_dentry;
        return;
    } else {
        /* 查找子目录
         * 传参子目录首字符为 '/'，实际记录会删除 '/' 字符
         */
        dentry_tmp = (*dentry)->child;
        while (dentry_tmp) {
            if (!memcmp(dentry_tmp->name, &dentry_name[1], strlen(dentry_name - 1))) {
                *dentry = dentry_tmp;
                return;
            }

            dentry_tmp = dentry_tmp->next;
        }
    }

    /* 未找到子目录，根据 flags 选项决定是否创建目录 */
    if (flags & O_CREATE) {
        dentry_new = add_new_dentry_to_list(*dentry, dentry_name);
        make_inode_for_dentry_file(dentry_new, type);
        *dentry = dentry_new;
    }

    return;
}

/*
 * 创建根目录节点
 */
void dentry_init(void)
{
    memset(&root_dentry, 0, sizeof(struct dentry));

    root_dentry.name = (char *)malloc(2);
    strcpy(root_dentry.name, "/");

    root_dentry.path = (char *)malloc(2);
    strcpy(root_dentry.path, "/");

    // 创建根节点（root_inode）
    make_inode_for_dentry_file(&root_dentry, DIR_TYPE);
}