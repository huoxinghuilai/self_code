struct vmm;

struct virt_page {
    unsigned int index; 
    void *virt_addr;
    unsigned int flags;
    struct virt_page *next;
    struct virt_page *prev;
    struct vmm *owner;
};

struct vmm {
    struct virt_page page_list;
};

int vmm_init(void);
void *vmm_alloc(unsigned int size);
