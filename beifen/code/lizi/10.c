#define N 10
int i;sum,fd;
int *result_ptr=mmap(0,4,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
int pid=fork();
if(pid==0){
for(sum-0,i=1;i<=N;i++)
sum+=i;
*result_ptr=sum;
}
else{
wait(0);
printf("result=%d\n",*result_ptr);
}
