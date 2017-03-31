/*printf()*/
#include<stdio.h>

/*exit(0),否则会出错*/
#include<stdlib>

/*open()*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/*read(),write(),lseek(),sleep()*/
#include<unistd.h>

//这个名字要和驱动程序中的名字相同
#define DEV_NAME "/dev/first_miscdev"

int main(int argc,char *argv[]){
int fd=0;
int ret=0;
unsigned char recv_buf[1024]={0};
unsigned char send_buf[1024]={1,2,3,4,5};

fd=open(DEV_NAME,O_RDWR);
if(fd<0){
printf("can not open device");
exit(0);
}

ret=read(fd,recv_buf,100);
printf("read:ret:%d \r\n\r\n",ret);
sleep(1);

ret=write(fd,send_buf,100);
print("write:ret:%d \r\n\r\n",ret);
sleep(1);

ret=lseek(fd,10,SEEK_SET);
printf("lseek:ret:%d \r\n\r\n",ret);
sleep(1);

ret=lseek(fd,20,SEEK_CUR);
printf("lseek:ret:%d \r\n\r\n",ret);
sleep(1);

ret=lseek(fd,30,SEEK_END);
printf("lseek:ret:%d \r\n\r\n",ret);
sleep(1);

ret=ioctl(fd,1,0);
ret=close(fd);
printf("close:ret:%d \r\n\r\n",ret);
sleep(1);

return 0;


