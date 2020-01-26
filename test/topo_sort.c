/*
 * 该程序主要进行拓扑排序
 * 拓扑排序主要通过统计定点的入度来进行
 * 当某一顶点的入度为0时，则将其提出，并且与该顶点相关联的顶点入度减一
 * 这里的图为有向图，且相关联的顶点，为由A指向B这一关系
 * 代码中被注释的地方为用于调试的代码
 * 最后的注释部分为测试输入部分
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

struct Graph {
	int value;
	struct Graph *next;
};
struct Graph **G;
int *degree;

int init_Graph_list(struct Graph **G);
int flush_Graph(int src, int dst);
//int print_Graph(struct Graph **G);
int *count_indegree(struct Graph **G, int n);
int topo_sort(struct Graph **G, int n, int *count);

int main(int argc, char *argv[])
{
	char str[MAX], *p;
	int src = 0, dst = 0, num = 0, N = 0;

	scanf("%d\n", &N);
	G = (struct Graph **)malloc(sizeof(struct Graph *) * (N + 1)); 

	init_Graph_list(G, N + 1);
	
	while(gets(str)) {
		if (strlen(str) == 0)
			break;
		p = str;
		while(*p != 0) {
				if (*p == '-' && *(p + 1) == '>') {
					src = num;
					num = 0;
					p = p + 2;
					continue;
				}			
				num = num * 10 + (*p - 48);
				p++;
		}
		dst = num;
		num = 0;
		
		memset(str, 0, MAX);
		flush_Graph(src, dst);
	}
	
//	print_Graph(G, N + 1);
	
	degree = count_indegree(G, N + 1);
	topo_sort(G, N + 1, degree);
}

int init_Graph_list(struct Graph **G, int n)
{
	int i = 0;
	
	for (i; i < n; i++) {
		G[i] = (struct Graph *)malloc(sizeof(struct Graph));
		G[i]->value = i;
		G[i]->next = NULL;
	}

	return 0;
}

int flush_Graph(int src, int dst)
{
	struct Graph *tmp;
	struct Graph *member;
	
	tmp = G[src];
	
	while (tmp->next != NULL)
		tmp = tmp->next;
	
	member = (struct Graph *)malloc(sizeof(struct Graph));
	member->value = dst;
	member->next = NULL;

	tmp->next = member;

	return 0;
}
/*
int print_Graph(struct Graph **G, int n)
{
	struct Graph *tmp;
	int i = 1;
	
	for (i; i < n; i++) {
		printf("%d", G[i]->value);
		tmp = G[i]->next;
		while(tmp != NULL) {
			printf("->");
			printf("%d", tmp->value);
			tmp = tmp->next;
		}
		printf("\n");
	}
	return 0;
}
*/
int *count_indegree(struct Graph **G, int n)
{
	int *count, i = 0;
	struct Graph *tmp;

	count = (int *)malloc(sizeof(int) * n);
	memset((char *)count, 0, sizeof(int) * n);

	for (i = 1; i < n; i++) {
		tmp = G[i]->next;
		while (tmp != NULL) {
			count[tmp->value]++;
			tmp = tmp->next;
		}
	}
/*
	for (i = 1; i < n; i++) {
		printf("%d: %d\n", i, count[i]);
	}
*/
	return count;
}

int topo_sort(struct Graph **G, int n, int *count)
{
	int i = 0, sum = 0, *res, j = 0;
	struct Graph *tmp;
	
	res = (int *)malloc(sizeof(int) * (n + 1));
	memset((char *)res, 0, sizeof(int) * (n + 1));

loop:
	for (i = 1; i < n; i++) {
		if (count[i] == -1) {
			sum++;
		}
		if (count[i] == 0) {
			res[++j] = i;
			break;
		}
	}
	if (sum != n - 1) {
		sum = 0;
		tmp = G[i];
		while(tmp != NULL) {
			count[tmp->value]--;
			tmp = tmp->next;
		}
/*
		for (i = 1; i < n; i++) {
			printf("%d: %d\n", i, count[i]);
		}
*/
		goto loop;
	}
	
	for (i = 1; i < n; i++) {
		printf("%d ", res[i]);
	}
	printf("\n");
	return 0;
}

/*
7
1->2
1->4
1->3
2->4
2->5
3->6
4->6
4->7
4->3
5->4
5->7
7->6
*/
