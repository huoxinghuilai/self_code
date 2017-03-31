#include<stdio.h>
#include<stdlib.h>

#define m 13

struct link{
	int num;
	struct link *next;
};
struct link *b[m];

//初始化哈希表
struct link *init()
{
	int i=0;
	for(i;i<m;i++)
	{
		b[i]=(struct link *)malloc(sizeof(struct link));
		b[i]->next=NULL;
	}
	return b[0];
}

//求取最大的素数
int sushu()
{
	int i=0;
	int j=m;
	while(j)
	{
		for(i=2;i<j;i++)
		{
			if(!(j%i))
				break;
		}
		if(i==j)
			break;
		j--;
	}
    return j;	
}

//创建哈希表，是地址链表的形式
struct link *create(int *a)
{
	int i=0;
	int j=m;
	int k=0;
	int d=0;
	struct link *p;
	k=sushu();
	for(i;i<m-1;i++)
	{
		d=a[i]%k;
		
		//获取空间
		p=(struct link *)malloc(sizeof(struct link));
		p->num=a[i];

		//用头插的方式插入
		p->next=b[d]->next;
		b[d]->next=p;
	}
	return b[0];
}

//显示链表地址的存储
struct link *show()
{
	int i=0;
	struct link *p;
	for(i;i<m;i++)
	{
		printf("b[%d]",i); 
		p=b[i]->next;
		while(p!=NULL)
		{
			printf(" -> %d",p->num);
			p=p->next;
		}
		printf("\n");
	}
}	

//寻找数据位置
int search(int i)
{
	int d;
	int j=1;
	struct link *p; 
	
	//求出数值所在的行
	d=i%m;
	p=b[d]->next;
	
	//求出数值所在的列
	while(p!=NULL)
	{
		if(p->num==i)
		{
			printf("位置：(%d,%d)\n",d,j);
			return;
		}
		p=p->next;
		j++;
	}
	printf("no this num!\n");
	return;
}

int main()
{
	int i=0;
	int a[m-1];
	int t;
	for(i=0;i<m-1;i++)
	{
		scanf("%d",&a[i]);
	}
    
	init();
	create(a);
	show();

	scanf("%d",&t);
	search(t);

}

