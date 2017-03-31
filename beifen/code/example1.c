//约瑟夫环，复习链表
#include<stdio.h>
#include<stdlib.h>

struct people{
int no;
int pwd;
struct people *next;
};

int main(){

int i=0,k=0;
printf("how many pople:\n");//输入总的人数
scanf("%d",&i);

struct people *head,*flag1,*flag2;//建成循环单链表
flag1=head;
flag1=head=(struct people *)malloc(sizeof(struct people));
scanf("%d %d",flag1->no,flag1->pwd);
k=i-1;
while(k--){
flag2=(struct people *)malloc(sizeof(struct people));
scanf("%d %d",flag2->no,flag2->pwd);
flag1->next=flag2;
flag1=flag2;
}
flag1->next=head;

while(i!=1){
k=i%head->pwd;
k=k-1;
while(k--)
head=head->next;
printf("%d ",head->no);
head=head->next;
i--;
}
}
