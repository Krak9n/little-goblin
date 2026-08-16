#include <string.h>
#include <unistd.h>
#include "server/server.h"
#include "http_requests/http_requests.h"
#include "hashmap/hashmap.h"

#define BUFFER_SIZE 30000
#define PORT 8080

const static char *status = "HTTP/1.1 200 OK\r\n";

const char *read_file(const char* path) {
	char *buffer = 0;
	long contents_length = 0;

	FILE *file = fopen(path, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		contents_length = ftell(file);
		fseek(file, 0, SEEK_SET);
		buffer = malloc(contents_length);

		if (buffer) {
			fread(buffer, 1, contents_length, file);
		}
		fclose(file);
	}

	return buffer;
}

void launch(Server *server) {
	char buffer[BUFFER_SIZE];
	int n_socket = {0};
	int addrlen = sizeof(server->ipv4_address);
	HttpRequests http_requests;

	printf("Waiting for connection on port %d.\r\n", PORT);
	for (;;) {
		n_socket = accept(
						server->socket,
						(struct sockaddr *)&server->ipv4_address,
						(socklen_t *)&addrlen);
		read(n_socket, buffer, BUFFER_SIZE);
		printf("%s\r\n", buffer);
		http_requests = newHttpRequests(buffer);
		
		page(http_requests, n_socket, buffer);
		close(n_socket);
	}
}
 
void page(HttpRequests* http_requests, int socket, const char* buffer) {
	const char *greeter = read_file("public/index.html");
	char* response;
	strcpy(response, status);
	strcat(buffer, response);

	write(socket, buffer, strlen(buffer));
}

int main() {
	Server server = newServer(
							  AF_INET, 0, PORT, 10,
							  SOCK_STREAM, INADDR_ANY, launch);
	server.launch(&server);
	return 0;
}
