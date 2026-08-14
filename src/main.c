#include <string.h>
#include <unistd.h>
#include "server/server.h"

#define BUFFER_SIZE 30000
#define PORT 8080

void launch(Server *server) {
	char buffer[BUFFER_SIZE];
	char *greeter = "HTTP/1.1 200 OK\nGMT\nServer: Apache/2.2.14 (Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-Type: text/html\nConnection: Closed\n\n<html><body><h1>Me</h1></body</html>";
	int n_socket = 0;

	printf("Waiting for connection on port %d.\r\n", PORT);
	for (;;) {
		n_socket = accept(
						server->socket,
						(struct sockaddr *)&server->address,
						(socklen_t *)sizeof(&server->address));
		read(n_socket, buffer, BUFFER_SIZE);
		printf("%s", buffer);

		write(n_socket, greeter, strlen(greeter));
		close(n_socket);
	}
}

int main() {
	Server server = server_constructor(
									   AF_INET,
									   0,
									   PORT,
									   10,
									   SOCK_STREAM,
									   INADDR_ANY,
									   launch
									   );
	server.launch(&server);
	return 0;
}
