#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len = sizeof(client_addr);
	int opt = 1;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("setsockopt failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(12345);
	if (bind(server_fd, (struct sockaddr *)&server_addr,
	sizeof(server_addr)) == -1)
	{
		perror("bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port 12345\n");
	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd == -1)
	{
		perror("accept failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}
	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
	close(client_fd);
	close(server_fd);
	return (0);
}
