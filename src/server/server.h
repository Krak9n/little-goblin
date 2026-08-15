#pragma once

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

	struct sockaddr_in ipv4_address;
	struct sockaddr_in6 ipv6_address;

	void (*launch)();
} Server;

Server newServer(
				 int domain,
				 int protocol,
				 uint port,
				 int backlog,
				 int service,
				 uint interface,
				 void(*launch)(Server *server));
