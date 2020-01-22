#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	/*
	 * 时针与分针之间的锐角角度
	 */
	char s[100], *p;
    	float a[2], x, y, z, d;

	gets(s);
    
	p=s;
    
	while(1)
	{
		a[0] = (*p) % 48 * 10 + *(p + 1) % 48;  //时针
		if( a[0] > 12)                    //时针取0~12
			a[0] = a[0] - 12;
		a[1] = *(p + 3) % 48 * 10+ *(p + 4) % 48;//分针
	
		x = a[1] / 60 * 30;               //时针一小时内偏移角度	
		y = a[1] / 60 * 360;              //分针偏移角度
		z = a[0] / 12 * 360;              //时针偏移角度
	
		if (z >= y)                    	  //分针靠后
			d = z - y + x;
		else                        	  //分针靠前
			d = y - z - x;
		if(d > 180)
			d = 360 - d;
		printf("%f\n", d);

    		if(*(p + 5) == '\n')
			break;
		p=p+6;
	}

	/*
	 * 链表输入
	 */
	struct time{
		char s[50];
		struct time *next;
	};
	int i = 3;
	struct time *head, *p;
	head = (struct time *)malloc(sizeof(struct time));
	p = head;
	while (i--)
	{
		struct time *q = (struct time *)malloc(sizeof(struct time));	
		scanf("%s", q->s);
		if(strlen(q->s) == "")
			break;
		q = p->next;
		p = q;						
	}
	
	p = head->next;
	while(p != NULL)
	{
		printf("%s\n", p->s);
		p = p->next;
	}
	
	/*
	 * 正方形面积
	 */
  	float length, area;
    	scanf("%f", &length);
    	area = length * length;
    	printf("%f\n", area); 
}
