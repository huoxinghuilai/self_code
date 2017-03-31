#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define MAXSTACK 100

int stack[MAXSTACK][2];
int size=0;
sem_t sem;

void readdata1(){

FILE *fp;
fp=fopen("1.dat","r");
while(!feof(fp)){
fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
sem_post(&sem);
++size;
}
fclose(fp);
}

void readdata2(){

FILE *fp;
fp=fopen("2.dat","r");
while(!feof(fp)){
fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
sem_post(&sem);
++size;
}
fclose(fp);
}

void handledata1(){

while(1){
sem_wait(&sem);
printf("multiply: %d*%d=%d\n",stack[size][0],stack[size][1],stack[size][0]*stack[size][1]);
--size;
}
}

void handledata2(){

while(1){
sem_wait(&sem);
printf("multiply: %d*%d=%n",stack[size][0],stack[size][1],stack[size][0]*stack[size][1]);
--size;
}
}

int main(){

pthread_t t1,t2,t3,t4;
sem_init(&sem,0,0);
pthread_create(&t1,NULL,(void *)handledata1,NULL);
pthread_create(&t2,NULL,(void *)handledata2,NULL);
pthread_create(&t3,NULL,(void *)readdata1,NULL);
pthread_create(&t4,NULL,(void *)readdata2,NULL);
pthread_join(t1,NULL);
}




