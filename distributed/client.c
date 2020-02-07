#include "include/sock_create.h"

int main(int argc, char *argv[])
{
	int port = 0, i = 0;
	char *ip;

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--port"))
			port = atoi(argv[i + 1]);

		if (!strcmp(argv[i], "--dest")) {
			ip = (char *)malloc(sizeof(char) * (strlen(argv[i + 1]) + 1));
			strcpy(ip, argv[i + 1]);
		}
	}

	int sock_fd = create_client_socket(port, ip);

	while (1) {

		struct simple_data data;
		struct arguments arg;

		scanf("%s %s %s %s", arg.method, arg.node, data.key, data.value);
		memcpy(&arg.data, &data, sizeof(struct simple_data));
		
		char *buff = (char *)malloc(sizeof(struct arguments) + 1);
		memcpy(buff, &arg, sizeof(struct arguments));
		strcat(buff, "\0");
		printf("\n%s %s %s %s\n", ((struct arguments *)buff)->method, ((struct arguments *)buff)->node, ((struct arguments *)buff)->data.key, ((struct arguments *)buff)->data.value);		
		
		int num  = send(sock_fd, buff, sizeof(struct arguments) + 1, MSG_DONTWAIT);
/*
		char *buff = "12345";
		int num = send(sock_fd, buff, strlen(buff), MSG_DONTWAIT);
*/
		if (!num) {
			printf("Send data failed!");
			return -1;
		} else {
			printf("Send data success, data is: %d!\n", num);
		}
	
		char res[20] = {0};
		recv(sock_fd, res, 20, 0);
		printf("res: %s\n", res);

	}
}
