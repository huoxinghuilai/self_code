#include<stdio.h>
#include<stdlib.h>
float *sort(float A[])
{
	int i=0,j=0,t;
	for(i;i<10;i++)
	{
		for(j=i;j<10;j++)
		{
			if(A[i]<A[j])
			{
				t=A[i];
				A[i]=A[j];
				A[j]=t;
			}
		}
	}
	return A;
}
int main()
{
	float A[10];
	int i=0;
	for(i;i<11;i++)
		A[i]=rand();
	for(i=0;i<10;i++)
		printf("%d ",A[i]);
	printf("\n");
	sort(A);
	for(i=0;i<10;i++)
		printf("%d ",A[i]);
	printf("\n");
	return 0;
}