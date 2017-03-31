#include<stdio.h>

struct p{
	int x;
	int y;
};


struct p b[3]={{0,3},{1,4},{2,5}};
struct p *a=b;

int main(){

	int i=3;
	while(i--){
		printf("%d %d %d\n",a[i],a[i].x,a[i].y);
	}
	return 0;
}
	