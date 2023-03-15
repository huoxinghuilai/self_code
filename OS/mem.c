#include "common.h"
#include "task.h"
#include "mem.h"

#define VMM_SIZE  40960
#define PAGE_SIZE 1024
#define VMM_PAGE_NUM (VMM_SIZE / PAGE_SIZE)
#define VMM_PAGE_BITMAP (VMM_PAGE_NUM / 8)

#define FREE_STATUS 0
#define ALLOC_STATUS 1

char page_map[VMM_PAGE_BITMAP];
static struct virt_page page[VMM_PAGE_NUM];
static struct vmm vmm[VMM_PAGE_NUM];
extern void *mem_addr;

int vmm_free(void *addr)
{
    struct task *current = get_current_task();
    struct vmm *vmm_tmp = current->vmm_list->next;
    struct virt_page *page_tmp = vmm_tmp->page_list->next;

    while (vmm_tmp != current->vmm_list) {
        if (vmm_tmp->addr == addr) {
            goto done;
        }
        vmm_tmp = vmm_tmp->next;
    }

done:
    while (page_tmp != vmm_tmp->page_list) {
        page_tmp->status = FREE_STATUS;
        page_tmp = page_tmp->next;
    }

    vmm_tmp->status = FREE_STATUS;
    addr = 0;
    
    return 0;
}

struct vmm *get_free_vmm(void)
{
    int i = 0;

    for (i; i < VMM_PAGE_NUM; i++) {
        if (vmm[i].status == FREE_STATUS) {
            vmm[i].status = ALLOC_STATUS;
            return &vmm[i];
        }
    }

    return 0;
}

void *vmm_alloc(unsigned long size)
{
    int nr = 0;
    int i = 0;
    int j = 0;
    int first = 0;   
    struct virt_page *page_tmp;
    struct task *current = get_current_task();
    struct vmm *vmm_tmp = get_free_vmm();
    int tmp = 0;

    if (vmm_tmp == 0) {
        print_uart0("vmm alloced failed.\n");
        return 0;
    }

    nr = (size % PAGE_SIZE) ? (size / PAGE_SIZE + 1) : (size / PAGE_SIZE);

    for (i = 0; i < VMM_PAGE_BITMAP; i++) {
        if (page_map[i] == 0xff) {
            continue;
        } else {
            for (j = 0; j < 8; j++) {
                tmp = (int)(page_map[i] & (1 << j));
                if (tmp == FREE_STATUS) {
                    page_tmp = page + (i * 8 + j);
                    page_tmp->index = i * 8 + j;
                    page_tmp->virt_addr = page_tmp->index * PAGE_SIZE + mem_addr;
                    page_tmp->status = ALLOC_STATUS;

                    if (!first) {                   
                        vmm_tmp->addr = page_tmp->virt_addr;
                        first = 1;
                    }

                    page->next = vmm_tmp->page_list;
                    page->prev = vmm_tmp->page_list->prev;
                    vmm_tmp->page_list->prev->next = page;
                    vmm_tmp->page_list->prev = page;

                    page_map[i] = page_map[i]| (1 << j);
                    nr--;
                }

                if (nr == 0)
                    goto done;
            }
        }
    }

    if (nr > 0) {
        print_uart0("no enough free page.\n");
        return 0;
    }

done:
    return vmm_tmp->addr;
}

int vmm_page_init(void)
{
    _memset(page_map, 0, sizeof(char) * VMM_PAGE_BITMAP);
    
    return 0;
}

int vmm_init(void)
{
    vmm_page_init();

    return 0;
}
