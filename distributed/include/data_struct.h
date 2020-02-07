#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct simple_data {
	char key[10];
	char value[10];
};

struct arguments {
	char method[5];
	char node[4];
	struct simple_data data;
};

//该结构体主要用于向子进程提供其所需的参数，可对其进行扩充或修改
struct process_data {
	struct arguments arg;
};

struct sock_data {
	int sock_fd;
	struct sockaddr_in *sock_addr;
};

struct node {
	char ip[16];
	int port;
};
