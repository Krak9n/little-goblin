#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct Server {
	int domain;
	int protocol;
	uint port;
	int backlog;
	int service;
	uint interface;

	uint socket;

	// For IPv4.
	struct sockaddr_in address;

	void (*launch)();
} Server;

Server server_constructor(
						  int domain,
						  int protocol,
						  uint port,
						  int backlog,
						  int service,
						  uint interface,
						  void(*launch)(Server *server));

#endif
