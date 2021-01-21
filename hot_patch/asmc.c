#include <stdio.h>
#include <stdlib.h>

struct pt_regs {
	unsigned long regs[32];
};

int change_func(void)
{
	printf("change_func!\n");
}

int ftrace_call_change(unsigned long ip, unsigned long parent_ip, void *tmp, struct pt_regs *regs)
{
	int (*func)(void);
	func = change_func;

	printf("from sub_func to ftrace_call_change!\n");
	printf("%lx %lx %lx %lx\n", ip, parent_ip, tmp, regs);

	regs->regs[0] = func; 
}

int sub_func()
{

	asm volatile (
		".set noat\n\t"
		"move $AT, $ra\n\t"
		"jal ftrace_caller\n\t"
	);

	printf("sub_func!\n");	
	return 0;
}

int main(int argc, char *argv[])
{
	sub_func();
	printf("success!\n");
	return 0;
}
