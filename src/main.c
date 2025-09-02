#include "server/server.h"
#include "http/request.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void concat(char *does, long unsigned int another, char *hope);
void launch(struct Server *server);
char* readfile(FILE *f);

char *working = 
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Content-Length: " ;

const char* notFound =
  "HTTP/1.1 404 Not Found\r\n"
  "Content-Type: text/plain\r\n"
  "Content-Length: 13\r\n"
  "\r\n"
  "404 Not Found";

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
  
  int new_socket;
  FILE* fptr = fopen("web/index.html", "rb"); // for now in all states returns only
                                              // a damn null pointer
  char w[4] = "\r\n";
  char *current; 

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
    printf("~~ CONNECTION ESTABLISHED ~~\n");
    printf("~~ BUFFER ~~ \n%s\n", buffer);
    
    //struct HTTPr requesting = http_constructor(buffer);
    // with rb mode
    current = readfile(fptr); 
    if (current == NULL) {
      printf("index page wasnt opened\n");
      write(new_socket, notFound, strlen(notFound));
    } 
    else {
      concat(working, strlen(current), w);
      write(new_socket, working, strlen(working));
    }
    close(new_socket);
  }
}

// returns NULL on error
char* readfile(FILE *f) {
  
  if (f == NULL || fseek(f, 0, SEEK_END)) {
    return NULL;
  }

  long length = ftell(f);
  rewind(f);
 
  if (length == -1 || (unsigned long) length >= SIZE_MAX) {
    return NULL;
  }

  // converting from long to size_t
  size_t ulength = (size_t) length;
  char *buffer = malloc(ulength + 1);
  
  if (buffer == NULL || fread(buffer, 1, ulength, f) != ulength) {
    free(buffer);
    return NULL;
  }
  buffer[ulength] = '\0'; // now buffer points to a string

  return buffer;
}


void concat(char *does, long unsigned int another, char *hope) {
  does = does + strlen(does);
  while (*does++ = another++ + *hope++);
}
