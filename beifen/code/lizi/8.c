#include<stdiio.h>
#include<stdlib.h>
#include<unistd.h>

//获取buff的地址，并且在后台运行该程序，在另一个程序中测试buff地址以后的1024个字节能否使用
int main(int argc,char *argv[]){
int i;
unsigned char *buff;
buff=(char *)malloc(sizeof(char)*1024);
printf("My pid is:%d\n",getpid());
for(i=0;i<60;i++){
sleep(60);
}
return 0;
}
