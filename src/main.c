#include "server/server.h"
//#include "http/request.h"
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *getFile(char *path);
char *getFileType(char *path);
void intToString(int num, char str[]);
char *concat(char *help, char *hope); 
void launch(struct Server *server);
char* readfile(FILE *f);

char *type = 
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/plain\r\n"; // should be something else later
                                  // f.e. content-type: %s and in method 
                                  // getFile give it a damn type

char *length = 
  "Content-Length: \r\n";

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
  char *index_path = "../src/web/";
  //printf("%s\n", path);
  //FILE *fptr = fopen(index_path, "rb"); // for now in all states returns only
  //if (0 == path == NULL || strcmp(path, "/"))
  //{
  char *path = "../src/web/index.html";
  //}                                           // a damn null pointer
  //printf("errno is %d: \n", errno);
  char *f = getFile(index_path);
  char w[4] = "\r\n";
  FILE *fptr = fopen(path, "r");
  char *current = readfile(fptr); // returns a null because of non existing file
  char *response = (char*)malloc(1024); // final response

  char *temp = (char*)malloc(15);
  char *store = (char*)malloc(123);
  int length = strlen(current);

  // goes into loop after
  concat(response, type);
  //concat(response, whole); // here later pass both with type defined 
  intToString(length, store);
  sprintf(temp, "Content-Length: %d", store); 
  concat(response, temp);
  concat(response, w);
  concat(response, w);
  concat(response, current);
  
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
    
    //struct HTTPr requesting = http_constructor(buffer);
    // with rb mode
    if (NULL == current) {
      printf("index page wasnt opened\n");
      write(new_socket, notFound, strlen(notFound));
    } 

    if(NULL != current) {
      write(new_socket, response, strlen(response));
    }
    close(new_socket);
  }
  fclose(fptr);
}

char *getFile(char *path) {
 
  char *whole = (char*)malloc(154); // we ll see if it fails
  char *type = (char*)malloc(130);
  FILE *file = fopen(path + 1, "r"); // skips the leading "/"
  if (NULL == file) {
    file = fopen("../src/web/404.html", "r");

    if (NULL == file) {
      return notFound;
    }
  }

  type = getFileType(path);
  if (NULL == type) { 
    type = "application/octet-stream";
  } 

  sprintf(
      whole,  
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: %s\r\n",
      type
  );

  fclose(file);
  return whole;

}

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

char *concat(char *help, char *hope) {
  strcat(help, hope);
  return help;
}

void intToString(int num, char str[]) {
  int i = 0, isNegative = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    int digit = num % 10;
    str[i++] = digit + '0';
    num = num / 10;
  }

  if (isNegative)
    str[i++] = '-';

  str[i] = '\0';

  int start = 0, end = i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

char *getFileType(char *path) {
  if (strstr(path, ".html")) {
      return "text/html";
  }

  if (strstr(path, ".css")) {
      return "text/css";
  }
  
  if (strstr(path, ".js")) {
      return "application/javascript";
  }
  
  if (strstr(path, ".jpg") || strstr(path, ".jpeg")){ 
      return "image/jpeg";
  }
  
  if (strstr(path, ".png")) {
      return "image/png";
  }
  
  if (strstr(path, ".mp4")) {
      return "video/mp4";
  }
  
  return NULL; // Return NULL if no match is found
}
