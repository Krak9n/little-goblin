#include "routing/routing.h"
#include "server/server.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10000

void launch(struct server *server);

int main() {

  struct server server = server_constructor(
      // d   //p  // s         // int     //pr //ba //v
      AF_INET, 0, SOCK_STREAM, INADDR_ANY, 80, 10, launch
  );

  server.launch(&server);

  return 0;
}

void launch(struct server *server) {
  char buffer[BUFFER_SIZE];
  int addlen = sizeof(server->address);
  // apprently the problem is here
  // needs to be changed to an http
  // header string
  char *fuck = "fuck";
  int new_socket;
  // passing files
  file("/", "index.html"); // indicating index page
  inorder();

  printf("fuck");
  while(1) {
    printf("waiting for connection\n");

    // a new socket
    new_socket = accept(
        server->socket, 
        (struct sockaddr *)&server->address, 
        (socklen_t *)&addlen
    );
    memset(buffer, 0, BUFFER_SIZE * sizeof(char));
    read(new_socket, buffer, 10000);
    
    printf("buffer: \n%s\n", buffer);
    write(new_socket, fuck, strlen(fuck));
    close(new_socket);
  }
}
