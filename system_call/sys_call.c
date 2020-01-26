#include<stdio.h>
#include"sys.h"

//定义了两个内联的系统调用函数
static inline systemcall(int,fork,nr_fork)
static inline systemcall(int,exit,nr_exit)

int main(){
if(fork()==1)
printf("fork成功\n");
else
printf("fork失败\n");
if(exit()==0)
printf("exit成功\n");
else
printf("exit失败\n");
}
