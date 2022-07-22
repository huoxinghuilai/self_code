#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 64
#define MM_SIZE 4096
#define ZONE_NUM 3

enum zone_type{
    Low = 0;
    Normal;
    High;
};

unsigned int zone_range[] = {
    [Low] = 512,
    [Normal] = 2560,
    [High] = 1024,
};

struct mm_zone {
    unsigned int start;
    unsigned int end;
    unsigned int size;
    int type;
    
    struct list_node list; //zone域链表节点
    struct list_head page_list; //每组zone域中都存在一组关联的页
};

struct page {
    unsigned int start;
    unsigned int end;
    unsigned int size;
    unsigned int flags;
    struct mm_zone zone;
};

struct list_head zone_list;

unsigned int kernel_args = 128;

unsigned int mm_alloc(unsigned int size, int type)
{
    struct page p;
    
    while(size > 0) { // 页管理模式下，需将已占用的页进行标记，避免被使用
        switch (type) {
            case Low:
                break;
            case Normal:
                p.zone = mm_zone[Normal];
                p.start = mm_zone[Normal].start;
                while (mm_check_used(p.start))
                    p.start += PAGE_SIZE;
                break;
            case High:
                break;
        }
        
        p.size = PAGE_SIZE;
        p.end = page->start + page->size - 1;
        p.flag = KERNEL_ARGS | KERNEL_USED;
        
        size = size - page->size;
        
        list_add(p.list_node, p.zone.page_list);
    }
}

int mm_init(void)
{
    unsigned int addr;
    struct mm_zone *zone;
    unsigned int zone_size;
    
    addr = (char *)malloc(MM_SIZE);    // 假设该空间为物理内存空间
    
    zone_size = sizeof(struct mm_zone);
    
    for (i = 0; i < ZONE_NUM; i++) {
        zone = (struct mm_zone *)(i * zone_size);
        
        zone->type = i;
        zone->start = i * zone_size;
        zone->size = zone_range[zone->type];
        zone->end = zone->start + zone->size - 1;
        
        list_add(zone->list, zone_list);
    }
    
    mm_alloc(kernel_args);
    
    return 0;
}

int main(int argc, char argv[])
{
    mm_init();
    
    return 0;
}
