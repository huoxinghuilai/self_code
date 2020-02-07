#include "data_struct.h"

//设置最大监听数，后期（可能）会修改为epoll形式
#define MAX_LISTEN 100

struct sock_data *create_sock_addr(int port)
{	
        int sock_fd = 0 , ip_port = 8000;
        struct sockaddr_in *server;
	struct sock_data *data;

        sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (port)
                ip_port = port;

        server = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	memcpy(server, "0", sizeof(struct sockaddr_in));
        server->sin_family = AF_INET;
        server->sin_port = htons(ip_port);
	
	data = (struct sock_data *)malloc(sizeof(struct sock_data));
	memcpy(data, "0", sizeof(struct sock_data));
	data->sock_fd = sock_fd;
	data->sock_addr = server;

	return data;
}

int create_server_socket(int port) 
{	
	struct sock_data *data;
	data = create_sock_addr(port);

	data->sock_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	printf("sock_addr: %s\n", inet_ntoa(data->sock_addr->sin_addr));	
        
	if (bind(data->sock_fd, (struct sockaddr *)data->sock_addr, sizeof(struct sockaddr_in)) == -1) {

                printf("端口绑定失败，请重试\n");
                return -1;
        }

        if (listen(data->sock_fd, MAX_LISTEN) == -1) {

                printf("端口监听失败，请重试\n");
                return -1;
        }

        return data->sock_fd;
}

int create_client_socket(int port, char *ip) 
{
	struct sock_data *data;
	data = create_sock_addr(port);

        data->sock_addr->sin_addr.s_addr = inet_addr(ip);	
	printf("sock_addr: %s\n", inet_ntoa(data->sock_addr->sin_addr));	
	
	if (connect(data->sock_fd, (struct sockaddr *)data->sock_addr, sizeof(struct sockaddr_in)) == -1) {
		
		printf("连接失败，请重试\n");
		return -1;
	}

	return data->sock_fd;
}

