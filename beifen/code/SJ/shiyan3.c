#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctype.h>

#define MAX_THREAD 3
unsigned long long main_counter,counter[MAX_THREAD];

void *thread_worker(void *);

int main(int agrc,char argv[]){

	int i,rtn,ch;
	pthread_t pthread_id[MAX_THREAD]={0};/*存放线程id*/
    for(i=0;i<MAX_THREAD;i++){
		pthread_create(&pthread_id[i],NULL,(void *)thread_worker,(void *)i);

	}
    for(i=0;i<MAX_THREAD;i++)
                printf("%d\n",pthread_id[i]);

	do{
		unsigned long long sum;
		for(i=0;i<MAX_THREAD;i++){
			sum+=counter[i];
			printf("%llu ",counter[i]);
		}
		printf("%llu %llu\n",main_counter,sum);
	}while((ch=getchar())!='q');
		return 0;
}

void *thread_worker(void *p){
	
        
	int thread_num;
        
        thread_num=(int)p;
        printf("%x %x %d\n",&p,&thread_num,thread_num);
        thread_num=(int)(*(int *)p);
	for(;;){
		counter[thread_num]++;
		main_counter++;
        printf("%d %d\n",counter[thread_num],main_counter);
        printf("%d %d\n",pthread_self(),thread_num);
	sleep(2);
        }
}
