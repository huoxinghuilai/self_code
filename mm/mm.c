#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VMM_SIZE  4096  // 假设虚拟空间占 4KB
#define PAGE_SIZE 64    // 假设页大小为 64 字节
#define VMM_PAGE_NUM (VMM_SIZE / PAGE_SIZE / 8)

char page_map[VMM_PAGE_NUM];
void *mm_addr;

struct virt_page {
    void *virt_addr;
    unsigned int flags;
    struct virt_page *next;
    struct virt_page *prev;
};

struct virt_page page_head;

void *vmm_alloc(unsigned int size)
{
    int nr, i, j;
    void *addr;

    nr = (size % PAGE_SIZE) ? (size / PAGE_SIZE + 1) : (size / PAGE_SIZE);
    printf("alloc %d page\n", nr);

    for (j = 0; j < VMM_PAGE_NUM; j++) {
        printf("page_map[%d]: %x\n", j, page_map[j]);

        for (i = 0; i < 8; i++) {
            printf("%x\n", 1 << i);

            if ((page_map[j] & (1 << i)) == 0) {
                printf("has free page is %d(index)\n", j * 8 + i);

                struct virt_page page;

                page.virt_addr = (j * 8 + i) * 64 + mm_addr;
                addr = page.virt_addr;

                page.next = &page_head;

                page.prev = page_head.prev;
                page_head.prev->next = &page;
                page_head.prev = &page;

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

    return 0;
}
