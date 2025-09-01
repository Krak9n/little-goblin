#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

struct server {
  int domain;
  int protocol;
  int service;
  u_long interface;
  int port;
  int backlog;

  // ipv4 if im not mistaken
  struct sockaddr_in address; 

  int socket;

  void (*launch)(struct server *server);
};

struct server server_constructor(
    int domain, int protocol, int service, 
    u_long interface, int port, int backlog, 
    void(*launch)(struct server *server)
);

#endif 
