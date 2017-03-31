//银行家算法
#include<stdio.h>

int zy[2]; //表示有3种资源
int xq1[3][2]; //实际需求资源数
int fp[3][2]; //得到的资源数
int xq2[3][2]; //还需要的资源数

int main(){

	int i,j;
	int t[2],t1[3][2],t2[3][2],t3[3][2]
	for(i=0;i<2;i++)
		scanf("%d",&zy[i]); //输入各种资源的个数
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			scanf("%d %d",&xq1[i][j],&fp[i][j]); //输入每个进程实际需要的资源，和已经得到的资源
			xq2[i][j]=xq1[i][j]-fp[i][j]; //求取每个进程还需要的资源
			if(xq2[i][j]<0){
				printf("输入错误！\n");
				return 0;
			}
		}
	}
    
	for(i=0;i<2;i++)
		t[i]=zy[i]; //各种资源总个数
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			t1[i][j]=xq1[i][j]; //每个进程实际需要的资源数
			t2[i][j]=fp[i][j]); //每个进程得到的资源数
			t3[i][j]=xq2[i][j]; //每个进程还需要的资源数
		}
	}
	//因为是求一个安全序列，所以让每个进程开头测试。
	for(j=0;j<2;j++){
		for(i=0;i<3;i++){
			t[j]-=fp[i][i];
			if(t[j]<t3[i][j]){
				printf("安全序列有错！\n");
				return 0;
			}
		}
	}



    



