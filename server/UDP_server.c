#include "../SocketOptions/NP.h"
#include <stdio.h>

#define MAX_READ_LENGTH 2096

int main(int argc, char* argv[]) {
	
	int socket_fd;
	int port_number = atoi(argv[1]);
	char read_buffer[MAX_READ_LENGTH];

	struct sockaddr_in server_addr, client_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_number);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	socket_fd = Socket(AF_INET, SOCK_DGRAM, 0);

	Bind(socket_fd, (const struct sockaddr *) &server_addr,
		(socklen_t)sizeof(server_addr));	

	socklen_t client_addr_length = (socklen_t)sizeof(client_addr);

	puts("Server Starting");

	int len;
	while(1){
		if((len = recvfrom(socket_fd, read_buffer, MAX_READ_LENGTH, 0,
			(struct sockaddr *)&client_addr, &client_addr_length)) < 0) {
			perror("Error reading from client\n");
			exit(1);
		}
		if ((sendto(socket_fd, read_buffer, len, 0,
			(struct sockaddr *)&client_addr, client_addr_length)) < 0) {
			perror("Error writing to client\n");
			exit(1);
		}

		bzero(read_buffer, len);
	}

	close(socket_fd);
	return 0;
}