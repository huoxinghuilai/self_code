#include "common.h"
#include "mem.h"
#include "task.h"

void *sub_task(void *str)
{
    print_uart0((char *)str);
}

void start_kernel(void)
{
    print_uart0("Hello, OS kernel!\n");

    char *addr = 0;
    char *str = "How Are you?\n";

    vmm_init();
    task_structure_init();

    addr = vmm_alloc(128);
    _memcpy(addr, str, _strlen(str));
    print_uart0(addr);
    // vmm_free(addr);

    create_task("sub task\n", sub_task)->call_back("this is sub task.\n");
}