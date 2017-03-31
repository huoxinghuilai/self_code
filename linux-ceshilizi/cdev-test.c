#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
int testdev;
int i,ret;
char buf[10];

testdev=open("/dev/mycdev",O_RDWR);
if(testdev==-1){
printf("cannot open file.\n");
exit(1);
}

if(ret=read(testdev,buf,10)<10){
printf("read error!\n");
exit(1);
}

for(i=0;i<10;i++){
printf("%d\n",buf[i]);
close(testdev);

return 0;
}