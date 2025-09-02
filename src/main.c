#include "server/server.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void launch(struct Server *server);

int main() {

  struct Server server = server_constructor(
      // d   //p  // s         // int     //pr //ba //v
      AF_INET, 0, SOCK_STREAM, INADDR_ANY, PORT, 10, launch
  );

  server.launch(&server);

  return 0;
}

void launch(struct Server *server) {
  char buffer[BUFFER_SIZE];
  int addlen = sizeof(server->address);
  
  char *fuck = "fuck";
  int new_socket;

  while(1) {
    printf("active at --> http://localhost:8080/\n");
    printf("~~ WAITING FOR CONNECTION ~~\n");

    // a new socket
    new_socket = accept(
        server->socket, 
        (struct sockaddr *)&server->address, 
        (socklen_t *)&addlen
    );
    memset(buffer, 0, BUFFER_SIZE * sizeof(char));
    read(new_socket, buffer, 10000);
    
    printf("~~ BUFFER ~~ \n%s\n", buffer);
    write(new_socket, fuck, strlen(fuck));
    close(new_socket);
  }
}
