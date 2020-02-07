#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "include/node.h"

#define MAX_SIZE 4096

struct process_data *parse_data(char *buff)
{
	struct process_data *arg;
	
	arg = (struct process_data *)malloc(sizeof(struct process_data));
	memcpy(arg, "0", sizeof(struct process_data));
	memcpy(&(arg->arg), buff, sizeof(struct arguments));

	printf("parse_data: %s %s %s %s\n", (arg->arg).method, (arg->arg).node, (arg->arg).data.key, (arg->arg).data.value);

	return arg;
}

/*
 * 该函数用于将数字转换为字符串，虽然是在开始不明确流程的时候写下的，
 * 但是仍然会保留该函数，以便后边会使用到
 */

char *itos(int data)
{
	char temp[5] = {0};
	int i = 0, start = 0, end = 0;

	while (1) {
		temp[i] = (char)('0' +  (data % 10));	
		data = data / 10;
		if (data != 0)
			i++;
		else
			break;	
	}
	
	for (end = i; start < end; start++, end--) {
		char tmp = temp[start];
		temp[start] = temp[end];
		temp[end] = tmp;
	}

	temp[end + 1] = '\0';

	char *str = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
	strcpy(str, temp);

	printf("str: %s\n", str);
	
	return str;
}

int main(int argc, char *argv[])
{
	int port = 0, i = 0;
	char *mode;

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--port"))
			port = atoi(argv[i + 1]);

		if (!strcmp(argv[i], "--mode")) {
			mode = (char *)malloc(sizeof(char) * (strlen(argv[i]) + 1));
			strcpy(mode, argv[i + 1]);
		}

		//对slaver的ip地址进行哈希计算后，按照索引顺序存入文件中，便于后期根据哈希索引按顺序获取slaver的ip，
		//这块先注释掉了，因为hash函数还没有完成。
		if (!strcmp(argv[i], "--slaver")) {
			int fd = open("./slaver_ip_table", O_RDWR | O_CREAT | O_APPEND, 0777);
 			
			//char *node = hash_ip(argv[i + 1]);
			//int len = strlen("slaver_ip: ") + strlen(node) + strlen(argv[i + 1]) + 1;
			
			int len = strlen("slaver_ip: ") + strlen(argv[i + 1]) + 1;
			char *buff = (char *)malloc(sizeof(char) * len);

			//snprintf(buff, len, "slaver_ip_%s: %s", node, argv[i + 1]);
			snprintf(buff, len, "slaver_ip: %s", argv[i + 1]);
			
			write(fd, buff, len);
			write(fd, "\r\n", 2);
			close(fd);
		}
	
		//用来保存slaver所对应的master节点地址，在分块分层级的设计中可能会需要
		if (!strcmp(argv[i], "--master")) {
			int fd = open("./master_ip_table", O_RDWR | O_CREAT | O_APPEND);
			
			int len = strlen("master_ip: ") + strlen(argv[i + 1]) + 1;
			char *buff = (char *)malloc(sizeof(char) * len);
			
			snprintf(buff, len, "master_ip: %s", argv[i + 1]);
			write(fd, buff, len);
			write(fd, "\r\n", 2);
			close(fd);
		}
	}

	int sock_fd = create_server_socket(port); 

	while (1) {

		int client_fd = 0, len = 0;
		char buffer[MAX_SIZE] = {0};
		struct process_data *arg;	//该结构体主要用于向处理子进程提供所需要的参数
		struct sockaddr_in *client_addr;
		
		client_addr = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
		memcpy(client_addr, "0", sizeof(struct sockaddr_in));
		len = sizeof(struct sockaddr_in);
		client_fd = accept(sock_fd, (struct sockaddr *)client_addr, &len);
		
		if (client_fd >= 0) {

			int pid = fork();
			if (pid == 0) {
				
				printf("Child process resolve data.\n");
				while (1) {
					
					int num = recv(client_fd, buffer, sizeof(struct arguments) + 1, 0);
					if (num > 0) {
				
						printf("client_fd %d has received %d words.\n", client_fd, num); 

						arg = parse_data(buffer);

						if (!strcmp(mode, "master")) {
							
							printf("mode: %s method: %s\n", mode, arg->arg.method);
							
							//char *res = "Server has got data.";
							//send(client_fd, res, strlen(res), 0);
							
							if (!strcmp(arg->arg.method, "set")) {
								
								struct node *node = find_memory_node();
								if (node == NULL) {
									char *str = "Can't restore data.";
									send(client_fd, str, strlen(str), 0);
								} else {
									char *tmp = send_data_to_node(&(arg->arg), node);
									send(client_fd, tmp, strlen(tmp), 0);
								}
							}
							
							else if (!strcmp(arg->arg.method, "get")) {
								struct node *node = get_node(arg->arg.node);
								char *res = recv_data_from_node(&(arg->arg), node);
								send(client_fd, res, strlen(res), 0);
							}
							
						}

						if (!strcmp(mode, "slaver")) {
							printf("mode: %s method: %s\n", mode, arg->arg.method);
							if (!strcmp(arg->arg.method, "status")) {
								check_status(client_fd);
							}
							else if (!strcmp(arg->arg.method, "set")) {
								char *res = restore_data(&(arg->arg));
								send(client_fd, res, strlen(res), 0);
							}
							else if (!strcmp(arg->arg.method, "get")) {
								char *value = get_data(&(arg->arg));
								printf("value: %s\n", value);
								send(client_fd, value, strlen(value), 0);
							}
							
						}
					}		
				}
			}
			close(client_fd);
		}
	}
}
