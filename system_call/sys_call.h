//定义系统调用函数
int sys_exit();
int sys_fork();

//定义系统调用表
struct syscall_table{
int (*func)(void);
};
struct syscall_table sys[2];

//实现exit函数
int sys_exit(){
printf("系统调用exit\n");
return 0;
}

//实现fork函数
int sys_fork(){
printf("系统调用fork\n");
return 1;
}

//定义软中断，用来模拟int &80
int softintr(int ax){
if(ax>=0 && ax<2){
ax=sys[ax].func();··
return ax;
}
else
return -1;
}

//定义系统调用号
#define nr_exit 0
#define nr_fork 1

//定义变量ax，用来模拟通用寄存器ax
int ax=0;

//宏定义系统调用接口函数
#define systemcall(type,name,nr_name) \
type name(){ \ 
ax=nr_name; \
ax=softintr(ax); \
return ax; \
}
