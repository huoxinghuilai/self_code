#include<stdio.h>
#include<pthread.h>
#include<ctype.h>

int total_words;
pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALZER;

int main(int ac,char *av[]){

pthread_t t1,t2;
void *count_words(void *);

if(ac!=3){
printf("usage: %s file1 file2",av[0]);
exit(1);
}

total_words=0;

pthread_create(&t1,NULL,count_words,(void *)av[1]);
pthread_create(&t2,NULL,count_words,(void *)av[2]);
pthread_join(t1,NULL);
pthread_join(t2,NULL);

printf("%5d, total words\n",total_words);
}

void *count_words(void *f){

char *filename=(char *)f;
FILE *fp;
int c,prevc='\0';

if((fp=fopen(filename,"r"))!=NULL){
while((c=hetc(fp))!=EOF){
if(!isalnum(c) && isalnum(prevc)){
pthread_mutex_lock(&counter_lock);//加上锁子，不让其他人用
total_words++;
pthread_mutex_unlock(&counter_lock);//打开锁子，让大家可以使用
}
prevc=c;
}
free(fp);
}
else
perror(filename);
return NULL;
}

