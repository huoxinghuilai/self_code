#include<stdio.h>
#include<sys/shm.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define TIME_MEM_KEY 99
#define SEG_SIZE ((size_t)100)
#define oops(m,x) {perror(m);exit(x);}

main(){
int seg_id;
char *mem_ptr,*ctime();
long now;
seg_id=shmget(TIME_MEM_KEY,SEG_SIZE,0777);
printf("%d\n",seg_id);
if(seg_id==-1)
oops("shmget",1);
mem_ptr=shmat(seg_id,NULL,0);
printf("%s\n",mem_ptr);
if(mem_ptr==(void *)-1)
oops("shmat",2);
printf("the time,direct from memory:..%s",mem_ptr);
shmdt(mem_ptr);
}

