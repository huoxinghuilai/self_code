#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[]){
//确定命令字符中cmd1和cmd2的区分线
int i=0;
int flag=0;
char *word="to";
for(i=1;i<argc;i++){
if(!strcmp(argv[i],word)){
flag=i;
printf("%s,%d\n",argv[i],flag);
break;
}
}
//读取cmd1到字符串string1中
char string1[100]="";
i=1;
char *c=" ";//用来区分命令和选项
while(i<flag){
strcat(string1,argv[i]);
strcat(string1,c);
i++;
}
//读取cmd2到字符串string2中
char string2[100]="";
i=flag+1;
while(i<argc){
strcat(string2,argv[i]);
strcat(string2,c);
i++;
}
//打印出cmd1和cmd2
printf("%s\n%s\n",string1,string2);

//cmd1的标准输出成为cmd2的标准输入
FILE *fp1,*fp2;
char buffer[1025];
int chars_read;
memset(buffer,'\0',sizeof(buffer));
fp1=popen(string1,"r");
fp2=popen(string2,"w");
if((fp1!=NULL)&&(fp2!=NULL)){
chars_read=fread(buffer,sizeof(char),1024,fp1);
while(chars_read>0){
buffer[chars_read-1]='\0';
//printf("reading 1024:-\n %s\n",buffer);
fwrite(buffer,sizeof(char),strlen(buffer),fp2);
chars_read=fread(buffer,sizeof(char),1024,fp1);
}
pclose(fp1);
pclose(fp2);
}
}



