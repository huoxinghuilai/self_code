#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sched.h"
#include "task.h"
//#include "mm.h"

int main(int argc, char *argv[])
{
    int i;

	vmm_init();



	init_boot_task();

    create_ready_queue();
    create_wait_queue();

    for (i = 0; i < 5; i++) {
        create_task();
    }

    show_task();
/*
    while (1) {
		if (sched_task())
			break;
	}
*/
	return 0;
}
