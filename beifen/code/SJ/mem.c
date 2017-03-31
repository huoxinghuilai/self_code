#include<stdio.h>
#include<stdlib.h>

#define PROCESS_NAME_LEN 32
#define MIN_SLICE 10 //最少把该存储区分为10块
#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_MEM_START 0
#define MA_FF 1
#define MA_BF 2
#define MA_WF 3

struct free_block_type{//说明一个块的大小，首地址

int size;
int start_addr;
struct free_block_type *next;
};
struct free_block_type *free_block;

struct allocated_block{//说明被使用的块的大小，首地址以及被哪个编号的程序使用

int pid;;
int size;
int start_addr;
char process_name[PROCESS_NAME_LEN];
struct allocated_block *next;
}
struct allocated_block *allocated_block_head=NULL;

int mem_size=DEFAULT_MEM_SIZE
int ma_algorithm=MA_FF;
static int pid=0;
int flag=0;

int main(){

char choice;
pid=0;

free_block=init_free_block(mem_size);
while(1){

display_meun();
choice=getchar();
switch(choice){

case 1:set_mem_size();
       break;
case 2:set_algorithm();
       flag=1;
       break;
case 3:new_process();
       flag=1;
       break;
case 4:kill_process();
       flag=1;
       break;
case 5:display_mem_usage();
       flag=1;
       break;
case 0:do_exit();
       exit(0);
default:break;
}
}
}

struct free_block_type *init_free_block(int mem_size){

struc free_block_type *fb;
fb=(struc free_block_type *)malloc(struct free_block_type);
if(fb==NULL){
printf("no mem\n");
return NULL;
}
fb->size=mem_size;
fb->start_addr=DEFAULT_MEM_START;
fb->next=NULL;
return fb;
}

void display_menu(){

printf("\n");
printf("1-set memory size (default=%d)\n",DEFAULT_MEM_START);
printf("2-select memory allocation algorithm\n");
printf("3-new process\n");
printf("4-terminate a process\n");
printf("5-display memory usage\n");
printf("0-exit\n");
}

int set_mem_size(){

int size;
if(flag！=0){
printf("cannot set memory again\n");
return 0;
}
printf("total memory size=");
scanf("%d",&size);
if(size>0){
mem_size=size;
free_block->size=mem_size;
}
flag=1;
return 1;
}
}

void set_algorithm(){

int algorithm;
printf("\t1-first fit\n");
printf("\t2-best fit\n");
printf("\t3-worst fit\n");
scanf("%d",&algorithm);
if(algorithm>=1 && algorithm<=3)
ma_algorithm=algorithm;
rearrange(ma_algorithm);
}

void rearrange(int algorithm){

switch(algorithm){
case MA_FF:rearrange_FF();break;
case MA_BF:rearrange_BF();break;
case MA_WF:rearrange_WF();break;
}
}

rearrange_FF(){

int i=0,t=0;
struct free_block_type *p,*q;
q=p=free_block;

q->start_addr+=t
do{
t=rand();
}while(t<10 && t>1024-t);
p->size+=t;
q=p;
p=p->next;
p=(struct free_block_type *)malloc(sizeof(struct free_block_type));
}

rearrange_BF(){
}

rearrange_WF(){
}

int new_process(){

struct allocate_block *ab;
int size,ret;

ab=(struct allocate_block *)malloc(sizeof(struct allocate_block));
if(!ab)
exit(-5);
ab->next=NULL;
pid++;
sprintf(ab->process_name,"process=%02d",pid);
ab->pid=pid;
printf("memory for %s:",ab->process_name);
scanf("%d",&size);
if(size>0)
ab->size=size;
ret=allocate_mem(ab);
if((ret==1)&&(allocated_block_head==NULL)){
allocated_block_head=ab;
return 1;
}
else if(ret==1){
ab->next=allocated_block_head;
allocated_block_head=ab;
return 2;
}
else if(ret==-1){
printf("allocation fail\n");
free(ab);
return -1;
}
return 3
}

int allocate_mem(struct allocated_block *ab){

struct free_block_type *fbt,*pre;
int request_size=ab->size;
fbt=pre=free_block;

while(fbt!=NULL){ //开始从空闲队列寻找
if(fbt->size >= request_size){ //如果找到的块符合要求的大小
ftb->size=ftb->size-request_size; //则分配空间，改变空闲队列
ab->start_addr=ftb->start_addr; //分配的块的首地址
ftb->start_addr=ftb->start_addr+request_size; //改变空闲队列中的地址
}
pre=fbt;
fbt=fbt->next;
}
if(fbt==NULL)
return -1;
return 1;
}

void kill_process(){

struct allocated_block *ab;
int pid;
printf("kill process,pid=");
scanf("%d",&pid); 
ab=find_process(pid);
if(!ab){
free_mem(ab);
dispose(ab);
}
}

int free_mem(struct allocated_block *ab){

int algorithm=ma_algorithm;
struct free_block_type *fbt,*pre,*work;
fbt=(struct free_block_type *)malloc(sizeof(struct free_block_type));
if(!fbt)
return -1;

}

int dispose(struct allocated_free *free_ab){

struct allocated_block *pre,*ab;//这一块的代码可以简化
if(free_ab==allocated_block_head){
allocated_block_head=allocated_block_head->next;
frre(free_ab);
return 1;
}
pre=allocated_block_head;
ab=allocated_block_head->next;
while(ab!=free_ab){
pre=ab;
ab=ab->next;
}
pre->next=ab->next;
free(ab);
return 2;
}
int  display_mem_usage(){

struct free_block_type *fbt=free_block;
struct allocated_block *ab=allocated_block_head;
if(fbt==NULL)
return -1;
printf("---------------------------------------\n");
printf("free memory:\n");
printf("%20s%20s\n","    start_addr","    size");
while(fbt!=NULL){
printf("%20d%20d\n",fbt->start_addr,fbt->size);
fbt=fbt->next;
}
printf("\nused memory:\n");
printf("%10s %20s %10s %10s\n","pid","processname","start_addr","size");
while(ab!=NULL){
printf("%10d %20s %10d %10d\n",ab->pid,ab->process_name,ab->start_addr,ab->size);
ab=ab->next;
}
printf("----------------------------------------\n");
return 0;
}














