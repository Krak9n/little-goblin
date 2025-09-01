#include "server.h"
#include <stdio.h>
#include <stdlib.h>
struct server server_constructor(
    int domain, int protocol, int service, 
    u_long interface, int port, int backlog, 
    void(*launch)(struct server *server)) {
  struct server server;

  // creating parametrs needed
  // for server. use those, instead
  // of defined in struct parametrs
  server.domain = domain;
  server.service = service;
  server.protocol = protocol;
  server.interface = interface;
  server.port = port;
  server.backlog = backlog;

  server.address.sin_family = domain;
  server.address.sin_port = htons(port);
  server.address.sin_addr.s_addr = htonl(interface);

  server.socket = socket(domain, service, protocol);
  if (server.socket = 0) {
    perror("failed to connect to socket:\n");
    exit(1);
  }

  if (-1 == (bind(server.socket, 
      (struct sockaddr *)&server.address, 
      sizeof(server.address)))) {
    perror("failed to bind to socket\n");
    exit(1);
  }

  // backlog for pending arguments
  // like one at time(?)
  if (-1 == (listen(server.socket, server.backlog))) {
    perror("failed to listen\n");
    exit(1);
  }

  server.launch = launch;

  return server;
}
