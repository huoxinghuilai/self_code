#include<stdio.h>
#include<stdlib.h>
#include"list.h"

struct C{
	int x,y;
    struct list_head list;
};

int main(){
	
	int i,j;
	int m=0,n;
    struct C *head,*p,*q;
    struct list_head *pos;

    scanf("%d %d",&i,&j);

    head=(struct C *)malloc(sizeof(struct C));
    head->x=(++m);
    scanf("%d",&n);
    head->y=n;
    INIT_LIST_HEAD(&(head->list));

    while(m++<i){
    p=(struct C *)malloc(sizeof(struct C));
    p->x=m;
    scanf("%d",&n);
    p->y=n;
    list_add_tail(&(p->list),&(head->list));
	}
    
	q=head;
	while(--m){
		printf("%x %x %x\n",&(q->list),q->list.next,q->list.prev);
		printf("%d %d\n",q->x,q->y);
		printf("%x\n",q->list.next);
		pos=q->list.next;
		q=list_entry(pos,struct C,list);
	}
        
        if(i!=0)
	j=j%i;
	while(i!=0){

	if(j==0){
		pos=head->list.prev;
		q=list_entry(pos,struct C,list);
        printf("%d ",q->x);
	
	}
    else if(j==1){
		q=head;
		printf("%d ",q->x);
                
		pos=head->list.next;
        head=list_entry(pos,struct C,list);
		
	}
	else{
		*pos=head->list;
		while(--j)
			pos=pos->next;
		q=list_entry(pos,struct C,list);
		printf("%d ",q->x);
		
		pos=pos->next;
		head=list_entry(pos,struct C,list);
        
	}
        
        i=i-1;
        if(i!=0)
        j=(q->y)%i;
        list_del(&(q->list));
	}

}




