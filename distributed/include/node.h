#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "sock_create.h"

#define MAX_SIZE 4096

//对slaver的IP：PORT进行哈希，将ip:port存到对应的哈系索引中，方便查找，可自行实现
char *hash_node(struct node *node)
{
	return NULL; 
}

//根据哈希索引值查找缩对应的ip:port
char *hash_ip(char *buff)
{
	return NULL;
}

struct node *get_node_info(char *buff)
{
	int i = 0, start = 0, end = 0;

	while (i < strlen(buff)) {
		if (buff[i] == ':') {
			if (start == 0)
				start = i + 2;
			else
				end = i;
		}
		i++;
	}

	char *ip = (char *)malloc(sizeof(char) * (end - start + 1));
	char *port = (char *)malloc(sizeof(char) * (strlen(buff) - end));

	memcpy(ip, &buff[start], end - start);
	strcat(ip, "\0");
	memcpy(port, &buff[end + 1], strlen(buff) - end - 1);
	strcat(port, "\0");

	int ip_port = atoi(port);

	printf("ip:port => %s:%d\n", ip, ip_port);

	int sock_fd = create_client_socket(ip_port, ip);
	struct arguments *array_send = (struct arguments *)malloc(sizeof(struct arguments));
	memcpy(array_send, "0", sizeof(struct arguments));
	strcpy(array_send->method, "status");

	send(sock_fd, array_send, sizeof(struct arguments), 0);
	
	char array_recv[MAX_SIZE] = {0};
	
	recv(sock_fd, array_recv, MAX_SIZE, 0);

	close(sock_fd);
	
	printf("array_recv: %s\n", array_recv);	
	if (!strcmp(array_recv, "Server can restore.")) {
		struct node *node = (struct node *)malloc(sizeof(struct node));
		strcpy(node->ip, ip);
		node->port = ip_port;

		return node; 
	} else {
		return NULL;	
	}
}

struct node *find_memory_node()
{
	int fd = open("./slaver_ip_table", O_RDONLY);
	int count = 0;

	while (1) {
		char *tmp, buff[50] = {0};

		int num = read(fd, buff, 50);
		if (num > 0) {

			int i = 0;
			while (buff[i] != '\n') {
				i++;
			}
			count = count + i + 1;
			tmp = (char *)malloc(sizeof(char) * (i + 1));
			memcpy(tmp, buff, i);
			tmp[i + 1] = '\0';		

			printf("buff: %s tmp: %s\n", buff, tmp);

			struct node *node = get_node_info(tmp);
			if (node != NULL) {
				return node;	
			}
				
			lseek(fd, count, SEEK_SET);
		}
		if (num == 0)
			break;			
	}

	return NULL;
}


char *send_data_to_node(struct arguments *arg, struct node *node)
{
	int sock_fd = create_client_socket(node->port, node->ip);
	send(sock_fd, arg, sizeof(struct arguments) + 1, 0);
	
	char buff[MAX_SIZE] = {0};
	recv(sock_fd, buff, MAX_SIZE, 0);
	
	close(sock_fd);	

	if (!strcmp(buff, "success")) {
		printf("Data has been stored.\n");
		return "success";
//		char *node = hash_node(node);
//		return node;
	}
	else
		return NULL;	
}

struct node *find_node_by_hash(char *buff)
{
	return NULL;
}

struct node *get_node(char *buff)
{
	//struct node *node = find_node_by_hash(buff);
	
	struct node *node = (struct node *)malloc(sizeof(struct node));
	strcpy(node->ip, "127.0.0.1");
	node->port = 9000;

	return node;	
}

char *recv_data_from_node(struct arguments *arg, struct node *node)
{
	int sock_fd = create_client_socket(node->port, node->ip);
	send(sock_fd, arg, sizeof(struct arguments), 0);
	
	char buff[MAX_SIZE] = {0};
	recv(sock_fd, buff, MAX_SIZE, 0);
	
	printf("buff: %s\n", buff);	
	
	char *tmp = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
	strcpy(tmp, buff);
	strcat(tmp, "\0");

	return tmp;
}

//该函数用于检测当前节点的存储状态，当前使用随机数进行简单的模拟，该函数可以被替换
int check_status(int sock_fd)
{
	int tmp = 0;
	
	srand((unsigned)time(NULL));
	tmp = rand() % 10;
	
	printf("tmp: %d\n", tmp);

	char *str1 = "Server can restore.";
	char *str2 = "Server can't restore.";
//	if (tmp > 5)
		send(sock_fd, str1, strlen(str1), 0);
//	else 
//		send(sock_fd, str2, strlen(str2), 0);

	return 0;			
}

char *restore_data(struct arguments *arg)
{
	if (!strcmp(arg->method, "set")) {
		int fd = open("./memory_data", O_CREAT | O_RDWR | O_APPEND, 0777);
		int len = strlen(arg->data.key) + strlen(arg->data.value) + 3;
		char *buff = (char *)malloc(sizeof(char) * len);
		snprintf(buff, len, "%s: %s", arg->data.key, arg->data.value);
		printf("key: %s value: %s\n", arg->data.key, arg->data.value);
		printf("key -> value: %s\n", buff);
		write(fd, buff, len);
		write(fd, "\r\n", 2);
		close(fd);

		return "success";
	}
}


char *get_data(struct arguments *arg) 
{
	printf("method: %s key: %s\n", arg->method, arg->data.key);
	
	if (!strcmp(arg->method, "get")) {
		int fd = open("./memory_data", O_RDONLY);
		int count = 0;
		while(1) {
			char buff[50] = {0};
			int num = read(fd, buff, 50);
			if (num > 0) {
                        	int i = 0, flag = 0;
                        	while (buff[i] != '\n') {
					if (buff[i] == ':')
						flag = i;
					i++;
				}

				char *tmp = (char *)malloc(sizeof(char) * (flag + 1));
				memcpy(tmp, buff, flag);
				strcat(tmp, "\0");
				printf("buff: %s, flag: %d i: %d tmp: %s key: %s\n", buff, flag, i, tmp, arg->data.key);

				if (!strcmp(arg->data.key, tmp)) {
					char *value = (char *)malloc(sizeof(char) * (i - flag));
					memcpy(value, &buff[flag + 2], i - flag);
					strcat(value, "\0");
					return value;
				}
                        	
				count = count + i + 1;
                             	lseek(fd, count, SEEK_SET);

                	}
			if (num ==0)
				break;
		}

		return "Not found data.";		
	}
}
