#include<stdio.h>
#include<malloc.h>
#include<unistd.h>

int  bss_var;
int data_var0=1;

int main(int argc,char **argv){
printf("below are addresses of types of process's mem:\n");
printf("Text location:\n");
printf("\tAddress of main(Code Segement):%p\n",main);
printf("__________________________________________\n");
int stack_var0=2;
printf("Stack location:\n");
printf("\tInitial end of stack:%p\n",&stack_var0);
int stack_var1=3;
printf("\tnew end of stack:%p\n",&stack_var1);
printf("__________________________________________\n");
printf("Data location:\n");
printf("\tAddress of data_var(Data Segment):%p\n",&data_var0);
static int data_var1=4;
printf("\tnew end of data_var(Data Segment):%p\n",&data_var1);
printf("__________________________________________\n");
printf("BSS location:\n");
printf("\tAddress of bss_var:%p\n",&bss_var);
printf("__________________________________________\n");
char *b=sbrk((ptrdiff_t)0);
printf("Heap location:\n");
printf("Initial end of heap:%p\n",b);
brk(b+4);
b=sbrk((ptrdiff_t)0);
printf("\tnew end of heap:%p\n",b);
return 0;
}

