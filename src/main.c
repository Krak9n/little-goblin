#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {

  int server_fd; 
  int new_socket; 

  struct sockaddr_in address; 

  int opt = 1;  
  int addrlen = sizeof(address); 
  char buffer[40000] = {0}; 
  
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(8080);

  if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
    perror("Bind failed");     
    exit(EXIT_FAILURE);     
  }

  // from here start a while loop
  // for multiple connections, 
  // not just one
  listen(server_fd, 3);
  printf("listening on port 8080...\n");
  new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
  
  read(new_socket, buffer, 40000);
  printf("received request:\n%s\n", buffer);

  const char *response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: 12\r\n"
    "\r\n"
    "nothing";

  write(new_socket, response, strlen(response));
  close(new_socket);
  close(server_fd);

  return 0;
}
