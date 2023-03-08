#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "dir.h"
#include "file.h"
#include "inode.h"

void insert_file_to_list(struct file **head, struct file *file)
{
    if (*head == NULL) {
        *head = file;
    } else {
        file->next = (*head)->next;
        (*head)->next = file;   
    }
}

struct file *add_new_file_to_list(struct dentry *dentry, char *file_name, int type)
{
    struct file *file;
    int length_path = 0, length_name = 0;

    file = (struct file *)malloc(sizeof(struct file));
    
    file->parent_dentry = dentry;

    file->name = (char *)malloc(strlen(file_name));
    memset(file->name, 0, strlen(file_name));
    memcpy(file->name, &file_name[1], strlen(file_name) - 1);

    length_path = strlen(dentry->path);
    length_name = strlen(file_name);
    file->path = (char *)malloc(length_path + length_name + 2);
    memset(file->path, 0, length_path + length_name + 2);
    strcpy(file->path, dentry->path);

    if ((dentry->path[length_path - 1]) != '/') {
        strcat(file->path, "/");
    }

    strcat(file->path, file->name);

#if DEBUG_FS
    printf("file_name: %s file_path: %s\n",file->name, file->path);
#endif

    insert_file_to_list(&dentry->file_head, file);
    make_inode_for_dentry_file(file, type);

    return file;
}

struct file *look_up_file_by_path(struct dentry *dentry, char *file_name, int flags, int type)
{
    struct file *file_tmp;

    file_tmp = dentry->file_head;

    while (file_tmp) {
        if (!strcmp(file_tmp->name, &file_name[1])) {
            printf("file %s has been create.\n", file_name);
            return NULL;
        }

        file_tmp = file_tmp->next;
    }

    if (flags & O_CREATE) {
        return add_new_file_to_list(dentry, file_name, type);
    }
}

