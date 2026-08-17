#include <string.h>
#include <unistd.h>
#include "server/server.h"
#include "http_requests/http_requests.h"
#include "routing/routing.h"
#include "hashmap/hashmap.h"

#define BUFFER_SIZE 30000
#define PORT 8080

int page(HttpRequests* http_requests, int socket, char* pass_buffer);
const static char *status_success = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";

char *read_file(const char* path) {
	char *buffer;
	long contents_length;

	FILE *file = fopen(path, "rt");
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
	if (*buffer) {
		printf("File has been read!\n");
	}

	return buffer;
}

void launch(Server *server) {
	char buffer[BUFFER_SIZE];
	int n_socket = {0};
	int addrlen = sizeof(server->ipv4_address);
	HttpRequests http_requests;

	printf("here\n");
	add_route("/", "index.html");
	printf("not here\n");
	add_route("/about", "about.html");

	printf("Waiting for connection on port %d.\r\n", PORT);
	for (;;) {
		n_socket = accept(
						server->socket,
						(struct sockaddr *)&server->ipv4_address,
						(socklen_t *)&addrlen);
		read(n_socket, buffer, BUFFER_SIZE);
		printf("%s\r\n", buffer);
		http_requests = newHttpRequests(buffer);
		
		n_socket = page(&http_requests, n_socket, buffer);
		close(n_socket);
	}
}
 
int page(HttpRequests* http_requests, int socket, char* pass_buffer) {
	char *buffer = malloc(BUFFER_SIZE);
	char *greeter = read_file("public/index.html");
	strcpy(buffer, status_success);
	strcat(buffer, greeter);
	printf("\n%s\n", buffer);

	write(socket, buffer, strlen(buffer));
	return socket;
}

int main() {
	char *path;
	printf("Current path is: %s\n", getcwd(path, BUFFER_SIZE));
	Server server = newServer(
							  AF_INET, 0, PORT, 10,
							  SOCK_STREAM, INADDR_ANY, launch);
	server.launch(&server);
	return 0;
}
