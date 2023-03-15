#ifndef __MEM_H
#define __MEM_H

struct virt_page {
    unsigned int index;
    void *virt_addr;

    int status;
    int flags;

    struct virt_page *next;
    struct virt_page *prev;
};

struct vmm {
    int status;
    void *addr;
    struct virt_page *page_list;

    struct vmm *next;
    struct vmm *prev;
};

int vmm_init(void);
void *vmm_alloc(unsigned long);
int vmm_free(void *);

#endif