#include "server/server.h"
#include "mime/mime.h"
#include <dirent.h>
#include "utils/utils.h"
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *iterate(char *path);
void launch(struct Server *server);

char *type = 
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/html\r\n"  // should be something else later
  "Content-Length: \r\n";         // f.e. content-type: %s and in method 
                                  // getFile give it a damn type

char* notFound =
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
  /*
   * will try to make server recognize 
   * if file is css, js, png or ico
  */
  char *index_path = "../src/web";
  char *path = "../src/web/index.html";
  //printf("%s\n", path);
  //char *path = iterate(index_path);
  FILE *fptr = fopen(path, "rb"); // for now in all states returns only
  //if (0 == path == NULL || strcmp(path, "/"))
  //{
  //}                                           // a damn null pointer
  //printf("errno is %d: \n", errno);
  //char *f = getFile(index_path);
  char w[4] = "\r\n";
  //FILE *fptr = fopen(path, "r");
  char *body = readfile(fptr); // returns a null because of non existing file
  char *response = (char*)malloc(1024); // final response

  //char *temp = (char*)malloc(15);
  char *store = (char*)malloc(123);
  int length = strlen(body);

  // goes into loop after
  concat(response, type);
  //concat(response, whole); // here later pass both with type defined 
  intToString(length, store);
  //sprintf(temp, "Content-Length: %s", store); 
  concat(response, store);
  concat(response, w);
  concat(response, w);
  concat(response, body); // body
  
  while(1) {
    printf("active at --> http://localhost:8080/\n");
    printf("~~ WAITING FOR CONNECTION ~~\n");

    // a new socket
    new_socket = accept(
        server->socket, 
        (struct sockaddr *)&server->address, 
        (socklen_t *)&addlen
    );

    printf("~~ CONNECTION ESTABLISHED ~~\n");
    memset(buffer, 0, BUFFER_SIZE * sizeof(char));
    read(new_socket, buffer, 10000);
    printf("~~ BUFFER ~~ \n%s\n", buffer);
   
    // receiving an http request
    //ssize_t bytes_received = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
    //if (-1 == bytes_received) {
    //    perror("failed to receive request\n");
    //    close(new_socket);
    //    exit(1);
    //}

    //struct HTTPr requesting = http_constructor(buffer);
    // with rb mode
    if (NULL == body) {
      printf("index page wasnt opened\n");
      write(new_socket, notFound, strlen(notFound));
    } 

    if(NULL != body) {
      write(new_socket, response, strlen(response));
    }
    close(new_socket);
  }
  fclose(fptr);
}

// path should be
// ../src/web/
char *iterate(char *path) {
  struct dirent *de;  // needed for reading

  DIR *dr = opendir(path);
  char *files; // apperently will return segfault

  if (NULL == dr) {
    printf("could not open current directory\n");
    exit(1);
  }

  while (NULL != (de = readdir(dr))) {
    sprintf(files, "%s\n", de->d_name);
  }

  return files;
}
