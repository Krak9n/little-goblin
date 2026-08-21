#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u_int;

typedef struct Server {
	int domain;
	int protocol;
	u_int port;
	int backlog;
	int service;
	u_int interface;

	u_int socket;

	struct sockaddr_in ipv4_address;
	struct sockaddr_in6 ipv6_address;

	void (*launch)();
} Server;

Server newServer(
				 int domain,
				 int protocol,
				 u_int port,
				 int backlog,
				 int service,
				 u_int interface,
				 void(*launch)(Server *server));
