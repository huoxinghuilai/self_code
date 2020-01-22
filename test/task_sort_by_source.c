//进程排队，假设2种资源，3个进程
#include <stdio.h>

int main(){

	int i, j, flag = 0, k =0, v = 0;
	int t[2], t1[3][2], t2[3][2], t3[3][2], s[2] = {0}, a[3];
	
	for (i = 0; i < 2; i++)
		scanf("%d", &t[i]);	//输入每种资源的个数
	
	for (i = 0; i < 3; i++){	//输入每个进程关于每种资源，已经得到的和还需要的个数	
		for (j = 0; j < 2; j++){
			
			scanf("%d %d", &t1[i][j], &t2[i][j]); 
			s[j] = s[j] + t1[i][j];
		}
	}
	
	for (j = 0; j < 2; j++)	//每种资源剩余个数
		s[j] = t[j] - s[j];
	
	//求取合理的进程运行序列。
	while (1) {
		for(i = 0; i < 3; i++) {
			for (j = 0; j < 2; j++) {	
				if(t2[i][j] != 0 && t2[i][j] < s[j]) {
					flag++;
				}			
			}
		
			if (flag == 2) {
				for (j = 0; j < 2; j++) {
					s[j] += t1[i][j];
					t2[i][j] = 0;
				}
				a[k++] = i;
				count++;
			}
	
			flag = 0;
			v++;
		}
		
		if (count == 3)
			break;
			
		if (v == 3) {
			printf("出现死锁问题，请重新配置资源！\n");
			return -1;
		}
	}
	
	for (i = 0; i < 3; i++)
		printf("%d ", a[i]);
	printf("\n");
	
	return 0;
}

----------------------
example:
10
10
2 3
3 4
3 1
1 4
4 3
2 3
	
example:
10
10
2 3
3 4
3 2
1 5
4 3
2 3
-----------------------

    



