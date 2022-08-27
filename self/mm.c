#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mm.h"

#define VMM_SIZE  4096  // 假设虚拟空间占 4KB
#define PAGE_SIZE 64    // 假设页大小为 64 字节
#define PAGE_OFFSET 6
#define VMM_PAGE (VMM_SIZE / PAGE_SIZE)
#define VMM_PAGE_NUM (VMM_PAGE / 8)

//static struct virt_page page_head;
static struct virt_page page_global[VMM_PAGE];
static struct virt_page page_list;
char page_map[VMM_PAGE_NUM];
void *mm_addr;

void vmm_free(void *addr)
{
    unsigned long addr1 = (unsigned long)addr;
    int index, index1, index2;
    struct virt_page *tmp, *page_head;

    index = addr1 / PAGE_SIZE;
    tmp = &page_global[index];
    page_head = &tmp->owner->page_list;

    while (tmp != page_head) {
	printf("%x \n", tmp);
	printf("%x %x\n", tmp->virt_addr, addr);

//	if (tmp->virt_addr == addr) {
	    index1 = tmp->index / 8;
	    index2 = tmp->index % 8;

	    page_map[index1] &= ~(1 << index2);
	    printf("page_map[%d]: %8x\n", index1, page_map[index1]);
//	    break;
//        }

        tmp = tmp->next; 
    }

//    printf("index: %d index1: %d index2: %d\n", index, index1, index2);

    return;
}

// void vmm_area_init(struct vmm *area)
// {
//     struct virt_page *page_head;

//     page_head = &area->page_list;

//     page_head->next = page_head;
//     page_head->prev = page_head;

//     return;
// }

/*
 * 申请内存时，默认从可用地址空间开始分配
 */
void *vmm_alloc(unsigned int size)
{
    int nr, i, j;
    void *addr;
    int first_page = 1;
    struct virt_page *page;
    // struct vmm vmm_area;
    // struct virt_page *page_head = &vmm_area.page_list;
    struct virt_page *page_head = &page_list;
	unsigned long *tmp;

    // vmm_area_init(&vmm_area);

    nr = (size % PAGE_SIZE) ? (size / PAGE_SIZE + 1) : (size / PAGE_SIZE);
    printf("alloc %d page\n", nr);

    for (j = 0; j < VMM_PAGE_NUM; j++) {
        for (i = 0; i < 8; i++) {

            if ((page_map[j] & (1 << i)) == 0) {
		        printf("has free page is %d(index)\n", j * 8 + i);

		        page = &page_global[j * 8 + i];
		        page->index = j * 8 + i;
				page->virt_addr = (j * 8 + i) * 64 + mm_addr;
		        printf("page->virt_addr: %x\n", page->virt_addr);

		        if (first_page) {
                    addr = page->virt_addr;
                    first_page = 0;
                }

                page->next = page_head;
                page->prev = page_head->prev;
                page_head->prev->next = page;
                page_head->prev = page;

                // page->owner = &vmm_area;

		        page_map[j] |= 1 << i;
                nr--;
            }

            if (nr == 0)
		break;
        }

        if (nr == 0)
            break;
    }

    if (nr) {
        printf("no enough free page.\n");

        return 0;
    }

	tmp = (unsigned long *)(addr + size - sizeof(void *));
	*tmp = (unsigned long)(&page_list);

    return addr;
}

/*
 * 内存均已页形式管理，因此只对页的使用情况进行初始
 */
int vmm_page_init(void)
{
    memset(page_map, 0, sizeof(VMM_PAGE_NUM));

    page_list.next = &page_list;
    page_list.prev = &page_list;

    return 0;
}

int vmm_init(void)
{
    mm_addr = (void *)malloc(sizeof(4 * 1024));    // 模拟物理内存

    vmm_page_init();
  
    return 0;
}

// int main(int argc, char argv[])
// {
//     void *addr;

//     vmm_init();

//     addr = vmm_alloc(234);
//     printf("addr: %x\n", addr);

//     addr = vmm_alloc(345);
//     printf("addr: %x\n", addr);

//     vmm_free(addr);

//     return 0;
// }
