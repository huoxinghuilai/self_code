#include<stdio.h>
#include<stdlib.h>

struct people{
int no;
int pwd;
struct people *next;
};

int main(){
struct people *head,*flag1,*flag2;
int i=0,j=0,k=1;

printf("how many pople and the password:\n");
scanf("%d %d",&i,&j);

flag1=head=(struct people *)malloc(sizeof(struct people));//sizeof(struct people *)=4;
flag1->no=k;
scanf("%d",&(flag1->pwd));

while(++k<=i){
flag2=(struct people *)malloc(sizeof(struct people));
flag2->no=k;
scanf("%d",&(flag2->pwd));
flag1->next=flag2;
flag1=flag2;
}

flag1->next=head;

/*while(i--){
	printf("%d %d\n",head->no,head->pwd);
	head=head->next;
}*/


k=j%i;
printf("%d %d %d ",i,j,k);
while(i!=1){

if(k==0){

	flag1=head;
	while(flag1->next->next!=head)
		flag1=flag1->next;
	printf("%d \n",flag1->next->no);
	k=(flag1->next->pwd)%(--i);
	printf("%d %d %d ",i,flag1->next->pwd,k);
	flag1->next=head;
	
}
else if(k==1){
	flag1=head;
	while(flag1->next!=head)
		flag1=flag1->next;
	printf("%d \n",flag1->next->no);
    k=(flag1->next->pwd)%(--i);
	printf("%d %d %d ",i,flag1->next->pwd,k);
	flag1->next=head->next;
	head=flag1;
}
else{
    flag1=head;
    while(k-->2)
		flag1=flag1->next;
    printf("%d \n",flag1->next->no);	
	k=(flag1->next->pwd)%(--i);
    printf("%d %d %d ",i,flag1->next->pwd,k);
	flag1->next=flag1->next->next;
	head=flag1->next;
}
}
printf("%d\n",head->no);

}
