#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VMM_SIZE  4096  // 假设虚拟空间占 4KB
#define PAGE_SIZE 64    // 假设页大小为 64 字节
#define PAGE_OFFSET 6
#define VMM_PAGE (VMM_SIZE / PAGE_SIZE)
#define VMM_PAGE_NUM (VMM_PAGE / 8)

char page_map[VMM_PAGE_NUM];
void *mm_addr;

struct virt_page {
    void *virt_addr;
    unsigned int flags;
    struct virt_page *next;
    struct virt_page *prev;
};

static struct virt_page page_head;
static struct virt_page page_global[VMM_PAGE];

void vmm_free(void *addr)
{
    struct virt_page *tmp = page_head.next;
    unsigned long addr1 = (unsigned long)addr;
    int index, index1, index2;

    while (tmp != &page_head) {
        printf("%x %x\n", tmp, &page_head);
        printf("%x %x\n", tmp->virt_addr, addr);

        if (tmp->virt_addr == addr) {
            index = addr1 / PAGE_SIZE;
            index1 = index / 8;
            index2 = index % 8;

            page_map[index1] &= ~(1 << index2);
            printf("page_map[%d]: %x\n", index1, page_map[index1]);
            break;
        }

        tmp = tmp->next;
    }

    printf("index: %d index1: %d index2: %d\n", index, index1, index2);

    return;
}

void *vmm_alloc(unsigned int size)
{
    int nr, i, j;
    void *addr;
    int first = 0;
    struct virt_page *page;

    nr = (size % PAGE_SIZE) ? (size / PAGE_SIZE + 1) : (size / PAGE_SIZE);
    printf("alloc %d page\n", nr);

    for (j = 0; j < VMM_PAGE_NUM; j++) {
        printf("page_map[%d]: %x\n", j, page_map[j]);

        for (i = 0; i < 8; i++) {
            printf("%x\n", 1 << i);

            if ((page_map[j] & (1 << i)) == 0) {
                printf("has free page is %d(index)\n", j * 8 + i);

                page = &page_global[j * 8 + i];
                printf("page: %x\n", page);

                page->virt_addr = (j * 8 + i) * 64 + mm_addr;
                printf("page->virt_addr: %x\n", page->virt_addr);
                if (!first) {
                    addr = page->virt_addr;
                    first = 1;
                }

                page->next = &page_head;
                page->prev = page_head.prev;
                page_head.prev->next = page;
                page_head.prev = page;

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

    return addr;
}

int vmm_page_init(void)
{
    memset(page_map, 0, sizeof(VMM_PAGE_NUM));

    page_head.next = &page_head;
    page_head.prev = &page_head;

    return 0;
}

int vmm_init(void)
{
    vmm_page_init();

    return 0;
}

int main(int argc, char argv[])
{
    void *addr;

    vmm_init();

    addr = vmm_alloc(234);
    printf("addr: %x\n", addr);

    addr = vmm_alloc(345);
    printf("addr: %x\n", addr);

    vmm_free(addr);

    return 0;
}
