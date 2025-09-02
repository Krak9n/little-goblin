#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 10000

struct Server {
  int domain;
  int protocol;
  int service;
  u_long interface;
  int port;
  int backlog;

  // ipv4 if im not mistaken
  struct sockaddr_in address; 

  int socket;

  void (*launch)(struct Server *server);
};

struct Server server_constructor(
    int domain, int protocol, int service, 
    u_long interface, int port, int backlog, 
    void(*launch)(struct Server *server)
);

#endif 
