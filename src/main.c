#include <string.h>
#include <unistd.h>
#include "server/server.h"
#include "http_requests/http_requests.h"
#include "routing/routing.h"
#include "hashmap/hashmap.h"
#include "arena/arena.h"
#include "vector/vector.h"
#include "http_responses/http_responses.h"

#define PORT 8080
// Could be changed though
static char *status = "HTTP/1.1 200 OK\nContent-Type: text/html\n";

void launch(Server *server) {
	char buffer[BUFFER_SIZE];
	int n_socket = {0};
	int addrlen = sizeof(server->ipv4_address);
	HttpRequests http_requests;

	//	add_route("/", "index.html");
	//add_route("/about", "about.html");

	printf("Waiting for connection on port %d.\r\n", PORT);
	for (;;) {
		n_socket = accept(
						server->socket,
						(struct sockaddr *)&server->ipv4_address,
						(socklen_t *)&addrlen);
		read(n_socket, buffer, BUFFER_SIZE);
		http_requests = newHttpRequests(buffer);

		// should be sending response here
		char *buffer = malloc(BUFFER_SIZE);
		char *greeter = read_file("public/index.html");
		strcpy(buffer, status);
		strcat(buffer, greeter);

		printf("\n== Response ==\n");
		printf("%s\n", buffer);

		write(n_socket, buffer, strlen(buffer));
		/*
		  HttpResponse* response = newHttpResponse(filename, status, http_requests);
		  // (socket, buffer, size, flags)
		  send(n_socket, response->body, response->size, 0);
		*/
		
		close(n_socket);
	}
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
