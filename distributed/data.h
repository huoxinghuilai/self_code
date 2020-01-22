#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 * 构建数据结构
 */

struct simple_data {
	char key[10];
	char value[10];
};

struct arguments {
	char method[5];
	char node[4];
	struct simple_data data;
};

/*
 * 创建本地服务socket
 */

int create_socket() {

	int sock_fd;
	struct sockaddr_in *server;

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	server = (struct sockaddr_in *)malloc(sizeof(struct sockadd_in));
	server->sin_family = AF_INET;
	server->sin_port = htons(8000);
	server->sin_addr.sa = inet_addr("127.0.0.1");

	if (bind(sock_fd, (struct sockaddr *)server, sizeof(struct sockaddr_in)) == -1) {

		printf("无法绑定端口，请检查端口号是否可用！\n");
		return -1;
	}

	if (listen(sock_fd, 100) == -1) {

		printf("监听服务出错，请重启！\n");
		return -1；
	}

	return sock_fd;
}
